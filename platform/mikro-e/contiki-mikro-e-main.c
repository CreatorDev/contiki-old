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

/* TODO: add documentation */
#include <contiki.h>
#include <clock.h>
#include <pic32.h>
#include <pic32_clock.h>
#include <dev/watchdog.h>
#include <platform-init.h>
#include <debug-uart.h>
#include <pic32_irq.h>
#include <dev/cc2520/cc2520.h>
#include "dev/serial-line.h"
#include <net-init.h>
#include <leds.h>
#include <sensors.h>
#include "button-sensor.h"
#include "motion-click.h"

#define UART_DEBUG_BAUDRATE 115200
SENSORS(&button_sensor, &button_sensor2, &motion_sensor);

/*---------------------------------------------------------------------------*/
int
main(int argc, char **argv)
{
  int32_t r = 0;
 
  pic32_init();
  watchdog_init();
  clock_init();
  leds_init();
  platform_init();

  process_init();
  process_start(&etimer_process, NULL);
  ctimer_init();
  rtimer_init();

  process_start(&sensors_process, NULL);
  SENSORS_ACTIVATE(button_sensor);
  SENSORS_ACTIVATE(button_sensor2);

  dbg_setup_uart(UART_DEBUG_BAUDRATE);
  net_init();

  uart3_set_input(serial_line_input_byte);
  serial_line_init();
  
  autostart_start(autostart_processes);
  watchdog_start();
  
  while(1) {
    do {
      watchdog_periodic();
      r = process_run();
    } while(r > 0);
    watchdog_stop();
    asm volatile("wait");
    watchdog_start();
  }
  
  return 0;
}
/*---------------------------------------------------------------------------*/
ISR(_CHANGE_NOTICE_VECTOR)
{
  if(BUTTON1_CHECK_IRQ()) {
    /* Button1 was pressed */
    button1_isr();
  } else if(BUTTON2_CHECK_IRQ()) {
    /* Button2 was pressed */
    button2_isr();
  } else if(MOTION_SENSOR_CHECK_IRQ()) {
    /* Motion was detected */
    motion_sensor_isr();
  }
}

ISR(_EXTERNAL_1_VECTOR)
{
    cc2520_interrupt();
}
/*---------------------------------------------------------------------------*/
