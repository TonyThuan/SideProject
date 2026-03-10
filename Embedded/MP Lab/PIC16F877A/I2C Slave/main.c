/*============================================================================*/
/*  
    Project       : I2C Slave Driver
    Pic           : Dao Thuan
    Kickoff date  : Feb 22, 2024
    Version       : 1.0
    Description   : Use PIC18F4431 - Internal Quartz 8MHz
                  : I2C Slave Driver
*/
/*----------------------------------------------------------------------------*/
/*
    Finish date   :
    Check date    :
    Tester        : Dao Thuan
*/
/*----------------------------------------------------------------------------*/
/*
    Note          :
*/
/*============================================================================*/

/*============================================================================*/
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
/*----------------------------------------------------------------------------*/
#define _XTAL_FREQ 20000000
/*----------------------------------------------------------------------------*/
#include <xc.h>
/*----------------------------------------------------------------------------*/

/*============================================================================*/

short z;
void I2C_Slave_Init(short address);
void __interrupt()  I2C_Slave_Read();
/*============================================================================*/

void main(void)
{
    // PORTB is input
    TRISB = 0xFF;
    // PORTD is output
    TRISD = 0;
    // Turn off LED
    PORTD = 0;
    // Init slave with address 0x20
    I2C_Slave_Init(0x20);
    while(1);
    return;
}

void I2C_Slave_Init(short address)
{
    // Slew rate control disabled for standard speed mode (100 kHz and 1 MHz)
    SSPSTAT = 0x80;
    // Setting slave address
    SSPADD = address;
    // Enable the serial port, Release clock
    // Set slave mode, 7-bit address
    SSPCON = 0x36;
    // Enable clock stretching for both slave transmit & receive
    SSPCON2 = 0x01;
    // Setting Pin C3,4 as input
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;
    // Enable global interrupt
    INTCONbits.GIE = 1;
    // Enable peripheral interrupt
    INTCONbits.PEIE = 1;
    // Clear SSP interrupt flag
    PIR1bits.SSPIF = 0;
    // Enable Synchronous Serial Port interrupt
    PIE1bits.SSPIE = 1;
}

void __interrupt()  I2C_Slave_Read()
{
    // Check Receive/Transmit interrupt flag
    if(PIR1bits.SSPIF == 1)
    {
        // Holds clock low (clock stretch), used to ensure data setup time
        SSPCONbits.CKP = 0;
        // If Overflow data or Collision data
        if((SSPCONbits.SSPOV) || (SSPCONbits.WCOL))
        {
            // Read value before deleting buffer
            z = SSPBUF;
            // Delete overflow indicator bit
            SSPCONbits.SSPOV = 0;
            // Delete collision detect bit
            SSPCONbits.WCOL = 0;
            // Release clock
            SSPCONbits.CKP = 1;
        }
        // Receive data from master and write to PORTD
        // Check the last byte received was address and Write mode
        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW)
        {
            z = SSPBUF;
            // Check Receive is not complete
            while(!SSPSTATbits.BF);
            PORTD = SSPBUF;
            SSPCONbits.CKP = 1;
        }
        // Write data PORTB to transfer to master
        // Check the last byte received was address and Read mode
        else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW)
        {
            z = SSPBUF;
            SSPSTATbits.BF = 0;
            SSPBUF = PORTB;
            SSPCONbits.CKP = 1;
            // Check the transmit in progress
            while(SSPSTATbits.BF);
        }
        PIR1bits.SSPIF = 0;
    }
}