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

#ifndef FLASH_H_
#define FLASH_H_

#define FLASH_MEM_BASE_ADDR                                             COFFEE_ADDRESS
#define FLASH_MEM_LEN                                                   0x10000

/* Byte page size, starting address on page boundary, and size of file system */
#define FLASH_START               0xBD000000
/* Minimum erasable unit. */
#define FLASH_PAGE_SIZE           4096
/* Last 7 pages reserved for NVM. */
#define FLASH_PAGES               127

#define FLASH_UNLOCK_KEY1 0xAA996655
#define FLASH_UNLOCK_KEY2 0x556699AA

unsigned int flash_write_word(void* address, uint32_t data);
unsigned int flash_write_row(void* address, void* data);
void flash_write(uint32_t address, const void * data, uint32_t len);
unsigned int flash_erase_page(void* address);
void flash_erase(void * addr);
void flash_read(uint32_t address, void * data, uint32_t len);

#endif /* FLASH_H_ */
