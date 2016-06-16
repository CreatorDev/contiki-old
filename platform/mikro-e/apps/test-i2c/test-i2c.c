/*
 * Copyright (c) 2016, Imagination Technologies Limited and/or its affiliated
 * group companies.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \file
 * 	A test application for I2C driver useing I2C1 port and Thermo3-click as slave.
 *	http://www.mikroe.com/click/thermo3/
 *
 */

#include <contiki.h>
#include <stdio.h>
#include <stdint.h>
#include <pic32_i2c.h>

#define TMP102_FREQUENCY		100000
#define TMP102_WRITE_ADDRESS		0x90
#define TMP102_READ_ADDRESS		0x91
#define TMP102_CONFIG_ADDRESS		0x01
#define TMP102_CONFIG_MSB		0x60
#define TMP102_CONFIG_LSB		0xE0
/*---------------------------------------------------------------------------*/
PROCESS(test_i2c, "Testing I2C Driver");
AUTOSTART_PROCESSES (&test_i2c);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(test_i2c, ev, data)
{
  PROCESS_EXITHANDLER(goto exit;)
  PROCESS_BEGIN();
  static uint8_t send_data[4] = {TMP102_WRITE_ADDRESS, TMP102_CONFIG_ADDRESS, TMP102_CONFIG_MSB, TMP102_CONFIG_LSB};
  static uint8_t receive_data[2] = {0,0};
  static struct etimer et;
  i2c1_init();
  i2c1_set_frequency(TMP102_FREQUENCY);
  i2c1_master_enable();
  i2c1_send_start();
  /*pass the array to be send and no.of byte*/
  if(i2c1_burst_send (send_data, 4)) {	
    printf("Failed the connection to slave\n");
  }
  i2c1_send_stop();
  while(1) {
    etimer_set(&et, CLOCK_SECOND);
    i2c1_send_start();
    /*commond to TMP102 write data on bus*/
    i2c1_byte_send(TMP102_READ_ADDRESS);
    /*pass the array to be receive and no.of byte*/
    if(i2c1_burst_receive(receive_data, 2)) {
      printf("Failed to receiving the data form slave\n");
    }
    i2c1_send_stop();
    printf("MSB byte is 0x%X\n", receive_data[0]);
    printf("LSB byte is 0x%X\n\n", receive_data[1]);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  }
  exit:
  i2c1_send_stop();
  i2c1_master_disable();
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
