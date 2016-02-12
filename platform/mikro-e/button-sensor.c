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

#include "button-sensor.h"
#include <lib/sensors.h>
#include <pic32_gpio.h>

static struct timer debouncetimer[NUM_OF_BUTTONS];
static int buttons_status[NUM_OF_BUTTONS];
static int button_pressed[NUM_OF_BUTTONS];

/*---------------------------------------------------------------------------*/
static void button_isr(int button_id, const struct sensors_sensor *s)
{
  if (!button_pressed[button_id]) {
    /*
     * If timer is still running, it means the button has just been released and
     * it is a false notification due to bouncing
     */
    if (timer_expired(&debouncetimer[button_id])) {
      button_pressed[button_id] = 1;
      /* Set a timer for 100ms to ignore false notifications due to bouncing */
      timer_set(&debouncetimer[button_id], CLOCK_SECOND / 10);
      /* Notify processes that button has been pressed */
      sensors_changed(s);
    }
  } else {
    /*
     * If timer is still running, it means the button has just been pressed and
     * it is a false notification due to bouncing
     */
    if (timer_expired(&debouncetimer[button_id])) {
      button_pressed[button_id] = 0;
      /* Set a timer for 100ms to ignore false notifications due to bouncing */
      timer_set(&debouncetimer[button_id], CLOCK_SECOND / 10);
    }
  }
}

void button1_isr(void)
{
  button_isr(BUTTON1, &button_sensor);
  BUTTON_CLEAR_IRQ(BUTTON1_PORT, BUTTON1_PIN);
}
/*---------------------------------------------------------------------------*/
void button2_isr(void)
{
  button_isr(BUTTON2, &button_sensor2);
  BUTTON_CLEAR_IRQ(BUTTON2_PORT, BUTTON2_PIN);
}
/*---------------------------------------------------------------------------*/
static int
button1_value(int type)
{
  return button_pressed[BUTTON1];
}
/*---------------------------------------------------------------------------*/
static int
button2_value(int type)
{
  return button_pressed[BUTTON2];
}
/*---------------------------------------------------------------------------*/
static int
button1_configure(int type, int value)
{
  switch(type) {
    case SENSORS_HW_INIT:
      /* Configure gpio pins and initialize interrupt */
      GPIO_CONFIGURE_AS_DIGITAL(BUTTON1_PORT, BUTTON1_PIN);
      GPIO_CONFIGURE_AS_INPUT(BUTTON1_PORT, BUTTON1_PIN);
      BUTTON_IRQ_INIT(BUTTON1_PORT);
      button_pressed[BUTTON1] = 0;
      return 1;

    case SENSORS_ACTIVE:
      if(value) {
        if(!buttons_status[BUTTON1]) {
          /* Enable interrupt for button press */
          timer_set(&debouncetimer[BUTTON1], 0);
          BUTTON_IRQ_ENABLE(BUTTON1_PORT, BUTTON1_PIN);
          buttons_status[BUTTON1] = 1;
        }
      } else {
        /* Disable interrupt for button press */
        BUTTON_IRQ_DISABLE(BUTTON1_PORT, BUTTON1_PIN);
        buttons_status[BUTTON1] = 0;
      }
      return 1;

    default:
      return 0;
  }
}
/*---------------------------------------------------------------------------*/
static int
button2_configure(int type, int value)
{
  switch (type) {
    case SENSORS_HW_INIT:
      /* Configure gpio pins and initialize interrupt */
      GPIO_CONFIGURE_AS_DIGITAL(BUTTON2_PORT, BUTTON2_PIN);
      GPIO_CONFIGURE_AS_INPUT(BUTTON2_PORT, BUTTON2_PIN);
      BUTTON_IRQ_INIT(BUTTON2_PORT);
      button_pressed[BUTTON2] = 0;
      return 1;

    case SENSORS_ACTIVE:
      if(value) {
        if(!buttons_status[BUTTON2]) {
          /* Enable interrupt for button press */
          timer_set(&debouncetimer[BUTTON2], 0);
          BUTTON_IRQ_ENABLE(BUTTON2_PORT, BUTTON2_PIN);
          buttons_status[BUTTON2] = 1;
        }
      } else {
        /* Disable interrupt for button press */
        BUTTON_IRQ_DISABLE(BUTTON2_PORT, BUTTON2_PIN);
        buttons_status[BUTTON2] = 0;
      }
      return 1;

    default:
      return 0;
  }
}
/*---------------------------------------------------------------------------*/
static int
button1_status(int type)
{
  return buttons_status[BUTTON1];
}
/*---------------------------------------------------------------------------*/
static int
button2_status(int type)
{
  return buttons_status[BUTTON2];
}
/*---------------------------------------------------------------------------*/
SENSORS_SENSOR(button_sensor, BUTTON_SENSOR, button1_value, button1_configure,
  button1_status);
SENSORS_SENSOR(button_sensor2, BUTTON_SENSOR2, button2_value, button2_configure,
  button2_status);
/*---------------------------------------------------------------------------*/
