#include "MKL46Z4.h"
#include "stdbool.h"
#include "stdlib.h"
#include "stdint.h"
#include "UART0_Init.h"
#include "Queue.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t count = 0;
uint8_t *putPtr = NULL;
/*******************************************************************************
 * Code
 ******************************************************************************/
uint8_t UART0_GetChar(void)
{
    /*wait until the flag receive turn on*/
    while (!(UART0->S1 & UART0_S1_RDRF_MASK));
    return UART0->D;
}

void save_queue(uint8_t chr)
{
    static uint8_t index = 0;

    Q_getLine(&putPtr);

    if(chr != 0x00 && chr != 0x0A)
    {
        putPtr[index++] = chr;
    }

    if(chr == 0x0A)
    {
        index = 0;
        queue_put();/*add new queue*/
    }
} 

void UART0_Putc(uint8_t data)/*send character*/
{
    while(!(UART0->S1 & UART0_S1_TDRE_MASK));
    UART0->D = data;
}

void UART0_Puts(uint8_t *str)/*send string*/
{
    while(*str != '\0')
    {
        UART0_Putc(*str++);
    }
}

void UART0_IRQHandler(void)  
{
    uint8_t buff;
    buff = UART0_GetChar();/*receive data*/
    save_queue(buff);/*save queue*/
}

void UART0_init(uint32_t baudRate, uint32_t clock)/*config UART0*/
{
    uint32_t baudrate1 = 0;
    uint32_t baudrate2 = 0;
    uint32_t diff = 0xFFFFFFFF;
    uint16_t tmp_sbr = 0;
    uint8_t tmp_osr = 4;
    uint16_t sbr = 0;
    uint8_t osr = 4;

    while(tmp_osr <= 32)
    {
        tmp_sbr = clock/(baudRate * tmp_osr);/*check each osr*/
        if(0==tmp_sbr)
        {
            tmp_sbr = 1;
        }
        baudrate1 = clock/(tmp_sbr * tmp_osr);/*compare baudrate1 and baudrate2*/
        baudrate2 = clock/((tmp_sbr + 1) * tmp_osr);

        if(diff >= MAX(baudrate1,baudRate))/*find the best value*/
        {
            diff = MAX(baudrate1,baudRate);
            sbr = tmp_sbr;
            osr = tmp_osr;
            if(0 == diff)
            {
                break;
            }
        }

        if(diff >= MAX(baudrate2,baudRate))
        {
            diff = MAX(baudrate2,baudRate);
            sbr = tmp_sbr+1;
            osr = tmp_osr;
            if(0 == diff)
            {
                break;
            }
        }
        tmp_osr ++;
    }

    SIM->SCGC5 |= (1 << 9);/*Enable PORTA clock*/
    SIM->SOPT2 = SIM->SOPT2 &~(1<<26)&~(1<<27);/*clear bit 26,27 of register SOPT2*/
    SIM->SOPT2 |= (1<<26);/*selects the clock source for the UART0*/
    SIM->SCGC4 |= SIM_SCGC4_UART0(1);/*UART0 Clock Gate Control*/

    PORTA->PCR[1] &= ~PORT_PCR_MUX_MASK;/*clear MUX of register PCR*/
    PORTA->PCR[1] |= PORT_PCR_MUX(2);/*configuration pin UART0_RX*/
    PORTA->PCR[2] &= ~PORT_PCR_MUX_MASK;/*clear MUX of register PCR*/
    PORTA->PCR[2] |= PORT_PCR_MUX(2);/*configuration pin UART0_TX */

    UART0->C1 &= ~UART0_C1_M_MASK;/*clear bit M of register C1*/
    UART0->C1 |= UART0_C1_M(0);/*receive and transmit 8 bit*/
    UART0->C4 &= ~UART0_C4_M10_MASK;

    /*TX and RX disabled*/
    UART0->C2 &= ~UART0_C2_RE_MASK;
    UART0->C2 &= ~UART0_C2_TE_MASK;

    /*clear BDH and BDL*/
    UART0->BDH &= ~UART0_BDH_SBR_MASK;
    UART0->BDL &= ~UART0_BDL_SBR_MASK;

    /*Set up BDH and BDL*/
    UART0->BDH =(UART0->BDH & UART0_BDH_SBR_MASK) | (uint8_t)(sbr >> 8);
    UART0->BDL = (uint8_t)sbr;
    UART0->C3 = 0x00;
    UART0->MA2 = 0x00;
    UART0->MA1 = 0x00;
    UART0->C4 &= ~UART0_C4_OSR_MASK;/*clear bits OSR of registers C4*/
    UART0->C4 = UART0_C4_OSR(osr-1);/*set bit OSR of register C4*/
    UART0->C5 = 0x00;

    /*Parity bit*/
    UART0->C1 &= ~UART0_C1_PE_MASK;/*clear bit PE of register C1*/
    UART0->C1 |= UART0_C1_PE(0);/*disable parity bit*/
    UART0->C1 |= UART0_C1_PT(0);/*choose Parity Type*/

    /*TX and RX enable*/
    UART0->C2 |= UART0_C2_RE(1);
    UART0->C2 |= UART0_C2_TE(1);

    /*enable interrupting*/
    UART0->C2 |= UART0_C2_RIE(1);
    UART0->C3 |= UART0_C3_ORIE(1);
    NVIC_EnableIRQ(UART0_IRQn);
}