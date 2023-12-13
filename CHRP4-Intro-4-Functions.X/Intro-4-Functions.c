/*==============================================================================
 Project: Intro-4-Functions             Activity: mirobo.tech/intro-4
 Date:    December 12, 2023
 
 This introductory programming activity for the mirobo.tech CHRP4 and UBMP4
 demonstrates the use of functions and the ability to pass variables between
 the program's main code and the function code.
 
 Additional program analysis and programming activities examine the location of
 function code within the program, introduce function prototypes, reinforce the
 concepts of global variables, local variables, and making sound using loops.
==============================================================================*/

#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "CHRP4.h"           // Include CHRP4 constants and functions

// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.

// Button constant definitions
#define NOBUTTON    0
#define UP          1
#define DOWN        2

// Program variable definitions
unsigned char LED4Brightness = 125;
unsigned char button;

unsigned char read_button(void)
{
    if(SW4 == 0)
    {
        return(UP);
    }
    else if(SW3 == 0)
    {
        return(DOWN);
    }
    else
    {
        return(NOBUTTON);
    }
}

void pwm_LED4(unsigned char pwmValue)
{
    for(unsigned char t = 255; t != 0; t --)
    {
        if(pwmValue == t)
        {
            LED4 = 1;
        }
        __delay_us(20);
    }
    // End the pulse if pwmValue < 255
    if(pwmValue < 255)
    {
        LED4 = 0;
    }
}

int main(void)
{
    OSC_config();               // Configure internal oscillator for 48 MHz
    CHRP4_config();             // Configure I/O for on-board CHRP4 devices
	
    while(1)
	{
        // Read up/down buttons and adjust LED4 brightness
        button = read_button();
        
        if(button == UP && LED4Brightness < 255)
        {
            LED4Brightness += 1;
        }

        if(button == DOWN && LED4Brightness > 0)
        {
            LED4Brightness -= 1;
        }

        // PWM LED4 with current brightness
        pwm_LED4(LED4Brightness);
        
        // Reset the microcontroller and start the bootloader if SW1 is pressed.
        if(SW1 == 0)
        {
            RESET();
        }
    }
}

// Move the function code to here in Program Analysis Activities step 6.


