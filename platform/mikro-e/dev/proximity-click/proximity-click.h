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

#ifndef __PROXIMITY_CLICK_H__
#define __PROXIMITY_CLICK_H__

#include <pic32_i2c.h>

#define I2C_FREQUENCY                 100000
#define WRITE_ADDR                    0X26
#define READ_ADDR                     0X27
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
/* Setting number of consecutive measurements
needed above/below the threshold  2 and enable
interrupt generation when high or low threshold
is exceeded.
*/
#define INTERRUPT_REG_SETTING         0X22
#define INTERRUPT_RESET               0XFF

#define PROXIMITY_SENSOR "proximity-sensor"

/* To initialize Motion sensor interrupt */
#define PROXIMITY_SENSOR_IRQ_INIT() __PROXIMITY_SENSOR_IRQ_INIT()
#define __PROXIMITY_SENSOR_IRQ_INIT()                                   \
  do {                                                                  \
    GPIO_CONFIGURE_AS_INPUT(D, 0);                                      \
    CNCONDSET = _CNCOND_ON_MASK;                                        \
    IEC1SET = _IEC1_CNDIE_MASK;                                         \
    IFS1CLR = _IFS1_CNDIF_MASK;                                         \
    IPC8SET = (6 << _IPC8_CNIP_POSITION) | (0 << _IPC8_CNIS_POSITION);  \
    (void)PORTD;                                                        \
  } while(0)

/* To enable Motion sensor interrupt */
#define PROXIMITY_SENSOR_IRQ_ENABLE() __PROXIMITY_SENSOR_IRQ_ENABLE()
#define __PROXIMITY_SENSOR_IRQ_ENABLE()                                \
  do {                                                                 \
    CNENDSET = _CNEND_CNIED0_MASK;                                     \
  } while(0)

/* To disable Motion sensor interrupt */
#define PROXIMITY_SENSOR_IRQ_DISABLE() __PROXIMITY_SENSOR_IRQ_DISABLE()
#define __PROXIMITY_SENSOR_IRQ_DISABLE()                               \
  do {                                                                 \
    CNENDCLR = _CNEND_CNIED0_MASK;                                     \
  } while(0)

/* To Clear Proximity sensor interrupt */
#define PROXIMITY_SENSOR_CLEAR_IRQ() __PROXIMITY_SENSOR_CLEAR_IRQ()
#define __PROXIMITY_SENSOR_CLEAR_IRQ()                                  \
    do{                                                                   \
        i2c1_master_enable();                                             \
        i2c1_send_start();                                                \
        i2c1_send_byte(WRITE_ADDR);                                       \
        i2c1_send_byte(INTERRUPT_STATUS_REG);                             \
        i2c1_send_byte(INTERRUPT_RESET);                                  \
        i2c1_send_stop();                                                 \
        i2c1_master_disable();                                            \
        (void)PORTD;                                                      \
        IFS1CLR = _IFS1_CNDIF_MASK;                                       \
        CNSTATDCLR = _CNSTATD_CNSTATD0_MASK;                              \
    }while(0)

/* Check if Proximity was detected */
#define PROXIMITY_SENSOR_CHECK_IRQ() __PROXIMITY_SENSOR_CHECK_IRQ()
#define __PROXIMITY_SENSOR_CHECK_IRQ()                                   \
  (IFS1bits.CNDIF & CNSTATDbits.CNSTATD0)

/* Method to be called when Interrupt is generated */
void proximity_sensor_isr(void);

extern const struct sensors_sensor proximity_sensor;
#endif /* __PROXIMITY_CLICK_H__ */
