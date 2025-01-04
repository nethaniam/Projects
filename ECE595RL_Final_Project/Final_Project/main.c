/**
 * @file main.c
 *
 * @brief Main source code for the FINAL_project program.
 *
 * This project simulates the idea of an autonomous car using the PMOD COLOR sensor, bumper switches, the analog distance sensors, piezo buzzers etc.
 *
 * The following connections must be made for the PMOD COLOR Module:
 *  - PMOD COLOR IO1 / ~INT     (Pin 1)     <-->  Not Connected
 *  - PMOD COLOR IO2 / LED_EN   (Pin 2)     <-->  MSP432 LaunchPad Pin P8.3
 *  - PMOD COLOR SCL            (Pin 3)     <-->  MSP432 LaunchPad Pin P6.5 (SCL)
 *  - PMOD COLOR SDA            (Pin 4)     <-->  MSP432 LaunchPad Pin P6.4 (SDA)
 *  - PMOD COLOR GND            (Pin 5)     <-->  MSP432 LaunchPad GND
 *  - PMOD COLOR VCC            (Pin 6)     <-->  MSP432 LaunchPad VCC (3.3V)
 *
 * There are a total of four main controller functions to emulate an autonomous vehicle:
 *  1. Localization
 *  2. Traffic light/signal detection
 *  3. Overtake
 *  4. Collision detection and handling
 *
 * @author Nethania Morales, Shantanu Telrandhe
 *
 */

#include <stdint.h>
#include <math.h>
#include "msp.h"
#include "inc/Clock.h"
#include "inc/CortexM.h"
#include "inc/GPIO.h"
#include "inc/EUSCI_A0_UART.h"
#include "inc/PMOD_Color.h"
#include "inc/Buzzer.h"
#include "inc/Motor.h"
#include "inc/Timer_A1_Interrupt.h"
#include "inc/LPF.h"
#include "inc/Bumper_Switches.h"
#include "inc/Analog_Distance_Sensors.h"
#include "inc/SysTick_Interrupt.h"

#define FINAL_PROJECT 1

uint32_t SysTick_ms_elapsed = 0;

uint32_t Filtered_Distance_Left;
uint32_t Filtered_Distance_Center;
uint32_t Filtered_Distance_Right;

uint32_t Converted_Distance_Left;
uint32_t Converted_Distance_Center;
uint32_t Converted_Distance_Right;

void Sample_Analog_Distance_Sensor(){
    uint32_t Raw_A17;
    uint32_t Raw_A14;
    uint32_t Raw_A16;

    Analog_Distance_Sensor_Start_Conversion(&Raw_A17, &Raw_A14, &Raw_A16);

    Filtered_Distance_Right = LPF_Calc(Raw_A17);
    Filtered_Distance_Center = LPF_Calc(Raw_A14);
    Filtered_Distance_Left = LPF_Calc(Raw_A16);

    Converted_Distance_Left = Analog_Distance_Sensor_Calibrate(Filtered_Distance_Left);
    Converted_Distance_Center = Analog_Distance_Sensor_Calibrate(Filtered_Distance_Center);
    Converted_Distance_Right = Analog_Distance_Sensor_Calibrate(Filtered_Distance_Right);

}

uint8_t collision_detected = 0;
void Bumper_Switches_Handler(uint8_t bumper_switch_state){
    if(collision_detected == 0){
        printf("Collision Detected! Bumper Switch State: 0x%02X\n", bumper_switch_state);
        collision_detected = 1;
    }
}

/**
 * @brief This function stops the motors and play an SOS alarm through the pizeo buzzers
 * whenever a collision is detected via the bumper switches
 *
 * @param None
 *
 * @return None
 */
void Handle_Collision(){
    // if a collision is detected, the motor stops and plays a repeated note on the buzzer
    Motor_Stop();
    Play_Note_Pattern();
}

/**
 * @brief This function uses the PMOD sensor data to emulate the actions of a car when at a
 * red light or green light. If the sensor detects a red light, the motor stops. If the sensor detects a
 * green light, the function calls the Lane Controller function that moves the motors foward.
 *
 * @param None
 *
 * @return None
 */
