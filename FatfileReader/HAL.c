#include "HAL.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
FILE *g_fp = NULL;
uint16_t   g_bytes_per_sector;

/*******************************************************************************
 * Code
 ******************************************************************************/

void kmc_open_file()
{
    uint8_t image_file_name[12];

    do
    {
        printf("Enter image file's name: ");
        gets(image_file_name);
        fflush(stdin);
        g_fp = fopen(image_file_name, "rb");
    }
    while(NULL == g_fp);
}

void kmc_close_file()
{
    fclose(g_fp);
}

void bytes_per_sector()
{
    if(fseek(g_fp, OFFSET_BPB_BytsPerSec, SEEK_SET))
    {
        puts("Seeking file is failed. ");
        return;
    }
    if((fread(&g_bytes_per_sector, sizeof(uint16_t), 1, g_fp) < sizeof(uint16_t)) && (!EOF))
    {
        puts("Reading file is failed.");
        return;
    }
}

int32_t kmc_read_sector(uint32_t index, uint8_t *buff)
{
    int32_t return_value = 0;

    if(fseek(g_fp, index * g_bytes_per_sector, SEEK_SET))
    {
        puts("Seeking file is failed. ");
    }
    return_value = fread(buff, sizeof(uint8_t), g_bytes_per_sector, g_fp);
    if((return_value < g_bytes_per_sector) && (!EOF))
    {
        puts("Reading file is failed.");
    }
    return return_value;
}

int16_t kmc_read_entry(uint32_t sector_index, uint16_t entry_index, uint8_t *buff)
{
    int16_t return_value = 0;
    
    if(fseek(g_fp, sector_index * g_bytes_per_sector + entry_index * BYTES_PER_ENTRY, SEEK_SET))
    {
        puts("Seeking file is failed.");
    }
    return_value = fread(buff, sizeof(uint8_t), BYTES_PER_ENTRY, g_fp);
    if((return_value < BYTES_PER_ENTRY) && (!EOF))
    {
        puts("Reading file is failed.");
    }
    return return_value;
}

int32_t kmc_read_multi_sector(uint32_t index, uint32_t num, uint8_t *buff)
{
    int32_t return_value = 0;

    if(fseek(g_fp, index * g_bytes_per_sector * num, SEEK_SET))
    {
        puts("Seeking file is failed. ");
    }
    return_value = fread(buff, sizeof(uint8_t), g_bytes_per_sector, g_fp);
    if((return_value < g_bytes_per_sector * num) && (!EOF))
    {
        puts("Reading file is failed.");
    }
    return return_value;
}

uint8_t kmc_read_FAT(uint16_t rsvd_sec_cnt, uint16_t staring_cluster, uint8_t *buff)
{
    uint32_t offset = 0;
    uint8_t return_value = 0;
    if(staring_cluster % 2 == 0)
    {
        offset = rsvd_sec_cnt * g_bytes_per_sector + staring_cluster * 1.5;
    }
    else
    {
        offset = rsvd_sec_cnt * g_bytes_per_sector + (staring_cluster - 1) * 1.5 + 1;
    }
    if(fseek(g_fp, offset, SEEK_SET))
    {
        puts("Seeking file is failed. ");
    }
    return_value = fread(buff, sizeof(uint8_t), 2, g_fp);
    if((return_value < 2) && (!EOF))
    {
        puts("Reading file is failed.");
    }

    return return_value;
}

