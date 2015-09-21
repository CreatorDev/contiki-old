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

#include "cfs-coffee-arch.h"
#include <p32xxxx.h>

#include "cfs/cfs.h"
#include "cfs/cfs-coffee.h"
#include "lib/crc16.h"
#include "lib/random.h"
#include "dev/flash.h"

void
pic32_flash_erase(coffee_page_t sector)
{
  void * erase_addr = (void *)(COFFEE_START + (sector * COFFEE_SECTOR_SIZE));
  uint16_t pos = 0;

  flash_erase(erase_addr);

  for(pos = 0; pos < COFFEE_SECTOR_SIZE; pos+=4) {
      flash_write_word(erase_addr + pos, 0);
  }
}

void
pic32_flash_write(uint32_t address, const void * data, uint32_t len)
{
  const uint32_t end = address + len;
  uint32_t i;
  uint32_t next_page, curr_page;
  uint16_t offset;
#if STATIC_FLASH_BUFFER
  static uint8_t buf[COFFEE_SECTOR_SIZE] __attribute__((coherent)) ;
#else
  uint8_t buf[COFFEE_SECTOR_SIZE];
#endif

  for(i = address; i < end;){
    next_page = (i | (COFFEE_SECTOR_SIZE - 1)) + 1;
    curr_page = i & ~(COFFEE_SECTOR_SIZE - 1);
    offset = i - curr_page;
    if(next_page > end)
      next_page = end;

    flash_read(curr_page, buf, COFFEE_SECTOR_SIZE);
    memcpy(buf + offset, data, next_page - i);

    flash_erase((void *)i);
    flash_write(curr_page, buf, COFFEE_SECTOR_SIZE);

    data = (uint8_t *) data + next_page - i;
    i = next_page;
  }
}
