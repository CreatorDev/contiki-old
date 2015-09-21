/*
 * Copyright (c) 2015, Imagination Technologies Limited and/or its
 * affiliated group companies.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "contiki-conf.h"
#include "dev/flash.h"

#ifndef CFS_COFFEE_ARCH_H_
#define CFS_COFFEE_ARCH_H_

/* Minimum reservation unit for Coffee. It can be changed by the user.  */
#define COFFEE_PAGE_SIZE          (FLASH_PAGE_SIZE/4)

#if (COFFEE_ADDRESS & 0xFFF) != 0
	#error "COFFEE_ADDRESS not aligned to a 4096-bytes page boundary."
#endif

#define COFFEE_PAGES              ((FLASH_PAGES*FLASH_PAGE_SIZE-               \
                 (COFFEE_ADDRESS-FLASH_START))/COFFEE_PAGE_SIZE)
#define COFFEE_START              (COFFEE_ADDRESS & ~(COFFEE_PAGE_SIZE-1))
#define COFFEE_SIZE               (COFFEE_PAGES*COFFEE_PAGE_SIZE)

/* These must agree with the parameters passed to makefsdata */
#define COFFEE_SECTOR_SIZE        FLASH_PAGE_SIZE
#define COFFEE_NAME_LENGTH        20

/* These are used internally by the coffee file system */
#define COFFEE_MAX_OPEN_FILES     4
#define COFFEE_FD_SET_SIZE        8
#define COFFEE_DYN_SIZE           (COFFEE_PAGE_SIZE*1)
/* Micro logs are not needed for single page sectors */
#define COFFEE_MICRO_LOGS         0
#define COFFEE_LOG_TABLE_LIMIT    16    /* It doesnt' matter as */
#define COFFEE_LOG_SIZE           128   /* COFFEE_MICRO_LOGS is 0. */

#if COFFEE_PAGES <= 127
#define coffee_page_t int8_t
#elif COFFEE_PAGES <= 0x7FFF
#define coffee_page_t int16_t
#endif

void pic32_flash_erase(coffee_page_t sector);
void pic32_flash_write(uint32_t address, const void * data, uint32_t len);

#define COFFEE_WRITE(buf, size, offset) \
        pic32_flash_write(COFFEE_START + offset, buf, size)

#define COFFEE_READ(buf, size, offset) \
        flash_read(COFFEE_START + offset, buf, size)

#define COFFEE_ERASE(sector) \
        pic32_flash_erase(sector)

#endif /* CFS_COFFEE_ARCH_H_ */
