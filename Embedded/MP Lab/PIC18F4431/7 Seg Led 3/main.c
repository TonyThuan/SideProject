/*============================================================================*/
/*  
    Project       : Led Controller
    Pic           : Dao Thuan
    Kickoff date  : Feb 22, 2024
    Version       : 1.0
    Description   : Use PIC18F4431 - External Quartz 20MHz
                  : Led is controlled by PORTB
                  : Negative pole of LED is connected with GND
                  : RB0-RB7 are Output pin
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
        //TITLE       "Led Controller"
        //PROCESSOR   P18F4431
        //INCLUDE     <P18F4431.inc>

// PIC18F4431 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = IRC        // Oscillator Selection bits (Internal oscillator block, CLKO function on RA6 and port function on RA7)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)
#pragma config IESO = ON        // Internal External Oscillator Switchover bit (Internal External Switchover mode enabled)

// CONFIG2L
#pragma config PWRTEN = OFF     // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bits (Brown-out Reset enabled)
// BORV = No Setting

// CONFIG2H
#pragma config WDTEN = ON       // Watchdog Timer Enable bit (WDT enabled)
#pragma config WDPS = 32768     // Watchdog Timer Postscale Select bits (1:32768)
#pragma config WINEN = OFF      // Watchdog Timer Window Enable bit (WDT window disabled)

// CONFIG3L
#pragma config PWMPIN = OFF     // PWM output pins Reset state control (PWM outputs disabled upon Reset (default))
#pragma config LPOL = HIGH      // Low-Side Transistors Polarity (PWM0, 2, 4 and 6 are active-high)
#pragma config HPOL = HIGH      // High-Side Transistors Polarity (PWM1, 3, 5 and 7 are active-high)
#pragma config T1OSCMX = ON     // Timer1 Oscillator MUX (Low-power Timer1 operation when microcontroller is in Sleep mode)

// CONFIG3H
#pragma config FLTAMX = RC1     // FLTA MUX bit (FLTA input is multiplexed with RC1)
#pragma config SSPMX = RC7      // SSP I/O MUX bit (SCK/SCL clocks and SDA/SDI data are multiplexed with RC5 and RC4, respectively. SDO output is multiplexed with RC7.)
#pragma config PWM4MX = RB5     // PWM4 MUX bit (PWM4 output is multiplexed with RB5)
#pragma config EXCLKMX = RC3    // TMR0/T5CKI External clock MUX bit (TMR0/T5CKI external clock input is multiplexed with RC3)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (Enabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Low-Voltage ICSP Enable bit (Low-voltage ICSP enabled)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000200-000FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (001000-001FFF) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (002000-002FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (003000-003FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot Block (000000-0001FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000200-000FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (001000-001FFF) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (002000-002FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (003000-003FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0001FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000200-000FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (001000-001FFF) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (002000-002FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (003000-003FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0001FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
/*----------------------------------------------------------------------------*/
#define _XTAL_FREQ 8000000
/*----------------------------------------------------------------------------*/
#include <xc.h>
/*----------------------------------------------------------------------------*/
unsigned char symbol[11] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 
                            0x7F, 0x6F, 0xFF};
unsigned long data1, data2, data3, data4;
unsigned long serialNum = 0;

void converCounter(unsigned long data);
/*============================================================================*/

void main(void)
{
    unsigned long count = 0;
    int i = 0;
    
    TRISB = 0;
    // Enable IC
    PORTBbits.RB3 = 1;
    __delay_ms(100);
    PORTBbits.RB3 = 0;
    while(1)
    {
        converCounter(count);
        for(i = 0; i < 32; i++)
        {
            if((serialNum & 0x8000000) == 0)
                PORTBbits.RB1 = 0;
            else PORTBbits.RB1 = 1;
            serialNum <<= 1;
            __delay_ms(5);
            //Write data bit into IC register
            PORTBbits.RB0 = 0;
            __delay_ms(5);
            PORTBbits.RB0 = 1;
        }
        //Write Latch and display to LED 7 Segment
        PORTBbits.RB2 = 0;
        __delay_ms(5);
        PORTBbits.RB2 = 1;
        
        __delay_ms(100);
        if(count == 1001)
            count = 0;
        count++;
    }
    return;
}

void converCounter(unsigned long data)
{
    data1 = symbol[data%10];
    
    data/=10;
    data2 = symbol[data%10];
    
    data/=10;
    data3 = symbol[data%10];
    
    data/=10;
    data4 = symbol[data%10];
    
    serialNum = (data4 << 24) || (data3 << 16) || (data2 << 8) | data;
}
