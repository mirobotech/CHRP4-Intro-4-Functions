/*==============================================================================
 File: CHRP4.h
 Date: August 1, 2023
 
 CHRP4 (PIC16F1459) symbolic constant and function definitions.
 
 I/O pin definitions sections:
 These sections assign unique symbolic names to on-board CHRP4 input and output
 devices making it easier to address them instead of using PIC16F1459 pin names.
 In the PIC16F1459 microcontroller, digital inputs are read through port
 registers (e.g. PORTC) and digital outputs write to port latches (e.g. LATC).
 Some pins are assigned more than one name to match older versions of the
 circuit board (e.g. D1 and LED1 refer to the same LED), while other pins have
 both an input definition as well as an output definition (e.g. H1IN and H1OUT).
 Add or modify symbolic definitions as needed.
 
 ADC input channel definitions section:
 Definitions representing the ADCON0 register channel select (CHS) bits, which
 are used to switch between ADC channels available on CHRP4. These definitions
 are used with the ADC_select_channel and ADC_read_channel functions.
 
 Function prototypes section:
 Function prototype definitions for each of the functions in the CHRP4.c file
 are located here. Function prototypes must exist for all external functions
 before they can be called from within the main program code.
==============================================================================*/

// PORTA I/O pin definitions
#define SW1         PORTAbits.RA3   // SW1/PROG/Reset (MCLR) pushbutton input
#define BEEPER      LATAbits.LATA4  // Piezo beeper (LS1) output
#define	LS1         LATAbits.LATA4  // Piezo beeper (LS1) output
#define D1          LATAbits.LATA5  // LED D1/RUN LED output (active-low)
#define LED1        LATAbits.LATA5  // LED D1/RUN LED output (active-low)

// PORTB I/O pin definitions
#define H1IN        PORTBbits.RB4   // External I/O header H1 input
#define H1OUT       LATBbits.LATB4  // External I/O header H1 output
#define SW2         PORTBbits.RB4   // Pushbutton SW2 input

#define H2IN        PORTBbits.RB5   // External I/O header H2 input
#define H2OUT       LATBbits.LATB5  // External I/O header H2 output
#define SW3         PORTBbits.RB5   // Pushbutton SW3 input
#define TRIG        LATBbits.LATB5  // SONAR module Trigger output

#define ECHO        PORTBbits.RB6   // SONAR module Echo input
#define H3IN        PORTBbits.RB6   // External I/O header H3 input
#define H3OUT       LATBbits.LATB6  // External I/O header H3 output
#define SW4         PORTBbits.RB6   // Pushbutton SW4 input

#define H4IN        PORTBbits.RB7   // External I/O header H4 input
#define H4OUT       LATBbits.LATB7  // External I/O header H4 output
#define IRIN        PORTBbits.RB7   // IR demodulator input
#define SW5         PORTBbits.RB7   // Pushbutton SW5 input

// PORTC I/O pin definitions
#define D6          LATCbits.LATC0  // Line sensor LED output
#define LED6        LATCbits.LATC0  // Line sensor LED output
#define D7          LATCbits.LATC0  // Left floor sensor LED/+5V output
#define LED7        LATCbits.LATC0  // Left floor sensor LED/+5V output

#define D8          LATCbits.LATC1  // Right floor sensor LED/+5V output
#define LED8        LATCbits.LATC1  // Right floor sensor LED/+5V output

#define Q1          PORTCbits.RC2   // Left line sensor input
#define Q3          PORTCbits.RC2   // Left floor sensor input

#define Q2          PORTCbits.RC3   // Right line sensor input
#define Q4          PORTCbits.RC3   // Right floor sensor input

#define D2          LATCbits.LATC4  // LED D2 output
#define LED2        LATCbits.LATC4  // LED D2 output
#define M1A         LATCbits.LATC4  // Motor 1A output
#define MOTOR1A     LATCbits.LATC4  // Motor 1A output

#define D3          LATCbits.LATC5  // LED D3 output
#define LED3        LATCbits.LATC5  // LED D3 output
#define M1B         LATCbits.LATC5  // Motor 1B output
#define MOTOR1B     LATCbits.LATC5  // Motor 1B output

#define D4          LATCbits.LATC6  // LED D4 output
#define LED4        LATCbits.LATC6  // LED D4 output
#define M2A         LATCbits.LATC6  // Motor 2A output
#define MOTOR2A     LATCbits.LATC6  // Motor 2A output

#define D5          LATCbits.LATC7  // LED D5 output
#define LED5        LATCbits.LATC7  // LED D5 output
#define M2B         LATCbits.LATC7  // Motor 2B output
#define MOTOR2B     LATCbits.LATC7  // Motor 2B output

// ADC (A-D converter) input channel definitions
#define AN6         0b00011000      // A-D converter channel 6 input
#define ANQ1        0b00011000      // Floor sensor Q1 analogue input (Ch6)
#define ANQ3        0b00011000      // Floor sensor Q3 analogue input (Ch6)
#define AN7         0b00011100      // A-D converter channel 7 input
#define ANQ2        0b00011100      // Floor sensor Q2 analogue input (Ch7)
#define ANQ4        0b00011100      // Floor sensor Q4 analogue input (Ch7)
#define AN10        0b00101000      // A-D converter channel 10 input (H1)
#define ANH1        0b00101000      // A-D converter channel 10 input (H1)
#define AN11        0b00101100      // A-D converter channel 11 input (H2)
#define ANH2        0b00101100      // A-D converter channel 11 input (H2)
#define ANTIM       0b01110100      // On-die temperature indicator module input

// Clock frequency definition for delay macros and simulation
#define _XTAL_FREQ  48000000        // Set clock frequency for time delays

// Prototypes for CHRP4.c functions:

/**
 * Function: void OSC_config(void)
 * 
 * Configure oscillator for 48 MHz operation (required for USB uC bootloader).
 */
void OSC_config(void);

/**
 * Function: void CHRP4_config(void)
 * 
 * Configure hardware ports and peripherals for on-board CHRP4 I/O devices.
 */
void CHRP4_config(void);

/**
 * Function: void ADC_config(void)
 * 
 * Configure ADC for 8-bit conversion from on-board phototransistor Q1 (AN7).
 */
void ADC_config(void);

/**
 * Function: void ADC_select_channel(unsigned char channel)
 * 
 * Enable ADC and switch ADC input mux to the channel specified by one of the
 * channel constants defined above.
 * 
 * Example usage: ADC_select_channel(ANQ2);
 */
void ADC_select_channel(unsigned char);

/**
 * Function: unsigned char ADC_read(void)
 * 
 * Convert currently selected ADC channel and return an 8-bit conversion result.
 * 
 * Example usage: light_level = ADC_read();
 */
unsigned char ADC_read(void);

/**
 * Function: unsigned char ADC_read_channel(unsigned char channel)
 * 
 * Enable ADC, switch to the channel specified by one of the channel constants
 * defined above, and return an 8-bit conversion result.
 * 
 * Example usage: light_level = ADC_read_channel(ANQ1);
 */
unsigned char ADC_read_channel(unsigned char);

// TODO - Add additional function prototypes for any new functions added to
// the CHRP4.c file here.
