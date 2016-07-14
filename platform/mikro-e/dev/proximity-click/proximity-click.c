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

#include <stdio.h>
#include <stdint.h>
#include <p32xxxx.h>
#include <pic32_i2c.h>
#include <lib/sensors.h>
#include "proximity-click.h"

static struct timer debouncetimer;
static int proximity_sensor_mode;

/*---------------------------------------------------------------------------*/
static void
proximity_sensor_read(const struct sensors_sensor *s)
{
  if (timer_expired(&debouncetimer)) {
    /* Set a timer for 100ms to ignore false notifications */
    timer_set(&debouncetimer, CLOCK_SECOND / 10);
    /* Notify processes that proximity has been detected */
    sensors_changed(s);
  }
}

void
proximity_sensor_isr(void)
{
  proximity_sensor_read(&proximity_sensor);
  /* Clear interrupt for Proximity sensor */
  PROXIMITY_SENSOR_CLEAR_IRQ();
}
/*---------------------------------------------------------------------------*/
static int
proximity_sensor_configure(int type, int value)
{

  switch(type) {
    case SENSORS_HW_INIT:
        PROXIMITY_SENSOR_IRQ_INIT();
        return 1;

    case SENSORS_ACTIVE:
      if(value) {
        if(!proximity_sensor_mode) {
          i2c1_init();
          i2c1_set_frequency (I2C_FREQUENCY);
          I2C1CONCLR = _I2C1CON_SMEN_MASK;
          I2C1CONSET = _I2C1CON_ACKDT_MASK;
          i2c1_master_enable();
          i2c1_send_start();
          /* proximity data enable and selftime enable */
          i2c1_byte_send(WRITE_ADDR);
          i2c1_byte_send(COMMAND_REG);
          i2c1_byte_send(PROXIMITY_SELFTIME_EN);
          i2c1_send_repeated_start();
          /* proximity measurement rate 4  measurement pre second */
          i2c1_byte_send(WRITE_ADDR);
          i2c1_byte_send(PROXIMITY_RATE_REG);
          i2c1_byte_send(PROXIMITY_RATE_4);
          i2c1_send_repeated_start();
          /* IRLED current 100 mA */
          i2c1_byte_send(WRITE_ADDR);
          i2c1_byte_send(IRLED_CUURENT_REG);
          i2c1_byte_send(IRLED_CURRENT_100MA);
          i2c1_send_repeated_start();
          /* High threshold register upper byte */
          i2c1_byte_send(WRITE_ADDR);
          i2c1_byte_send(HIGH_THRESHOLD_UPPER_REG);
          i2c1_byte_send(THRESHOLD_UPPER_BYTE);
          i2c1_send_repeated_start();
          /* High threshold register lower byte */
          i2c1_byte_send(WRITE_ADDR);
          i2c1_byte_send(HIGH_THRESHOLD_LOWER_REG);
          i2c1_byte_send(THRESHOLD_LOWER_BYTE);
          i2c1_send_repeated_start();
          /* Enable interrupt for Proximity sensor */
          i2c1_byte_send(WRITE_ADDR);
          i2c1_byte_send(INTERRUPT_CONTROL_REG);
          i2c1_byte_send(INTERRUPT_REG_SETTING);
          i2c1_send_stop();
          i2c1_master_disable();
          PROXIMITY_SENSOR_IRQ_ENABLE();
          timer_set(&debouncetimer, 0);
          proximity_sensor_mode = 1;
        }
      } else {
        /* Disable interrupt for Proximity sensor */
        PROXIMITY_SENSOR_IRQ_DISABLE();
        proximity_sensor_mode = 0;
      }
      return 1;

    default:
      return 0;
  }

}

static int
proximity_sensor_value(int type)
{
  uint8_t data[2];
  int     value;
  i2c1_master_enable();
  i2c1_send_start();
  i2c1_byte_send(WRITE_ADDR);
  i2c1_byte_send(PROXIMITY_DATA_UPPER_REG);
  i2c1_send_repeated_start();
  i2c1_byte_send(READ_ADDR);
  i2c1_byte_receive(data);
  i2c1_send_repeated_start();
  i2c1_byte_send(WRITE_ADDR);
  i2c1_byte_send(PROXIMITY_DATA_LOWER_REG);
  i2c1_send_repeated_start();
  i2c1_byte_send(READ_ADDR);
  i2c1_byte_receive(data + 1);
  i2c1_send_stop();
  i2c1_master_disable();
  value = ((uint16_t)data[0] << 8) | data[1];
  return value;
}
/*---------------------------------------------------------------------------*/
static int
proximity_sensor_status(int type)
{
  return proximity_sensor_mode;
}
/*---------------------------------------------------------------------------*/
SENSORS_SENSOR(proximity_sensor, PROXIMITY_SENSOR, proximity_sensor_value, proximity_sensor_configure,
		proximity_sensor_status);
/*---------------------------------------------------------------------------*/
