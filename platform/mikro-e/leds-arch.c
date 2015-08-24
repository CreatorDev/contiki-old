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
#include "dev/leds.h"
#include "pic32_gpio.h"

/* LED1 is driven by pin RB1 */
#define LED1_PORT   B
#define LED1_PIN    1

/* LED2 is driven by pin RB2 */
#define LED2_PORT   B
#define LED2_PIN    2

/*---------------------------------------------------------------------------*/
void
leds_arch_init(void)
{
  GPIO_CONFIGURE_AS_DIGITAL(LED1_PORT, LED1_PIN);
  GPIO_CONFIGURE_AS_OUTPUT(LED1_PORT, LED1_PIN);
  GPIO_CLR(LED1_PORT, LED1_PIN);

  GPIO_CONFIGURE_AS_DIGITAL(LED2_PORT, LED2_PIN);
  GPIO_CONFIGURE_AS_OUTPUT(LED2_PORT, LED2_PIN);
  GPIO_CLR(LED2_PORT, LED2_PIN);
}

/*---------------------------------------------------------------------------*/
unsigned char
leds_arch_get(void)
{
  return (GPIO_VALUE(LED1_PORT, LED1_PIN) ? LED1 : 0) |
    (GPIO_VALUE(LED2_PORT, LED2_PIN) ? LED2 : 0);
}

/*---------------------------------------------------------------------------*/
void
leds_arch_set(unsigned char leds)
{
  if(leds & LED1) {
    GPIO_SET(LED1_PORT, LED1_PIN);
  } else {
    GPIO_CLR(LED1_PORT, LED1_PIN);
  }

  if(leds & LED2) {
    GPIO_SET(LED2_PORT, LED2_PIN);
  } else {
    GPIO_CLR(LED2_PORT, LED2_PIN);
  }
}

/*---------------------------------------------------------------------------*/
