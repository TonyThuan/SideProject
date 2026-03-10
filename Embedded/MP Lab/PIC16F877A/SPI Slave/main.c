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
typedef enum
{
    // Enable serial port
    SPI_MASTER_OSC_DIV4 = 0x20,  // Master mode, clock = Fosc/4
    SPI_MASTER_OSC_DIV16 = 0x21, // Master mode, clock = Fosc/16
    SPI_MASTER_OSC_DIV64 = 0x22, // Master mode, clock = Fosc/64
    SPI_MASTER_TMR2     = 0x23,  // Master mode, clock = timer 2 output / 2
    SPI_SLAVE_SS_EN     = 0x24,  // Slave mode, enable SS pin control
    SPI_SLAVE_SS_DIS    = 0x25   // Slave mode, disable SS pin control
} SPI_Type;

typedef enum
{
    SPI_DATA_SAMPLE_MIDDLE = 0b00000000,  // Input data sample at middle of data output time
    SPI_DATA_SAMPLE_END   = 0b10000000    // Input data sample at end of data output time
} SPI_DataSample;  // Sample time

typedef enum
{
    SPI_CLOCK_IDLE_HIGH = 0b00001000,  // Idle state for clock í a high level
    SPI_CLOCK_IDLE_LOW = 0b00000000    // Idle state for clock í a low level
} SPI_ClockIdle; // Idle status

typedef enum
{
 SPI_IDLE_2_ACTIVE = 0b00000000,  // Idle to active
 SPI_ACTIVE_2_IDLE = 0b01000000   // Active to idle
} SPI_TransmitEdge; // Transmit edge
/*============================================================================*/

/*============================================================================*/

void __interrupt() SPI_Slave_Read();
unsigned char SPI_Read();
void SPI_sendData(char data);
static void SPI_ReceiveAndWait();
void SPI_Init(SPI_Type sType, SPI_DataSample sDataSample,
        SPI_ClockIdle sClockIdle, SPI_TransmitEdge sTransmitEdge);

void main(void)
{
    TRISB = 0xFF;
    TRISD = 0x00;
    PORTD = 0x00;
    // Enable global interrupt
    INTCONbits.GIE = 1;
    // Enable peripheral interrupt
    INTCONbits.PEIE = 1;
    // Clear SSP interrupt flag
    PIR1bits.SSPIF = 0;
    // Enable Synchronous Serial Port interrupt
    PIE1bits.SSPIE = 1;
    ADCON1 = 0;
    // Slave select
    TRISA5 = 1;
    SPI_Init(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW,
            SPI_IDLE_2_ACTIVE);
    while(1)
    {
    }
    
}

void SPI_Init(SPI_Type sType, SPI_DataSample sDataSample,
        SPI_ClockIdle sClockIdle, SPI_TransmitEdge sTransmitEdge)
{
    TRISC5 = 0; // Serial Data Output
    if(sType & 0x04)  // If Slave mode
    {
        SSPSTAT = sTransmitEdge;
        TRISC3 = 1;  // Serial Clock
    } else  // If Master mode
    {
        SSPSTAT = sDataSample | sTransmitEdge;
        TRISC3 = 0;  // Serial Clock
    }
    SSPCON = sType | sClockIdle;
}

void __interrupt() SPI_Slave_Read()
{
    if(SSPIF == 1)
    {
        PORTD = SPI_Read();
        SPI_sendData(PORTB);
        PIR1bits.SSPIF = 0;
    }
}

static void SPI_ReceiveAndWait()
{
    while(!SSPSTATbits.BF); // Check receive complete
}

unsigned char SPI_Read()
{
    SPI_ReceiveAndWait();
    return SSPBUF;
}

void SPI_sendData(char data)
{
    SSPBUF = data;
}