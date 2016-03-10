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

#ifndef __BUTTON_SENSOR_H__
#define __BUTTON_SENSOR_H__

#include <pic32_gpio.h>

/* There are two buttons on the board */
#define BUTTON1           0
#define BUTTON2           1
#define NUM_OF_BUTTONS    2

/* Button1 is connected to pin RE7 */
#define BUTTON1_PORT      E
#define BUTTON1_PIN       7

/* Button1 is connected to pin RB0 */
#define BUTTON2_PORT      B
#define BUTTON2_PIN       0

/* To initialize interrupt on button press */
#define BUTTON_IRQ_INIT(port) __BUTTON_IRQ_INIT(port)
#define __BUTTON_IRQ_INIT(port)                                         \
  do {                                                                  \
    CNCON##port##SET = _CNCON##port##_ON_MASK;                          \
    IEC1SET = _IEC1_CN##port##IE_MASK;                                  \
    IFS1CLR = _IFS1_CN##port##IF_MASK;                                  \
    IPC8SET = (6 << _IPC8_CNIP_POSITION) | (0 << _IPC8_CNIS_POSITION);  \
    (void)PORT##port;                                                   \
  } while(0)

/* To enable button press interupt */
#define BUTTON_IRQ_ENABLE(port, pin) __BUTTON_IRQ_ENABLE(port, pin)
#define __BUTTON_IRQ_ENABLE(port, pin)                                  \
  do {                                                                  \
    CNEN##port##SET = _CNEN##port##_CNIE##port##pin##_MASK;             \
  } while(0)

/* To disable button press interupt */
#define BUTTON_IRQ_DISABLE(port, pin) __BUTTON_IRQ_DISABLE(port, pin)
#define __BUTTON_IRQ_DISABLE(port, pin)                                 \
  do {                                                                  \
    CNEN##port##CLR = _CNEN##port##_CNIE##port##pin##_MASK;             \
  } while(0)

/* To clear interupt */
#define BUTTON_CLEAR_IRQ(port, pin) __BUTTON_CLEAR_IRQ(port, pin)
#define __BUTTON_CLEAR_IRQ(port, pin)                                   \
  do {                                                                  \
    (void)PORT##port;                                                   \
    IFS1CLR = _IFS1_CN##port##IF_MASK;                                  \
    CNSTAT##port##CLR = _CNSTAT##port##_CNSTAT##port##pin##_MASK;       \
  } while(0)

/* Check if button was pressed */
#define BUTTON_CHECK_IRQ(port, pin) __BUTTON_CHECK_IRQ(port, pin)
#define __BUTTON_CHECK_IRQ(port, pin)                                   \
  (IFS1bits.CN##port##IF & CNSTAT##port##bits.CNSTAT##port##pin)


/* Check if button1 was pressed */
#define BUTTON1_CHECK_IRQ() BUTTON_CHECK_IRQ(BUTTON1_PORT, BUTTON1_PIN)
/* Method to be called when button1 is pressed */
void button1_isr(void);

/* Check if button2 was pressed */
#define BUTTON2_CHECK_IRQ() BUTTON_CHECK_IRQ(BUTTON2_PORT, BUTTON2_PIN)
/* Method to be called when button2 is pressed */
void button2_isr(void);

#define BUTTON_SENSOR "Button1"
#define BUTTON_SENSOR2 "Button2"
extern const struct sensors_sensor button_sensor, button_sensor2;

#endif /* __BUTTON_SENSOR_H__ */
