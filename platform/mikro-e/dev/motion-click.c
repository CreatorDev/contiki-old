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
 * 	Motion click driver.
 *	http://www.mikroe.com/click/motion/
 *
 */

#include <lib/sensors.h>
#include "motion-click.h"

static struct timer debouncetimer;
static int motion_sensor_mode;
static int motion_sensor_state;
/*---------------------------------------------------------------------------*/
static void motion_sensor_read(const struct sensors_sensor *s)
{
  if (!motion_sensor_state) {
    if (timer_expired(&debouncetimer)) {
    	motion_sensor_state = 1;
      /* Set a timer for 100ms to ignore false notifications */
       timer_set(&debouncetimer, CLOCK_SECOND / 10);
      /* Notify processes that Motion has been detected */
      sensors_changed(s);
    }
  } else {
    if (timer_expired(&debouncetimer)) {
    	motion_sensor_state = 0;
      /* Set a timer for 100ms to ignore false notifications */
      timer_set(&debouncetimer, CLOCK_SECOND / 10);
    }
  }
}

void motion_sensor_isr(void)
{
  motion_sensor_read(&motion_sensor);
  MOTION_SENSOR_CLEAR_IRQ();
}
/*---------------------------------------------------------------------------*/
static int
motion_sensor_configure(int type, int value)
{
  switch(type) {
    case SENSORS_HW_INIT:
      /* Configure gpio pins and initialize interrupt */
      MOTION_SENSOR_IRQ_INIT();
      motion_sensor_state = 0;
      return 1;

    case SENSORS_ACTIVE:
      if(value) {
        if(!motion_sensor_mode) {
          /* Enable interrupt for Motion sensor */
          timer_set(&debouncetimer, 0);
          MOTION_SENSOR_IRQ_ENABLE();
          motion_sensor_mode = 1;
        }
      } else {
        /* Disable interrupt for Motion sensor */
        MOTION_SENSOR_IRQ_DISABLE();
        motion_sensor_mode = 0;
      }
      return 1;

    default:
      return 0;
   }
}
/*---------------------------------------------------------------------------*/
static int
motion_sensor_status(int type)
{
  return motion_sensor_mode;
}
/*---------------------------------------------------------------------------*/
static int
motion_sensor_value(int type)
{
  return motion_sensor_state;
}
/*---------------------------------------------------------------------------*/
SENSORS_SENSOR(motion_sensor, MOTION_SENSOR, motion_sensor_value, motion_sensor_configure,
		motion_sensor_status);
/*---------------------------------------------------------------------------*/
