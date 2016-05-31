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
#include "proximity-click.h"

#define I2C_FREQUENCY		          100000
#define SALE_ADDR_WRITE               0X26
#define SALE_ADDR_READ                0X27
/* VCNL4010 REGISTERS */
#define COMMAND_REG                   0X80
#define PROXIMITY_RATE_REG            0X82
#define IRLED_CUURENT_REG             0X83
#define PROXIMITY_DATA_UPPER_REG      0X87
#define PROXIMITY_DATA_LOWER_REG      0X88
#define HIGH_THRESHOLD_UPPER_REG      0X8C
#define HIGH_THRESHOLD_LOWER_REG      0X8D
#define INTERRUPT_CONTROL_REG         0X89
#define INTERRUPT_STATUS_REG          0X8E
/* reg config value */
#define PROXIMITY_SELFTIME_EN         0X03
#define PROXIMITY_RATE_4              0X01
#define IRLED_CURRENT_100MA           0X10
#define THRESHOLD_UPPER_BYTE          0X08
#define THRESHOLD_LOWER_BYTE          0XA0
#define TH_INT_EN_TWO_COUNT           0X22
#define INT_LINE_RESET                0XFF
void
proximity_click_init(void)
{
  i2c1_init();
  i2c1_set_frequency (I2C_FREQUENCY);
  I2C1CONCLR = _I2C1CON_SMEN_MASK;
  I2C1CONSET = _I2C1CON_ACKDT_MASK;
  i2c1_master_enable();
  i2c1_send_start();
  /* proximity data enable and selftime enable */
  i2c1_byte_send(SALE_ADDR_WRITE);
  i2c1_byte_send(COMMAND_REG);
  i2c1_byte_send(PROXIMITY_SELFTIME_EN);
  i2c1_send_repeated_start();
  /* proximity measurement rate 4  measurement pre second */
  i2c1_byte_send(SALE_ADDR_WRITE);
  i2c1_byte_send(PROXIMITY_RATE_REG);
  i2c1_byte_send(PROXIMITY_RATE_4);
  i2c1_send_repeated_start();
  /* IRLED current 100 mA */
  i2c1_byte_send(SALE_ADDR_WRITE);
  i2c1_byte_send(IRLED_CUURENT_REG);
  i2c1_byte_send(IRLED_CURRENT_100MA);
  i2c1_send_repeated_start();
  /* High threshold register upper byte */
  i2c1_byte_send(SALE_ADDR_WRITE);
  i2c1_byte_send(HIGH_THRESHOLD_UPPER_REG);
  i2c1_byte_send(THRESHOLD_UPPER_BYTE);
  i2c1_send_repeated_start();
  /* High threshold register lower byte */
  i2c1_byte_send(SALE_ADDR_WRITE);
  i2c1_byte_send(HIGH_THRESHOLD_LOWER_REG);
  i2c1_byte_send(THRESHOLD_LOWER_BYTE);
  i2c1_send_repeated_start();
  /* Interrupt control register two mesurements 
   * exceed threshold and proximity INT enable
   * also threshold applied to proximity measurements
   */
  i2c1_byte_send(SALE_ADDR_WRITE);
  i2c1_byte_send(INTERRUPT_CONTROL_REG);
  i2c1_byte_send(TH_INT_EN_TWO_COUNT);
  i2c1_send_stop();
  i2c1_master_disable();
}

void
proximity_data(void)
{
  uint8_t data[2];
  uint16_t value; 
  i2c1_master_enable();
  i2c1_send_start();
  i2c1_byte_send(SALE_ADDR_WRITE);
  i2c1_byte_send(PROXIMITY_DATA_UPPER_REG);
  i2c1_send_repeated_start();
  i2c1_byte_send(SALE_ADDR_READ);
  i2c1_byte_receive(data);
  i2c1_send_repeated_start();
  i2c1_byte_send(SALE_ADDR_WRITE);
  i2c1_byte_send(PROXIMITY_DATA_LOWER_REG);
  i2c1_send_repeated_start();
  i2c1_byte_send(SALE_ADDR_READ);
  i2c1_byte_receive(data + 1);
  i2c1_send_stop();
  i2c1_master_disable();
  value = ((uint16_t)data[0] << 8) | data[1];
  printf("The proximity data is 0x%X\n", value);
}

void
proximity_clear_irq(void)
{
  i2c1_master_enable();
  i2c1_send_start();
  /* Reset interrupt status register */
  i2c1_byte_send(SALE_ADDR_WRITE);
  i2c1_byte_send(INTERRUPT_STATUS_REG);
  i2c1_byte_send(INT_LINE_RESET);
  i2c1_send_stop();
  i2c1_master_disable();
}