#include "MKL46Z4.h"
#include "Parse_srec.h"
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
bool srec_check(uint8_t* input_data)/*verify srec data line*/
{
    bool ret;
    char buff[4];
    uint8_t i = 0;
    uint8_t byte_count = 0;

    if(input_data[0] == 'S')/*check first character*/
    {
        if(('4' == input_data[1]) || ('0' > input_data[1]) || ('9' < input_data[1]))
        {
            ret = false;
        }
        else
        {
            for(i = 0; i < 2; i++)
            {
                buff[i] = input_data[i+2];
            }

            byte_count = strtol(buff, NULL, 16);/*convert to number*/

            if(checksum(input_data, byte_count))
            {
                ret = true;
            }
            else
            {
                ret = false;
            }
        }
    }
    return ret;
}

parse_status_t parse_srec(uint8_t* input_data, parse_data_struct_t* output_data)
{
    parse_status_t status;
    uint8_t address_size = 0;
    uint8_t type = 0;
    uint8_t add_offset = 4;
    uint8_t data_offset;
    uint32_t tempAddress = 0;
    uint8_t tempData = 0;
    uint8_t byte_count = 0;

    output_data->address = 0;
    output_data->dataLength = 0;

    if(srec_check(input_data) == true)
    {
        type = input_data[1] - 0x30;
        switch(type)
        {
            case 0:
            {
                address_size = 2u;/*2byte address*/
                status = stt_parsing;
                break;
            }
            case 1:
            case 2:
            case 3:
            {
                address_size = type + 1;/*S1/S2/S3 -> 2byte/3byte/4byte address*/
                status = stt_parsing;
                break;
            }
            case 7:
            case 8:
            case 9:
            {
                address_size = 11 - type;/* S7/S8/S9 -> 2byte/3byte/4byte address*/
                status = stt_done;
                break;
            }
            default:
            {
                status = stt_error;
                break;
            }
        }
        byte_count = (convert_Hex(input_data[2])<<4 | convert_Hex(input_data[3]));/*convert byte count*/

        output_data->dataLength = byte_count - address_size - CHECK_SUM_SIZE;/*get data length*/

        for(uint8_t i = 0; i < address_size; i++)/*get address*/
        {
            tempAddress = (tempAddress << 8) | ((convert_Hex(input_data[add_offset])<<4)|(convert_Hex(input_data[add_offset+1])));
            add_offset+=2;
        }
        output_data->address = tempAddress;

        data_offset = add_offset;/*get data*/
        for(uint8_t i = 0; i < output_data->dataLength; i++)
        {
            tempData = 0;
            tempData = (convert_Hex(input_data[data_offset]) << 4) | (convert_Hex(input_data[data_offset+1]));
            output_data->data[i] = tempData;
            data_offset += 2;
        }
        return status;
    }
    else
    {
        status = stt_error;
        return status;
    }
}

bool checksum(uint8_t* input_data, uint8_t length)/*check checksum*/
{
    bool ret;
    uint16_t sum = 0;
    uint8_t val = 0;

    for(uint8_t i = 2; i <= length*2 + 2; i+=2)
    {
        val = (convert_Hex(input_data[i])<<4) | (convert_Hex(input_data[i+1]));
        sum += val;
    }
    sum = sum&0xFF;
    if(sum == 0xFF)
    {
        ret = true;
    }
    else
    {
        ret = false;
    }
    return ret;
}

uint8_t convert_Hex(uint8_t hex)/*convert hex to dec*/
{
    uint8_t output;
    if((hex >= '0') && (hex <= '9'))/*characters 0-9*/
    {
        output = hex - '0';
    }
    else if((hex >= 'A') && (hex <= 'F'))/*characters A-F*/
    {
        output = hex - 'A' + 10;
    }
    else/*others character*/
    {
        output = 0xFF;
    }
    return output;
}