/* Learn More -- Program Analysis Activities
 * 
 * 1.   Functions start with a function declaration (the first line of the
 *      function that provides the return type, function name, and optional
 *      function parameters). The main function, starting with the function
 *      declaration 'int main(void)' has been a part of every introductory
 *      program so far, and it is still a part of this program.
 * 
 *      This program also contains two new functions: one begins with the
 *      function declaration 'unsigned char read_button(void)', and the other
 *      with 'void pwm_LED4(unsigned char pwmValue)'. 

 *      Where are these functions located in the program? Which function do you
 *      think will run first? How can you know?
 * 
 * 2.   What is the purpose of the 'unsigned char' variable type declaration in
 *      the read_button() function? Is it used by the function to receive a
 *      variable from the main code, or to return a variable to the main code?
 * 
 * 3.   How does the function call statement 'button = read_button();' in the
 *      main code support your answer in 2, above?
 * 
 * 4.   What value will the button variable be set to when no button is pressed?
 *      Where does this value originate?
 * 
 * 5.   What is the purpose of the 'unsigned char' variable type declaration in
 *      the pwm_LED4() function? Where does the value of the variable come from?
 *      Which variable in the function will be used to store this value?
 * 
 * 6.   C language compilers typically read through an entire program file in a
 *      single pass, converting the C code into machine code. The two functions
 *      read_button() and pwm_LED4() are located above the main() function so
 *      that their memory locations and variables will be defined when they are
 *      compiled, before the remainder of the program is compiled. When the
 *      compiler later encounters a function call statement to one of these
 *      functions, it already knows that the functions exist, and where and how
 *      to access their code and variables.
 * 
 *      Try moving the read_button() and pwm_LED4() functions to the end of the
 *      program, below the closing brace of the main() function, and build the
 *      program in MPLAB. What happens?
 * 
 *      The compiler should have reported an error since it had not encountered
 *      the functions before trying to compile the function call statements in
 *      the main code. This error can be eliminated by adding function prototype
 *      statements above the main() function in the code.
 * 
 *      A function prototype is an 'empty' copy the function declaration (the
 *      first line of the function). The purpose served by a function prototype
 *      is to inform the compiler about both the name of a function that the
 *      compiler will encounter, as well as the number and type of variables
 *      that the function will use. A C language linker program will take care
 *      of sorting out the names and memory locations of all of the functions
 *      and variables used in a program, and arranges all of them in the proper
 *      order in the microcontroller's memory following the compilation step.
 * 
 *      Let's explore how this works. Leave the functions in their new location,
 *      below the main() function, and add the two function prototype
 *      statements shown below, above the main() function and all of the program
 *      code. In other words, add these two lines back in the original location
 *      of the functions in the program, right below the variable definitions:

unsigned char read_button(void);

void pwm_LED4(unsigned char);

 *      The function prototype for the pwm_LED4() function is slightly different
 *      than the actual function declaration statement that was moved below the
 *      while loop in the program code. Can you identify the difference?
 *      Thinking about the compilation process described earlier, can you
 *      provide a reason why the difference will not be a problem during
 *      compilation?
 * 
 *      Building the program now, with the added function prototypes, should
 *      work without generating errors just as it did in the original program.
 *      Try it!
 * 
 * 7.   In the C language, functions can be located either above the main
 *      program code that calls them (as they were in the original program),
 *      below the main() function of the program if function prototypes are
 *      added above the main code (as seen in step 6, above), or in completely
 *      separate files known as function libraries.
 * 
 *      Function libraries are separate '.c' source code files which are
 *      typically joined to your project's main '.c' file using 'include'
 *      statements. The include statements specify a '.h' header file. Header
 *      files contain both the variable definitions and the function prototypes
 *      for their associated .c files, which contain just the function's C
 *      language source code. Header files typically also contain comments and
 *      descriptions relating to the purpose and use of the included functions.
 * 
 *      The statement '#include "CHRP4.h"' near the top of this program (and
 *      all of the other Introductory programs), adds external functions into
 *      the main program. The 'CHRP4.h' file contains function prototypes and
 *      other details about the functions located in the 'CHRP4.c' file, along
 *      with various symbolic constants used by both the main program in this
 *      source code file, as well as the program code in the CHRP4.c file.
 * 
 *      Open the CHRP4.c file in the code editor and you will find the two
 *      config() functions called from this program's main() function. Are any
 *      values passed between this code and the config() functions? How can you
 *      tell?
 * 
 * 8.   The 'button' variable is a global variable because it was assigned
 *      at the beginning of this program, outside of any functions. Global
 *      variables are available to all functions. How does the 'button'
 *      variable get assigned a value? In which function does this occur?
 * 
 * 9.   Which variable does the value of LED4Brightness get transferred to in
 *      the pwm_LED4() function? Is this variable global, or local to the LED
 *      function? Could the pwm_LED4() function use the LED4Brightness variable
 *      directly, instead of transferring its value to another variable first?
 *      What would happen to the value of the LED4Brightness variable if it was
 *      used in the pwm_LED4() function?
 * 
 * 10.  Functions make it easy and quick to use or re-use complex code through
 *      a simple function call. Take a close look at this program's main()
 *      function, and read through the code again. What benefits have been
 *      obtained by using the read_button() and pwm_LED4() calls in the code
 *      instead of placing the entire contents of the function code into the
 *      program code?
 *      
 *      Likewise, what benefits are provided to beginner programmers by using
 *      the OSC_config(); and CHRP4_config(); function calls instead of having
 *      their function code inserted into the main program?
 * 
 * 11.  The OSC_config() and CHRP4_config() functions are defined in the CHRP4.h
 *      header file, and their program code is located in the CHRP4.c file. What
 *      other functions are available in the header file? Is their corresponding
 *      program code in also in the CHRP4.c file?
 *      
 * 
 * Programming Activities
 * 
 * 1.   In addition to brightening or dimming an LED using PWM, it would be
 *      useful to have buttons that are able to instantly turn LED D4 fully on
 *      or fully off. But, PWM dimming is still a useful capability that should
 *      be retained.
 * 
 *      Modify the read_button() and main() functions to enable SW2 as an
 *      instant-on button, and SW5 as an instant-off button. Pressing either of
 *      these buttons should over-write the current LED4Brightness value, while
 *      still allowing SW3 and SW4 to smoothly adjust the brightness using PWM.
 *
 * 2.   Duplicate this program to create a new program using one function to
 *      read the pushbuttons, and a second function to control the LEDs. Each
 *      pushbutton should light its corresponding LED when pressed, and turn
 *      the LED off when it is released.
 * 
 * 3.   Duplicate your program from step 2 to create a four note (or more)
 *      music player using two functions: one to read the pushbuttons, and a
 *      second to play a corresponding sound on the piezo beeper using a loop
 *      to create the sound wave's period. Try to do this by creating a single
 *      sound function that will accept a parameter representing the note's
 *      pitch, and have each button pass the sound function a different value.
 * 
 * 4.   A function that converts an 8-bit binary value into its equivalent
 *      3-digit decimal numbers might be useful for helping to debug programs
 *      (and we will need one in the next activity). Create a function that
 *      converts an 8-bit binary number into three character variables to store
 *      the hundreds, tens, and ones digits of a (binary) number passed to the
 *      function. For example, passing the function the value of 142 will
 *      result in the hundreds variable containing the value 1, the tens
 *      variable containing 4, and the ones variable 2. How could you test this
 *      function to verify that it works? Try it! (Hint: the BCD number system
 *      represents the decimal digits 0-9 using only 4 bits. Can you display
 *      the equivalent BCD digits on the LEDs?)
 */
