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
 *  \file
 *  	A test application to get temperature form Thermo3 click board.
 *	http://www.mikroe.com/click/thermo3/
 */

#include <contiki.h>
#include <stdio.h>
#include "dev/common-clicks.h"

#define TEMP_REG	0x00   /*Temp. register Address*/
#define CONFIG_REG	0x01   /*Config. register Address*/ 
#define CONFIG_MSB	0x60   /*default value*/
#define CONFIG_LSB	0xE0   /*Conversion rate is set to 8Hz*/
/*---------------------------------------------------------------------------*/
PROCESS(test_thermo3, "Test Thermo3 click");
AUTOSTART_PROCESSES (&test_thermo3);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(test_thermo3, ev, data)
{
  PROCESS_BEGIN();
  static double temp_c;
  static struct etimer et;
  tmp102_init();
  tmp102_reg_select(CONFIG_REG);                
  tmp102_reg_write(CONFIG_MSB, CONFIG_LSB);
  tmp102_reg_select(TEMP_REG);             
  while(1) {
    temp_c = 0;
    etimer_set(&et, CLOCK_SECOND);
    temp_c = tmp102_read_temp();	
    printf("Temperature is %.3f degree celsius\n",temp_c);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  }
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
