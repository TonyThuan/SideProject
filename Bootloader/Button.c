#include "Button.h"
#include "stdbool.h"
#include "Queue.h"
#include "BOOT.h"
#include "UART0_Init.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
void Butotn_Init(void)/*config for button*/
{
  SIM->SCGC5 |= (1 << 11);
  PORTC->PCR[3] |= PORT_PCR_MUX(1);
  GPIOC->PDDR &= ~SW1_MASK;
  PORTC->PCR[3] |= PULL_UP_MASK;
}

void Execute()
{
    if(((GPIOC->PDIR >> 3) & 0x01) == 0)/*press SW1 and reset to go to boot*/
    {
        /* wait user release button */
        while(((GPIOC->PDIR >> 3) & 0x01) == 0)
        queue_init();
        UART0_init(9600, SystemCoreClock);
        jump_To_Boot();
    }
    else/*go to application*/
    {
        SCB->VTOR = 0xA000;
        jump_To_App();
    }
}