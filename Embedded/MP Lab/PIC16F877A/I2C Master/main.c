/*============================================================================*/
/*  
    Project       : I2C Master Driver
    Pic           : Dao Thuan
    Kickoff date  : Feb 22, 2024
    Version       : 1.0
    Description   : Use PIC18F4431 - Internal Quartz 8MHz
                  : I2C Master Driver
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
void I2C_Master_Init(unsigned long baud);
void I2C_Master_Wait();
void I2C_Master_Start();
void I2C_Master_RepeatedStart();
void I2C_Master_Stop();
void I2C_Master_Write(unsigned data);
unsigned short I2C_Master_Read();

/*============================================================================*/

void main()
{
    // PORTB is input
    TRISB = 0xFF;
    // PORTD is output
    TRISD = 0;
    // Turn off led
    PORTD = 1;
    // Baud rate 100kHz
    I2C_Master_Init(100000);
    while(1)
    {
        // Start condition
        I2C_Master_Start();
        // Send 7 bit address + 1 bit Write
        I2C_Master_Write(0x20);
        // Send data
        I2C_Master_Write(PORTB);
        // Stop condition
        I2C_Master_Stop();
        __delay_ms(100);

        // Start condition
        I2C_Master_Start();
        // Send 7 bit address + 1 bit Read
        I2C_Master_Write(0x21);
        // Read data with ACK=0
        PORTD = I2C_Master_Read();
        // Stop condition
        I2C_Master_Stop();
        __delay_ms(1000);
    }
}
void I2C_Master_Init(unsigned long baud)
{
    // Enable I2C, Set I2C Master mode
    SSPCON = 0b00101000;
    SSPCON2 = 0;
    // Setting Clock Speed
    SSPADD = (_XTAL_FREQ/(4*baud)) - 1;
    SSPSTAT = 0;
    // Setting as input
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;
}

void I2C_Master_Wait()
{
    // Transmit/ Receive is in progress
    while((SSPSTATbits.R_W) || (SSPCON2 & 0x1F));
}

void I2C_Master_Start()
{
    I2C_Master_Wait();
    // Initiate start condition
    SSPCON2bits.SEN = 1;
}

void I2C_Master_RepeatedStart()
{
    I2C_Master_Wait();
    // Initiate repeated start condition
    SSPCON2bits.RSEN = 1;
}

void I2C_Master_Stop()
{
    I2C_Master_Wait();
    // Initiate stop condition
    SSPCON2bits.PEN = 1;
}

void I2C_Master_Write(unsigned data)
{
    I2C_Master_Wait();
    // Write data to SSPBUF
    SSPBUF = data;
}

unsigned short I2C_Master_Read()
{
    unsigned short temp;
    I2C_Master_Wait();
    // Receive enable
    SSPCON2bits.RCEN = 1;
    I2C_Master_Wait();
    // Read data from buffer
    temp = SSPBUF;
    I2C_Master_Wait();
    // Acknowledge sequence
    SSPCON2bits.ACKEN = 1;
    return temp;
}