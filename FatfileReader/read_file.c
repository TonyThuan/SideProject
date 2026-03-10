#include "read_file.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint16_t   g_bytes_per_sector;
uint8_t    g_sectors_per_cluster;
uint16_t   g_rsvd_sec_cnt;
uint8_t    g_number_FATs;
uint16_t   g_entries_per_RDET;
uint16_t   g_sectors_per_FAT;
uint32_t   g_first_RDET_sector;
uint8_t    g_main_entry[MAX_DIRECTORY];
directory_t g_file_folder;

/*******************************************************************************
 * Code
 ******************************************************************************/
void init_boot_sector()
{
    uint8_t buff[512];
    kmc_read_sector(0, buff);
    g_bytes_per_sector    = (buff[OFFSET_BPB_BytsPerSec + 1] << 8) | buff[OFFSET_BPB_BytsPerSec];
    g_sectors_per_cluster = buff[OFFSET_BPB_BPB_SecPerClus];
    g_rsvd_sec_cnt        = (buff[OFFSET_BPB_RsvdSecCnt + 1] << 8) | buff[OFFSET_BPB_RsvdSecCnt];
    g_number_FATs         = buff[OFFSET_BPB_NumFATs];
    g_entries_per_RDET    = (buff[OFFSET_BPB_RootEntCnt + 1] << 8) | buff[OFFSET_BPB_RootEntCnt];
    g_sectors_per_FAT     = (buff[OFFSET_BPB_FATSz16 + 1] << 8) | buff[OFFSET_BPB_FATSz16];
}

uint32_t init_root_directory(uint32_t *head)
{
    uint8_t buff[BYTES_PER_ENTRY];
    int8_t sector_per_RDET = g_entries_per_RDET * BYTES_PER_ENTRY / g_bytes_per_sector;
    uint16_t i;
    uint8_t index_file_folder = 0;

    g_first_RDET_sector = g_rsvd_sec_cnt + g_number_FATs * g_sectors_per_FAT;
    *head = g_first_RDET_sector;
    
    puts("0. Exit");
    for(i = 0; i < g_entries_per_RDET; i++)
    {
        kmc_read_entry(g_first_RDET_sector, i, buff);
        if(buff[OFFSET_DIR_Name] == EMPTY_ENTRY)
        {
            break;
        }
        if((buff[OFFSET_DIR_Name] != REMOVED_ENTRY) && (buff[OFFSET_DIR_Attr] != ATTR_SUB_ENTRY))
        {
            uint8_t j;

            g_main_entry[index_file_folder] = i;
            index_file_folder = index_file_folder + 1;

            for(j = 0; j < 8; j++)
            {
                g_file_folder.short_name[OFFSET_DIR_Name + j] = buff[OFFSET_DIR_Name + j];
            }

            if(buff[OFFSET_DIR_Attr] == ATTR_DIRECTORY)
            {
                for(j = 8; j < OFFSET_DIR_Attr; j++)
                {
                    g_file_folder.short_name[OFFSET_DIR_Name + j] = ' ';
                }
                g_file_folder.short_name[OFFSET_DIR_Name + j] = '\0';
            }
            else
            {
                g_file_folder.short_name[OFFSET_DIR_Name + 8] = '.';
                for(j = 9; j < 12; j++)
                {
                    g_file_folder.short_name[OFFSET_DIR_Name + j] = buff[OFFSET_DIR_Name + j - 1];
                }
                g_file_folder.short_name[OFFSET_DIR_Name + j] = '\0';
            }

            printf("%d. %s\n", index_file_folder, g_file_folder.short_name);
        }
    }
    g_file_folder.starting_cluster = 0;
    g_file_folder.parent_cluster = 0;
    
    return index_file_folder;
}

uint32_t read_FAT_element(uint8_t *FAT_element, uint32_t element_index)
{
    uint32_t next_cluster = 0;
    /* FAT 12 */
    if((element_index % 2) == 0)
    {
        next_cluster = FAT_element[0] | ((FAT_element[1] & 0x0F) << 12);
    }
    else
    {
        next_cluster = ((FAT_element[0] & 0xF0) >> 4) | (FAT_element[1] << 4);
    }
    return next_cluster;
}

