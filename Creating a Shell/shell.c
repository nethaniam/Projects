#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <libgen.h>
#include <dirent.h>

# define LSH_RL_BUFSIZE 1024
char *lsh_read_line(void){
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if(!buffer) {
        fprintf(stderr, "ALLOCATION ERROR!\n");
        exit(EXIT_FAILURE);
    }

    while(1){
        // read character
        c = getchar();

        // if hit EOF, replace wiht null character
        if(c == EOF || c == '\n'){
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        // if execeeded the buffer, reallocate
        if(position >= bufsize){
            bufsize += LSH_RL_BUFSIZE; // increase bufsize of 1024
            buffer = realloc(buffer, bufsize);
            if(!buffer){
                fprintf(stderr, "ALLOCATION ERROR!\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
char **lsh_split_line(char *line){
    int bufsize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if(!tokens){
        fprintf(stderr, "ALLOCATIONS ERROR!\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, LSH_TOK_DELIM);
    while(token != NULL){
        tokens[position] = token;
        position++;
        if(position >= bufsize){
            bufsize += LSH_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if(!tokens){
                fprintf(stderr, "ALLOCATION ERROR!\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

int lsh_launch(char **args){
    pid_t pid, wpid;
    int status;
    pid = fork();
    if(pid == 0){
        // child process
        if(execvp(args[0], args) == -1){
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    } else if(pid<0){
        perror("lsh");
    } else{
        // parent process
        do{
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);
int lsh_change_user(char **args);
int lsh_mkdir(char **args);
int lsh_touch(char **args);
int lsh_delete(char **args);
int lsh_open(char **args);
int lsh_ls(char **args);

char *builtin_str[] = {
    "cd", "ls", "help", "change_user", "mkdir", "touch", "open", "delete", "exit"
};

int (*builtin_func[]) (char **) = {
    &lsh_cd,
    &lsh_ls,
    &lsh_help,
    &lsh_change_user,
    &lsh_mkdir,
    &lsh_touch,
    &lsh_open,
    &lsh_delete,
    &lsh_exit
};

int lsh_num_builtins(){
    return sizeof(builtin_str) / sizeof(char *);
}

#define MAX_PATH_LEN 1024
#define MAX_HISTORY 100
char dir_history[MAX_HISTORY][MAX_PATH_LEN];
int history_index = -1;

void push_dir(const char *dir){
    if(history_index< MAX_HISTORY - 1){
        history_index++;
        strncpy(dir_history[history_index], dir, MAX_PATH_LEN);
    } else {
        fprintf(stderr, "DIRECTORY HISTORY IS FULL\n");
    }
}

char *pop_directory(){
    if(history_index >=0){
        return dir_history[history_index--];
    }
    return NULL;
}

int lsh_cd(char **args){
    char cwd[MAX_PATH_LEN];
    if(args[1] != NULL && strcmp(args[1], "-") == 0){
        char *prev_dir = pop_directory();
        if(prev_dir == NULL){
            fprintf(stderr, "NO PREVIOUS DIRECTORY TO GO BACK TO!\n");
            return 1;
        }
        if(chdir(prev_dir) != 0){
            perror("lsh");
            return 1;
        }
            printf("Changed successfully to previous directory\n");
            return 1;
        } 
        if(getcwd(cwd, sizeof(cwd)) == NULL){
            perror("getcwd() error");
            return 1;
        }
        if(args[1] == NULL){
        char *home_dir = getenv("HOME");
        if(home_dir != NULL){
            push_dir(cwd);
            if(chdir(home_dir) != 0){
                perror("lsh");
            }
        } else{
            fprintf(stderr, "HOME VARIABLE NOT SET!\n");
        }
    } else {
        push_dir(cwd);
        if(chdir(args[1]) != 0){
            perror("lsh");
            return 1;
        }
    }
    return 1;
}

int lsh_ls(char **args){
    struct dirent *entry;
    DIR *dir = opendir(".");
    if(dir == NULL){
        perror("lsh");
        return 1;
    }
    while((entry = readdir(dir)) != NULL){
        printf("%s  ", entry->d_name);
    }
    printf("\n");
    closedir(dir);
    return 1;
}

int lsh_help(char **args){
    int i;
    printf("Help Menu\n");
    printf("type program names and arguments, then hit enter\n");
    printf("the following are built in:\n");

    for (i = 0; i < lsh_num_builtins(); i++){
        printf("    %s\n", builtin_str[i]);
    }

    printf("use the man command for info on other programs\n");
    return 1;
}

int lsh_change_user(char **args){
    if(args[1] == NULL){
        fprintf(stderr, "lsh: expected argument after \"change_user\"\n");
        printf("PLEASE INCLUDE THE USER YOU WANT TO CHANGE TO!\n");
    } else{
        if(setenv("USER", args[1], 1) !=0){
            perror("lsh");
        } else{
            printf("user changed to: %s\n", args[1]);
        }
    }
    return 1;
}

int lsh_mkdir(char **args){
    if(args[1] == NULL){
        fprintf(stderr, "lsh: expected argument after \"mkdir\"\n");
        printf("PLEASE INCLUDE THE NAME OF THE DIRECTORY!\n");
        return 1;
    } else{
        if(mkdir(args[1], 0777) != 0){
            perror("lsh");
        } else{
            printf("Directory \"%s\" created successfully \n", args[1]);
        }
    }
    return 1;
}

int lsh_touch(char **args){
    if(args[1] == NULL){
        fprintf(stderr, "lsh: expected argument after \"touch\"\n");
        printf("PLEASE INCLUDE THE NAME OF THE FILE!");
        return 1;
    } else{
        FILE *file = fopen(args[1], "w");
        if (file == NULL){
            perror("lsh");
        } else{
            printf("File \"%s\" created successfully \n", args[1]);
            fclose(file);
        }
    }
    return 1;
}

int lsh_open(char **args){
    if(args[1] == NULL){
        fprintf(stderr, "EXPECTED ARGUMENT AFTER \"open\"\n");
        return 1;
    }
    pid_t pid = fork();
    if(pid == 0){
        char *commands[] = {"xdg-open", "open", "nano", "vim", "gedit", NULL};
        for(int i = 0; commands[i] != NULL; i++){
            execlp(commands[i], commands[i], args[1], NULL);
        }

        perror("lsh");
        exit(EXIT_FAILURE);
    } else if (pid <0){
        perror("lsh");
    } else {
        wait(NULL);
    }
    return 1;
}

int lsh_delete(char **args){
    struct dirent *entry;
    DIR *dir = opendir(".");
    if(args[1] == NULL){
        fprintf(stderr, "lash:expected argument to \"delete\"\n");
        return 1;
    } else{
        if(remove(args[1]) != 0){
            perror("lsh");
        } else{
            while((entry = readdir(dir)) != NULL){
                if(args[1] == entry->d_name){
                printf("File \"%s\" deleted successfully \n", args[1]);
                } else{
                    continue;
                }
            }
        }
    }
    return 1;
}

int lsh_exit(char **args){
    return 0;
}

int lsh_execute(char **args){
    int i;
    if(args[0] == NULL){
        return 1;
    }
    for (i = 0; i<lsh_num_builtins(); i++){
        if(strcmp(args[0], builtin_str[i]) == 0){
            return (*builtin_func[i])(args);
        }
    }
    //return lsh_launch(args);
    return 1;
}

void lsh_loop(void){
    char *line;
    char **args;
    int status;

    do{
        char *user = getenv("USER");
        if(user == NULL){
            user = "unkown";
        }
        char cwd[1024];
        if(getcwd(cwd, sizeof(cwd)) != NULL) {
            char *folder = basename(cwd);
            printf("%s@Computer-1:%s$ ", user, folder);
        } else{
            perror("getcwd() error");
            continue;
        }
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);

        free(line);
        free(args);
    } while(status);
}

int main(int argc, char **argv){
    // load configuration files, if any

    // run the command loop
    lsh_loop();

    // perform any shutdown/cleanup procedures
    return EXIT_SUCCESS;
}