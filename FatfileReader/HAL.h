#ifndef _HAL_H_
#define _HAL_H_

#include <stdio.h>
#include <stdint.h>
#include "read_file.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXIT_FAIL 0
#define OFFSET_BPB_BytsPerSec      0x0B
/*******************************************************************************
 * API
 ******************************************************************************/

void kmc_open_file();

void kmc_close_file();

void bytes_per_sector();

/*!
 * @brief <Mo ta chuc nang cua ham>
 *
 * @param var3 <Mo ta muc dich cua var3>.
 * @param var4 <Mo ta muc dich cua var4>.
 *
 * @return <Mo ta cac gia tri tra ve>.
 */
int32_t kmc_read_sector(uint32_t index, uint8_t *buff);

int16_t kmc_read_entry(uint32_t sector_index, uint16_t entry_index, uint8_t *buff);

uint8_t kmc_read_FAT(uint16_t rsvd_sec_cnt, uint16_t staring_cluster, uint8_t * buff);

int32_t kmc_read_multi_sector(uint32_t index, uint32_t num, uint8_t *buff);

#endif /* _HAL_H_ */