void read_file()
{
    uint32_t offset = 0;
    uint8_t buff[g_bytes_per_sector * g_sectors_per_cluster];
    uint32_t i;
    uint8_t FAT_element[2];
    uint32_t current_cluster = 0;
    uint32_t next_cluster = g_file_folder.starting_cluster;

    offset = g_rsvd_sec_cnt + g_number_FATs * g_sectors_per_FAT
             + g_entries_per_RDET * BYTES_PER_ENTRY / g_bytes_per_sector;
    kmc_read_multi_sector(offset + g_file_folder.starting_cluster - 2, g_sectors_per_cluster, buff);

    puts("0. Back");
    printf("%s:\n", g_file_folder.short_name);
    for(i = 0; i < g_bytes_per_sector * g_sectors_per_cluster; i++)
    {
        if(buff[i] != 0x07)
        {
            printf("%c", buff[i]);
        }
    }
    while(1)
    {
        current_cluster = next_cluster;
        uint8_t buffer[g_bytes_per_sector * g_sectors_per_cluster];
        kmc_read_FAT(g_rsvd_sec_cnt, g_file_folder.starting_cluster, FAT_element);
        next_cluster = read_FAT_element(FAT_element, current_cluster);
        if(next_cluster > 0xFEF)
        {
            break;
        }
        /* print content of file */
        kmc_read_multi_sector(offset + next_cluster, g_sectors_per_cluster, buffer);
        for(i = 0; i < g_bytes_per_sector * g_sectors_per_cluster; i++)
        {
            if(buff[i] != 0x07)
            {
                printf("%c", buff[i]);
            }
            if(buff[i] == EOF)
            {
                break;
            }
        }
        printf("\n");
    }
}

uint32_t read_folder()
{
    uint8_t buff[BYTES_PER_ENTRY];
    uint16_t i;
    uint8_t index_file_folder = 0;
    uint32_t offset;

    offset = g_rsvd_sec_cnt + g_number_FATs * g_sectors_per_FAT
             + g_entries_per_RDET * BYTES_PER_ENTRY / g_bytes_per_sector;

    puts("0. Exit");
    for(i = 2; i < g_bytes_per_sector / BYTES_PER_ENTRY; i++)
    {
        kmc_read_entry(offset +  g_file_folder.starting_cluster - 2, i, buff);
        if(buff[OFFSET_DIR_Name] == EMPTY_ENTRY)
        {
            break;
        }
        if((buff[OFFSET_DIR_Name] != REMOVED_ENTRY) && (buff[OFFSET_DIR_Attr] != ATTR_SUB_ENTRY))
        {
            uint8_t j;

            g_main_entry[index_file_folder] = i;
            index_file_folder = index_file_folder + 1;

            for(j = 0; j < 8; j++)
            {
                g_file_folder.short_name[OFFSET_DIR_Name + j] = buff[OFFSET_DIR_Name + j];
            }

            if(buff[OFFSET_DIR_Attr] == ATTR_DIRECTORY)
            {
                for(j = 8; j < OFFSET_DIR_Attr; j++)
                {
                    g_file_folder.short_name[OFFSET_DIR_Name + j] = ' ';
                }
                g_file_folder.short_name[OFFSET_DIR_Name + j] = '\0';
            }
            else
            {
                g_file_folder.short_name[OFFSET_DIR_Name + 8] = '.';
                for(j = 9; j < 12; j++)
                {
                    g_file_folder.short_name[OFFSET_DIR_Name + j] = buff[OFFSET_DIR_Name + j - 1];
                }
                g_file_folder.short_name[OFFSET_DIR_Name + j] = '\0';
            }

            printf("%d. %s\n", index_file_folder, g_file_folder.short_name);
        }
    }

    return index_file_folder;
}

uint32_t read_file_folder(uint32_t *head, uint8_t choose)
{
    uint8_t buff[BYTES_PER_ENTRY];
    uint8_t i;
    uint32_t index_file_folder = 0;

    kmc_read_entry(*head, g_main_entry[choose - 1], buff);
    
    for(i = 0; i < 8; i++)
    {
        g_file_folder.short_name[i] = buff[i];
    }
    g_file_folder.short_name[i] = '.';
    for(i = 9; i < 12; i++)
    {
        g_file_folder.short_name[i] = buff[i-1];
    }
    g_file_folder.short_name[i] = '\0';
    g_file_folder.parent_cluster = g_file_folder.starting_cluster;
    g_file_folder.starting_cluster = (buff[OFFSET_DIR_FstClusHI + 1] << 24) | (buff[OFFSET_DIR_FstClusHI] << 16)
                                    | (buff[OFFSET_DIR_FstClusLO + 1] << 8) | buff[OFFSET_DIR_FstClusLO];

    if(buff[OFFSET_DIR_Attr] == ATTR_DIRECTORY)
    {
        *head = g_rsvd_sec_cnt + g_number_FATs * g_sectors_per_FAT
             + g_entries_per_RDET * BYTES_PER_ENTRY / g_bytes_per_sector + g_file_folder.starting_cluster - 2;
        index_file_folder = read_folder();
    }
    else
    {
        read_file();
    }
    
    return index_file_folder;
}

