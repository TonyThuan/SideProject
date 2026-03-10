#ifndef _Parse_srec_H_
#define _Parse_srec_H_

#include "stdlib.h"
#include "stdbool.h"
#include "Queue.h"
#include "UART0_Init.h"

/*******************************************************************************
* Definitions
*******************************************************************************/
#define CHECK_SUM_SIZE          1
#define RECORD_TYPE_LENGTH      2
#define BYTE_COUNT_LENGTH       2
/*******************************************************************************
 * Typedef
 ******************************************************************************/
typedef enum
{
    stt_done        = 0x00U,
    stt_parsing  = 0x01U,
    stt_error       = 0xFFU,
} parse_status_t;

typedef struct
{
    uint32_t address;
    uint8_t data[MAX_DATA_SREC_SIZE];
    uint8_t dataLength;
} parse_data_struct_t;
/*******************************************************************************
* Function
*******************************************************************************/

/*
 * @brief check srec line
 * @param input_data is pointer to line
*/
bool srec_check(uint8_t* input_data);

/*
 * @brief get parsing status
 * @param input_data is pointer to line
 * @param output_data is struct pointer
*/
parse_status_t parse_srec(uint8_t* input_data, parse_data_struct_t* output_data);

/*
 * @brief check the checksum value
 * @param input_data is input line
 * @param length is length of data needed to check
*/
bool checksum(uint8_t* input_data, uint8_t length);

/*
 * @brief convert hex to dec
 * @param hex is number need to convert
*/
uint8_t convert_Hex(uint8_t hex);

#endif /* _Parse_srec__H_ */