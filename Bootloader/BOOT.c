#include "MKL46Z4.h"
#include "stdbool.h"
#include "stdlib.h"
#include "stdint.h"
#include "UART0_Init.h"
#include "Queue.h"
#include "Flash.h"
#include "Parse_srec.h"
#include "BOOT.h"
#include "intrinsics.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef void (*function) (void);
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
function JumpToApp;
/*******************************************************************************
 * Code
 ******************************************************************************/
uint32_t get_erase_sector()/*find sector to erase*/
{
    uint32_t erase_Sector;

    if((ADDRESS_END_OF_APP - ADDRESS_START_OF_APP) % SECTOR_SIZE == 0)
    {
        erase_Sector = (ADDRESS_END_OF_APP - ADDRESS_START_OF_APP)/SECTOR_SIZE;
    }
    else 
    {
        erase_Sector = (ADDRESS_END_OF_APP - ADDRESS_START_OF_APP)/SECTOR_SIZE +1;
    }
    return erase_Sector;
}

void jump_To_Boot()/*run boot loader*/
{
    uint8_t* getData = NULL;
    parse_data_struct_t output;
    parse_status_t status;
    uint32_t erase_Sector;
    UART0_Puts("Run Boot!\n");
    erase_Sector = get_erase_sector();
    Erase_Multi_Sector(ADDRESS_START_OF_APP, erase_Sector);/*erase multi sector*/
    UART0_Puts("Send srec file!\n");
    while(true) 
    {
        if(queue_getData(&getData))
        {
            status = parse_srec(getData, &output);
            queue_get();
            if(getData[1] != '0')
            {
                if(stt_error == status)
                {
                    UART0_Puts("file error!\n");
                    break;
                }
                else
                {
                    __disable_interrupt();
                    for (uint8_t i = 0; i < output.dataLength; i += 4)/*write address and data into Flash*/
                    {
                        Program_LongWord_8B(output.address + i, output.data + i);
                    }
                    __enable_interrupt();
                    UART0_Puts(">");
                    if(stt_done == status) 
                    {
                        UART0_Puts("\nUpdate Firmware success!\n");
                        break;
                    }
                }
            }
        }
    }
}

void jump_To_App()/*run app*/
{
    __disable_interrupt();
    static uint32_t App_Address;
    App_Address = *(uint32_t*)(ADDRESS_START_OF_APP + 4);/*get app start address*/
    JumpToApp = (function) App_Address;
    __set_MSP(*(uint32_t*) ADDRESS_START_OF_APP);/*Set stack point*/
    JumpToApp();/*executed app program*/
}