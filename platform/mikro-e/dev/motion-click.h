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

/**
 * \file
 * 	Motion click driver.
 *	http://www.mikroe.com/click/motion/
 *
 */

#ifndef __MOTION_SENSOR_H__
#define __MOTION_SENSOR_H__

/* Motion sensor is connected to pin RD0 */
#define MOTION_SENSOR_PORT      D
#define MOTION_SENSOR_PIN       0

/* To initialize interrupt on Motion detected */
#define MOTION_SENSOR_IRQ_INIT(port) __MOTION_SENSOR_IRQ_INIT(port)
#define __MOTION_SENSOR_IRQ_INIT(port)                                         \
  do {                                                                         \
    CNCON##port##SET = _CNCON##port##_ON_MASK;                                 \
    IEC1SET = _IEC1_CN##port##IE_MASK;                                         \
    IFS1CLR = _IFS1_CN##port##IF_MASK;                                         \
    IPC8SET = (6 << _IPC8_CNIP_POSITION) | (0 << _IPC8_CNIS_POSITION);         \
    (void)PORT##port;                                                          \
  } while(0)

/* To enable Motion sensor interupt */
#define MOTION_SENSOR_IRQ_ENABLE(port, pin) __MOTION_SENSOR_IRQ_ENABLE(port, pin)
#define __MOTION_SENSOR_IRQ_ENABLE(port, pin)                                  \
  do {                                                                         \
    CNEN##port##SET = _CNEND_CNIE##port##pin##_MASK;                           \
  } while(0)

/* To disable Motion sensor interupt */
#define MOTION_SENSOR_IRQ_DISABLE(port, pin) __MOTION_SENSOR_IRQ_DISABLE(port, pin)
#define __MOTION_SENSOR_IRQ_DISABLE(port, pin)                                \
  do {                                                                        \
    CNEN##port##CLR = _CNEN##port##_CNIE##port##pin##_MASK;                   \
  } while(0)

/* To clear interupt */
#define MOTION_SENSOR_CLEAR_IRQ(port, pin) __MOTION_SENSOR_CLEAR_IRQ(port, pin)
#define __MOTION_SENSOR_CLEAR_IRQ(port, pin)                                  \
  do {                                                                        \
    (void)PORT##port;                                                         \
    IFS1CLR = _IFS1_CN##port##IF_MASK;                                        \
    CNSTAT##port##CLR = _CNSTAT##port##_CNSTAT##port##pin##_MASK;             \
  } while(0)

/* To check status of IRQ */
#define MOTION_SENSOR_IRQ_STATUS(port, pin) __MOTION_SENSOR_IRQ_STATUS(port, pin)
#define __MOTION_SENSOR_IRQ_STATUS(port, pin)                                 \
  (IFS1bits.CN##port##IF & CNSTAT##port##bits.CNSTAT##port##pin)

/* Check if Motion was detected */
#define MOTION_SENSOR_CHECK_IRQ() MOTION_SENSOR_IRQ_STATUS(MOTION_SENSOR_PORT, MOTION_SENSOR_PIN)

/* Method to be called when Motion is detected */
void motion_sensor_isr(void);

#define MOTION_SENSOR "motion-sensor"

extern const struct sensors_sensor motion_sensor;

#endif /* __MOTION_SENSOR_H__ */
