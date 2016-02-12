/*
 * Copyright (c) 2016, Imagination Technologies Limited and/or its
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
#include <pic32_gpio.h>
#include <lib/sensors.h>
#include "button-sensor.h"

/*---------------------------------------------------------------------------*/
PROCESS(test_button_process, "Test Button process");
AUTOSTART_PROCESSES(&test_button_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(test_button_process, ev, data)
{
  PROCESS_BEGIN();

  printf("In test button process\n");
  static int i=0;
  while(1) {
    printf("Wait for button press : %d\n", ++i);
    PROCESS_WAIT_EVENT_UNTIL((ev == sensors_event));
    if (data == &button_sensor)
      printf("Button1 press event received\n");


    if (data == &button_sensor2)
      printf("Button2 press event received\n");
  }
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
