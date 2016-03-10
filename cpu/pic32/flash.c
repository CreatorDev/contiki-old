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

#include <p32xxxx.h>

#include "contiki.h"
#include "dev/flash.h"

#define DEBUG 0
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

unsigned int
nvm_unlock (unsigned int nvmop)
{
  unsigned int status;
  asm volatile ("di %0" : "=r" (status));
  NVMCON &= ~0x4000;
  NVMCON = nvmop;
  NVMCON |= 0x4000;
  NVMKEY = 0;
  NVMKEY = FLASH_UNLOCK_KEY1;
  NVMKEY = FLASH_UNLOCK_KEY2;
  NVMCONSET = 0x8000;
  while (NVMCON & 0x8000);
  if (status & 0x00000001)
    asm volatile ("ei");
  else
    asm volatile ("di");
  return (NVMCON & 0x3000);
}

unsigned int
flash_write_word(void* address, uint32_t data)
{
  unsigned int res;
  NVMADDR = (unsigned int) address;
  NVMDATA = data;
  res = nvm_unlock (1);
  return res;
}

unsigned int
flash_write_row(void* address, void* data)
{
  unsigned int res;
  NVMADDR = (unsigned int) address;
  NVMSRCADDR = (unsigned int) data;
  res = nvm_unlock(3);
  return res;
}

void
flash_write(uint32_t address, const void * data, uint32_t len)
{
  uint32_t * write_addr = (uint32_t *)(address ^ 0xA0000000);
  uint32_t * mem_addr = (uint32_t *)data;
  uint32_t pos = 0;

  PRINTF("FLASH: write at %08X (%p) len %d from %p\n", address, write_addr, len, data);

  ENERGEST_ON(ENERGEST_TYPE_FLASH_WRITE);

  for(pos = 0; pos < len >> 2; pos++) {
    flash_write_word((void *)&write_addr[pos], mem_addr[pos]);
  }

  if(len >> 2 && len & 0x3)
  {
    static uint32_t last_word = 0;
    memcpy(&last_word, &mem_addr[pos], len & 0x3);
    flash_write_word((void *)&write_addr[pos], last_word);
  }

  ENERGEST_OFF(ENERGEST_TYPE_FLASH_READ);
}

unsigned int
flash_erase_page(void* address)
{
  unsigned int res;
  NVMADDR = (unsigned int) address;
  res = nvm_unlock(4);
  return res;
}

void
flash_erase(void * addr)
{
  void * erase_addr = (void *)(((uint32_t)addr) ^ 0xA0000000);

  PRINTF("FLASH: erase address %p\n", erase_addr);

  ENERGEST_ON(ENERGEST_TYPE_FLASH_WRITE);
  flash_erase_page(erase_addr);
  ENERGEST_OFF(ENERGEST_TYPE_FLASH_WRITE);
}

void
flash_read(uint32_t address, void * data, uint32_t len)
{
  void * flash_addr = (void *)(address);

  PRINTF("FLASH: read at %08X (%p) len %d to %p\n", address, flash_addr, len, data);

  ENERGEST_ON(ENERGEST_TYPE_FLASH_READ);
  memcpy(data, flash_addr, len);
  ENERGEST_OFF(ENERGEST_TYPE_FLASH_READ);
}


