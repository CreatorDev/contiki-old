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

#include <contiki.h>
#include <stdio.h>
#include <sys/etimer.h>
#include <clock.h>
#include <pic32_spi.h>
#include <pic32_gpio.h>
#include <cc2520.h>

#define SPI_CLOCK_FREQUENCY 4000000   /* 4MHz */

/*---------------------------------------------------------------------------*/
PROCESS(test_spi_process, "Test SPI process");
AUTOSTART_PROCESSES(&test_spi_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(test_spi_process, ev, data)
{
  PROCESS_BEGIN();
  uint8_t read_byte, write_byte;
  static struct etimer et;
  etimer_set(&et, 10 * CLOCK_SECOND);

  /* Configure cc2520 chip select pin */
  GPIO_CONFIGURE_AS_OUTPUT(E, 3);
  GPIO_SET(E, 3);

  pic32_spi2_init(SPI_CLOCK_FREQUENCY, SPI_DEFAULT);
  printf("In test spi process\n");

  while(1) {
    /* Enable cc2520 chip select */
    GPIO_CLR(E, 3);

    /* Write command to read chip id */
    write_byte = CC2520_INS_MEMRD | ((CC2520_CHIPID >> 8) & 0xFF);
    pic32_spi2_write(&write_byte, 1);

    write_byte = CC2520_CHIPID & 0xFF;
    pic32_spi2_write(&write_byte, 1);

    /* Read chip id */
    pic32_spi2_read(&read_byte, 1);

    /* Disable cc2520 chip select */
    GPIO_SET(E, 3);

    printf("Chip ID: 0x%02x \n", read_byte);
    if(read_byte == 0x84) {
      printf("Test passed\n");
    } else {
      printf("Test failed\n");
    }

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    etimer_reset(&et);
  }
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
