#ifndef _READ_FILE_H_
#define _READ_FILE_H_

#include <stdio.h>
#include <stdint.h>
#include "HAL.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define BYTES_PER_ENTRY            32
#define EMPTY_ENTRY                0x00
#define REMOVED_ENTRY              0xE5
#define MAX_DIRECTORY              50

/* BOOT SECTOR STRUCTURE */
#define OFFSET_BPB_BytsPerSec      0x0B
#define OFFSET_BPB_BPB_SecPerClus  0x0D
#define OFFSET_BPB_RsvdSecCnt      0x0E
#define OFFSET_BPB_NumFATs         0x10
#define OFFSET_BPB_RootEntCnt      0x11
#define OFFSET_BPB_FATSz16         0x16

/* ROOT DIRECTORY STRUCTURE */
#define OFFSET_DIR_Name            0x00      /* Short name */
#define OFFSET_DIR_Attr            0x0B      /* File Attribute */
    #define ATTR_READ_ONLY         0x01
    #define ATTR_HIDDEN 	       0x02
    #define ATTR_SYSTEM 	       0x04
    #define ATTR_VOLUME_ID 	       0x08
    #define ATTR_DIRECTORY	       0x10
    #define ATTR_ARCHIVE  	       0x20
    #define ATTR_SUB_ENTRY         0x0F
    #define ATTR_END_ROOT          0x00
    #define ATTR_LONG_NAME 	       ATTR_READ_ONLY | ATTR_HIDDEN | ATTR_SYSTEM | ATTR_VOLUME_ID
#define OFFSET_DIR_NTRes           0x0C      /* Reserved for use by Windows NT */
#define OFFSET_DIR_CrtTimeTenth    0x0D      /* Millisecond stamp at file creation time */
#define OFFSET_DIR_CrtTime         0x0E      /* Time file was created */
#define OFFSET_DIR_CrtDate         0x10      /* Date file was created */
#define OFFSET_DIR_LstAccDate      0x12      /* Last access date */
#define OFFSET_DIR_FstClusHI       0x14      /* High word of this entry's first cluster number */
#define OFFSET_DIR_WrtTime         0x16      /* Time of last write */
#define OFFSET_DIR_WrtDate         0x18      /* Date of last write */
#define OFFSET_DIR_FstClusLO       0x1A      /* Low word of this entry's first cluster number */
#define OFFSET_DIR_FileSize        0x1C      /* 32-bit DWORD holding this file's size in bytes */

/*******************************************************************************
 * API
 ******************************************************************************/

typedef struct
{
    uint8_t short_name[13];
    uint32_t starting_cluster;
    uint32_t parent_cluster;
} directory_t;

extern directory_t g_file_folder;

/*!
 * @brief <Mo ta chuc nang cua ham>
 *
 * @param var3 <Mo ta muc dich cua var3>.
 * @param var4 <Mo ta muc dich cua var4>.
 *
 * @return <Mo ta cac gia tri tra ve>.
 */
uint32_t init_root_directory(uint32_t *head);

uint32_t read_file_folder(uint32_t *head, uint8_t choose);

#endif /* _READ_FILE_H_ */
