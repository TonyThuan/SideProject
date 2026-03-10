#include <stdio.h>
#include <stdint.h>
#include "HAL.h"
#include "read_file.h"
#include "display.h"
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

int main()
{
    uint32_t head = 0;
    uint8_t num_file_folder;
    uint32_t choose;

    kmc_open_file();
    bytes_per_sector();
    init_boot_sector();

    while(1)
    {
        puts("-----------------------------------------------------------------");
        puts("ROOT DIRECTORY:");
    
        num_file_folder = init_root_directory(&head);
    
        choose = get_choose(num_file_folder);
        if(choose == 0)
        {
            return;
        }
    
        while(1)
        {
            num_file_folder = read_file_folder(&head, choose);
        
            choose = get_choose(num_file_folder);
        
            if(choose == 0)
            {
                if((g_file_folder.parent_cluster == 0) && (g_file_folder.starting_cluster == 0))
                {
                    return;
                }
                else if(g_file_folder.parent_cluster == 0)
                {
                    break;
                }
            }
        }
    }

    kmc_close_file();

    return 0;
}
