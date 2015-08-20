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
#include <net-init.h>

#define UART_DEBUG_BAUDRATE 115200

/*---------------------------------------------------------------------------*/
int
main(int argc, char **argv)
{
  int32_t r;

  pic32_init();
  watchdog_init();
  clock_init();
  platform_init();

  process_init();
  process_start(&etimer_process, NULL);
  ctimer_init();
  rtimer_init();

  dbg_setup_uart(UART_DEBUG_BAUDRATE);
  net_init();

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
ISR(_CHANGE_NOTICE_VECTOR) {
  if (CC2520_FIFOP_INT_IS_1) {
    /*
     * Need to check FIFOP pin to detect rising or falling edge as change
     * notification interrupt is generated for each value change irrespective
     * of falling or leading edge and cc2520_interrupt() needs to be called
     * only for rising edge.
     */
    if (CC2520_FIFOP_IS_1) {
      /* For rising edge */
      cc2520_interrupt();
    } else {
      /* For falling edge */
      CC2520_CLEAR_FIFOP_INT();
    }
  }
}
/*---------------------------------------------------------------------------*/