void PMOD_Controller(){
    // Declare structs for both raw and normalized PMOD Color data
     PMOD_Color_Data pmod_color_data;
     PMOD_Calibration_Data calibration_data;

     pmod_color_data = PMOD_Color_Get_RGBC();
     calibration_data = PMOD_Color_Init_Calibration_Data(pmod_color_data);
     Clock_Delay1us(2400);
     while(1)
     {
         // The on-board LED on the PMOD COLOR module can be controlled using the PMOD_Color_LED_Control function
         // PMOD_Color_LED_Control(PMOD_COLOR_ENABLE_LED);

         // Sample the PMOD COLOR sensor every 50 ms
         pmod_color_data = PMOD_Color_Get_RGBC();
         PMOD_Color_Calibrate(pmod_color_data, &calibration_data);
         pmod_color_data = PMOD_Color_Normalize_Calibration(pmod_color_data, calibration_data);
         printf("r=%04x g=%04x b=%04x\r\n", pmod_color_data.red, pmod_color_data.green, pmod_color_data.blue);
         Clock_Delay1ms(50);
         // if the pmod sensor senses the color red, the motor stops
         // else it calls the Lane_Controller function to have the robot start moving forward
         if(pmod_color_data.red>pmod_color_data.green){
             Motor_Stop();}
         else if (pmod_color_data.red<pmod_color_data.green){
                 Lane_Controller();

         }
     }
}

/**
 * @brief This function makes the robot overtake an object/obstacle afeter being behind the object for a certain amount of time
 *
 * @param None
 *
 * @return None
 */
void Overtake_Controller(){
    if(Converted_Distance_Center > 300){
        // if center distance center is greater than 300 after the wait time
        // the robot will call the Lane_Controller function
        Lane_Controller();}
    else{
        // robot turns to the right and stops there for 550ms
        Motor_Left(3500,3500);
        Clock_Delay1ms(550);
        Motor_Stop();
        Clock_Delay1ms(550);
        // if there is an object in front it, the robot returns to its original position
        if(Converted_Distance_Center < 500){
            Motor_Right(3500,3500);
            Clock_Delay1ms(470);
            Motor_Stop();
            Clock_Delay1ms(10000);
            // the Overtake function is called again to keep checking if it is safe to overtake
            Overtake_Controller();
        }
        else{
            // if there is no object in the lane next to the robot, the robot goes around the object in front of it
            Motor_Forward(3500,3500);
            Clock_Delay1ms(700);
            Motor_Forward(3500,0);
            Clock_Delay1ms(1000);
            Motor_Forward(3500,3500);
            Clock_Delay1ms(2000);
            Motor_Stop();
            Clock_Delay1ms(550);
            // motor turns right to merge into previous lane
            Motor_Right(3500,3500);
            Clock_Delay1ms(550);
            Motor_Stop();
            Clock_Delay1ms(550);
            // uses sensors to check if there is an object to the robots right
            // if so, the robot does not merge to the right and stays in its lane
            if(Converted_Distance_Center < 500){
                Motor_Left(3500,3500);
                Clock_Delay1ms(550);
                Motor_Stop();
                Clock_Delay1ms(550);
            }
            // if not object to its right, the robot merges back to the orginal lane
            else{
                Motor_Forward(3500,3500);
                Clock_Delay1ms(800);
                Motor_Forward(0,3500);
                Clock_Delay1ms(750);
            }
        }
    }
}

/**
 * @brief This function controls how fast the robot goes in its lane using the analog sensors
 *
 * @param None
 *
 * @return None
 */
