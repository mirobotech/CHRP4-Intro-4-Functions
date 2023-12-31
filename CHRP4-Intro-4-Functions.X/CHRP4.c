/*==============================================================================
 File: CHRP4.c
 Date: August 1, 2023
 
 CHRP4 (PIC16F1459) hardware initialization functions
 
 Initialization functions used to configure the PIC16F1459 oscillator, on-board
 CHRP4 I/O devices, and ADC (analog-to-digital converter), as well as ADC
 channel selection and conversion functions. Include the CHRP4.h file in your
 main program to call these functions. Add or modify functions as needed.
==============================================================================*/

#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "CHRP4.h"           // Include CHRP4 constant & function definitions

// Configure oscillator for 48 MHz operation (required for USB-uC bootloader).
void OSC_config(void)
{
    OSCCON = 0xFC;              // Set 16MHz HFINTOSC with 3x PLL enabled
    ACTCON = 0x90;              // Enable active clock tuning from USB clock
    while(!PLLRDY);             // Wait for PLL lock (disable for simulation)
}

// Configure hardware ports and peripherals for on-board CHRP4 I/O devices.
void CHRP4_config(void)
{
    OPTION_REG = 0b01010111;    // Enable port pull-ups, TMR0 internal div-256

    LATA = 0b00000000;          // Clear output latches before configuring PORTA
    ANSELA = 0b00000000;        // Disable analog input on all PORTA input pins
    WPUA = 0b00001000;          // Enable weak pull-up on SW1 input only
    TRISA = 0b00001111;         // Set LED D1 and Beeper pins as outputs

    LATB = 0b00000000;          // Clear output latches before configuring PORTB
    ANSELB = 0b00000000;        // Disable analog input on all PORTB input pins
    WPUB = 0b11110000;          // Enable weak pull-ups on pushbutton inputs
    TRISB = 0b11110000;         // Enable pushbutton SW2-SW5 inputs
//    TRISB = 0b11010000;         // Enable SONAR module TRIG output, ECHO input

    LATC = 0b00000000;          // Clear output latches before configuring PORTC
    ANSELC = 0b00000000;        // Disable analog input on all PORTC input pins
    TRISC = 0b00001100;         // Enable phototransistor Q1/Q3, Q2/Q4 inputs

    // TODO - Enable interrupts here, if required.
}

// Configure ADC for 8-bit conversion. Set on-board phototransistor Q1 as input.
void ADC_config(void)
{
    LATC = 0b00000000;          // Clear Port C latches before configuring PORTC
    
    // Enable analog input and disable digital output for each analog pin below:
    TRISCbits.TRISC2 = 1;       // Disable Q1/Q3 output driver (TRISx.bit = 1)
    TRISCbits.TRISC3 = 1;       // Disable Q2/Q4 output driver
    ANSELC = 0b00001100;        // Enable Q1 & Q2 analog input (ANSELx.bit = 1)
    
    // General ADC setup and configuration
    ADCON0 = 0b00011100;        // Set channel to Q1/AN7, leave ADC off
    ADCON1 = 0b01100000;        // Left justified result, FOSC/64 clock, +VDD ref
    ADCON2 = 0b00000000;        // Auto-conversion trigger disabled
}

// Enable ADC and switch ADC input mux to the specified channel (use channel
// constants defined in CHRP4.h header file - e.g. ANQ1).
void ADC_select_channel(unsigned char channel)
{
    ADON = 1;                   // Turn the ADC on
    ADCON0 = (ADCON0 & 0b10000011); // Clear channel select (CHS) bits by ANDing
    ADCON0 = (ADCON0 | channel);	// Set channel by ORing with channel constant
}

// Convert the currently selected channel and return an 8-bit conversion result.
unsigned char ADC_read(void)
{
    GO = 1;                     // Start the conversion by setting Go/~Done bit
	while(GO)                   // Wait for the conversion to finish (GO==0)
        ;                       // Terminating loop on new line silences warning
    return (ADRESH);            // Return the MSB (upper 8-bits) of the result
}

// Enable ADC, switch to specified channel, and return 8-bit conversion result.
// Use channel constants defined in CHRP4.h header file (e.g. ANQ1).
unsigned char ADC_read_channel(unsigned char channel)
{
    ADON = 1;                   // Turn the ADC on
    ADCON0 = (ADCON0 & 0b10000011); // Clear channel select (CHS) bits by ANDing
    ADCON0 = (ADCON0 | channel);	// Set channel by ORing with chan. constant
    __delay_us(5);              // Allow input to settle (charges internal cap.)
    GO = 1;                     // Start the conversion by setting Go/~Done bit
	while(GO)                   // Wait for the conversion to finish (GO==0)
        ;                       // Terminating loop on new line silences warning
    ADON = 0;                   // Turn the ADC off
    return (ADRESH);            // Return the MSB (upper 8-bits) of the result
}
