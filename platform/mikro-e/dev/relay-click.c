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
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
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
 *         Relay click driver.
 *         http://www.mikroe.com/click/relay/
 */

#include "pic32_gpio.h"
#include <stdio.h>
#include <stdint.h>
#include "relay-click.h"
/*---------------------------------------------------------------------------*/
#define RELAY1_PORT    F
#define RELAY1_PIN     3
#define RELAY2_PORT    E
#define RELAY2_PIN     5
/*---------------------------------------------------------------------------*/
void
relay_click_init(void)
{
  GPIO_CONFIGURE_AS_OUTPUT(RELAY1_PORT, RELAY1_PIN);
  GPIO_CLR(RELAY1_PORT, RELAY1_PIN);

  GPIO_CONFIGURE_AS_OUTPUT(RELAY2_PORT, RELAY2_PIN);
  GPIO_CLR(RELAY2_PORT, RELAY2_PIN);
}
/*---------------------------------------------------------------------------*/
void
relay_on(int8_t relay_num)
{
  switch(relay_num) {
    case RELAY1:
      GPIO_SET(RELAY1_PORT, RELAY1_PIN);
      break;
    case RELAY2:
      GPIO_SET(RELAY2_PORT, RELAY2_PIN);
      break;
    default:
      printf("Invalid relay to set on\n");
      break;
  }
}
/*---------------------------------------------------------------------------*/
void
relay_off(int8_t relay_num)
{
  switch(relay_num) {
    case RELAY1:
      GPIO_CLR(RELAY1_PORT, RELAY1_PIN);
      break;
    case RELAY2:
      GPIO_CLR(RELAY2_PORT, RELAY2_PIN);
      break;
    default:
      printf("Invalid relay to set off\n");
      break;
  }
}
/*---------------------------------------------------------------------------*/
void
relay_toggle(int8_t relay_num)
{
  switch(relay_num) {
    case RELAY1:
      GPIO_INV(RELAY1_PORT, RELAY1_PIN);
      break;
    case RELAY2:
      GPIO_INV(RELAY2_PORT, RELAY2_PIN);
      break;
    default:
      printf("Invalid relay to set off\n");
      break;
  }
}
/*---------------------------------------------------------------------------*/
