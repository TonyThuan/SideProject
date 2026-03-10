#ifndef _UART0_Init_H_
#define _UART0_Init_H_


/*******************************************************************************
* Definitions
*******************************************************************************/
#define MAX(A,B)         ((A)>(B)? (A-B) : (B-A))
/*******************************************************************************
* Function
*******************************************************************************/

/*
 * @brief send character
 * @param data is character input
*/
void UART0_Putc(uint8_t data);

/*
 * @brief send string
 * @param str is pointer to char
*/
void UART0_Puts(uint8_t *str);

/*
 * @brief config UART0
 * @param baudRate is desire baudrate
 * @param clock is source clock
*/
void UART0_init(uint32_t baudRate, uint32_t clock);

/*
 * @brief UART0 interrupt handler
*/
void UART0_IRQHandler();

#endif /* _UART0_H_ */