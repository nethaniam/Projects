## SUMMARY
This project simulates a shell using code from [Brennan's GitHub](https://brennan.io/2015/01/16/write-a-shell-in-c/). I adapted the code to have more built-in functions. Here is a list of the following built-in functions that were added:
- lsh_change_user
- lsh_mkdir
- lsh_touch
- lsh_delete
- lsh_open
- lsh_ls
  
**NOTE: The shell will have a HOME directory wherever it is placed.**
# TO-DO LIST:
- [ ]Add more functions to the shell
- [ ]Add comments to describe each function within the code
- [ ]Cleanup code
# FUNCTIONS:
**lsh_change_user**
This function simulates changing between users. The actual concept of changing users within a shell is more complex (requires root user sudo commands). This function does not change users but makes it look as though it does. It requires an input of the user's "name" after lsh_change_user to work. It then prints a string that shows the updated user name (printf("%s@Computer-1:%s$ ", user, folder);).
**lsh_mkdir**
**lsh_touch**
**lsh_delete**
**lsh_open**
**lsh_ls**