void Lane_Controller(){
    // if an object is backing up towards the robot, the robot will move backwards
    if(Converted_Distance_Center < 200){
        Motor_Backward(1500,1500);
    }
    // if there is an object at 300mm or less, the robot stops
    else if(Converted_Distance_Center < 300){
        Motor_Stop();
        // robot waits for 5000ms before checking analog distance sensor
        Clock_Delay1ms(5000);
        if(Converted_Distance_Center < 200){
                Motor_Backward(1500,1500);
            }
        else if(Converted_Distance_Center < 300){
            // if center distance center is less than 300 after the wait time
            // the robot will overtake the "car"
            Overtake_Controller();
        }
    }
    // if there is an object at 500mm or less, the robot slows its speed
    else if(Converted_Distance_Center < 500){
        Motor_Forward(1500,1500);
    }
    // if no object in front of the robot, the robot goes full speed forward
    else{
        Motor_Forward(3500,3500);
    }
}

void Timer_A1_Periodic_Task(){
    Sample_Analog_Distance_Sensor();
}

void SysTick_Handler(void)
{
    // constantly checking whether a collision is detected
    SysTick_ms_elapsed++;
    if (collision_detected == 1){
        // if so, the Handle_Collision function is called
        Handle_Collision();
    }
    // this simulates the red stop light and green stop light using LED2
    if(SysTick_ms_elapsed >= 7000){
        LED2_Output(RGB_LED_RED);
        Clock_Delay1ms(5000);
        SysTick_ms_elapsed = 0;
    }
    else{
        LED2_Output(RGB_LED_GREEN);

    }
}

int main(void)
{
    uint32_t Raw_A17;
    uint32_t Raw_A14;
    uint32_t Raw_A16;

    // Ensure that interrupts are disabled during initialization
    DisableInterrupts();

    // Initialize the 48 MHz Clock
    Clock_Init48MHz();

    // Initialize the built-in red LED
    LED1_Init();
    LED2_Init();

    // Initialize the buttons
    Buttons_Init();

    // Initialize EUSCI_A0_UART
    EUSCI_A0_UART_Init_Printf();

    // Initialize the bumper switches which will be used to generate external I/O-triggered interrupts
    Bumper_Switches_Init(&Bumper_Switches_Handler);

    // Initialize the PMOD Color module
    PMOD_Color_Init();

    // Initialize the buzzer
    Buzzer_Init();

    // Initialize the motor
    Motor_Init();

    // Indicate that the PMDO Color module has been initialized and powered on
    //printf("PMOD COLOR has been initialized and powered on.\n");

    // Initialize Analog Sensor
    Analog_Distance_Sensor_Init();

    // Start conversion
    Analog_Distance_Sensor_Start_Conversion(&Raw_A17, &Raw_A14, &Raw_A16);

    // Initialize low pass filters
    LPF_Init(Raw_A17, 64);
    LPF_Init(Raw_A14, 64);
    LPF_Init(Raw_A16, 64);

    // Initialize SysTick periodic interrupt with a rate of 100 Hz
    SysTick_Interrupt_Init(SYSTICK_INT_NUM_CLK_CYCLES, SYSTICK_INT_PRIORITY);

    // Initialize Timer A1
    Timer_A1_Interrupt_Init(&Timer_A1_Periodic_Task, TIMER_A1_INT_CCR0_VALUE);

    // Enable the interrupts used by the modules
    EnableInterrupts();
    LED2_Output(RGB_LED_GREEN);
    // Display the PMOD Color Device ID
   printf("PMOD Color Device ID: 0x%02X\n", PMOD_Color_Get_Device_ID());
    while(1){
#if defined FINAL_PROJECT

    PMOD_Controller();

#elif defined CONTROLLER_2
    #if defined CONTROLLER_1 || CONTROLLER_3
        #error "Only CONTROLLER_1, CONTROLLER_2, or CONTROLLER_3 can be active at the same time."
    #endif

    // Your function for Task 1 goes here (Controller_2)

#elif defined CONTROLLER_3
    #if defined CONTROLLER_1 || CONTROLLER_2
#error "Only CONTROLLER_1, CONTROLLER_2, or CONTROLLER_3 can be active at the same time."
    #endif

    // Your function for Task 2 goes here (Controller_3)

#else
    #error "Define either one of the options: CONTROLLER_1, CONTROLLER_2, or CONTROLLER_3."
#endif
    }
}
