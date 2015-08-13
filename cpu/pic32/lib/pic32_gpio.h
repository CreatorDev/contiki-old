/*
 * Copyright (c) 2015, Imagination Technologies Limited and/or its affiliated group companies.
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

#ifndef __INCLUDE_PIC32_GPIO_H__
#define __INCLUDE_PIC32_GPIO_H__

#include <p32xxxx.h>
#include <pic32_irq.h>

#define GPIO_CONFIGURE_AS_ANALOG(port, pin) __GPIO_CONFIGURE_AS_ANALOG(port, pin)
#define GPIO_CONFIGURE_AS_DIGITAL(port, pin) __GPIO_CONFIGURE_AS_DIGITAL(port, pin)
#define GPIO_CONFIGURE_AS_INPUT(port, pin) __GPIO_CONFIGURE_AS_INPUT(port, pin)
#define GPIO_CONFIGURE_AS_OUTPUT(port, pin) __GPIO_CONFIGURE_AS_OUTPUT(port, pin)
#define GPIO_SET(port, pin) __GPIO_SET(port, pin)
#define GPIO_CLR(port, pin) __GPIO_CLR(port, pin)
#define GPIO_INV(port, pin) __GPIO_INV(port, pin)
#define GPIO_VALUE(port, pin) __GPIO_VALUE(port, pin)

#define __GPIO_CONFIGURE_AS_ANALOG(port, pin)                     \
  do {                                                            \
    ANSEL##port##SET = _ANSEL##port##_ANS##port##pin##_MASK;      \
  } while(0)

#define __GPIO_CONFIGURE_AS_DIGITAL(port, pin)                    \
  do {                                                            \
    ANSEL##port##CLR = _ANSEL##port##_ANS##port##pin##_MASK;      \
  } while(0)

#define __GPIO_CONFIGURE_AS_INPUT(port, pin)                      \
  do {                                                            \
    TRIS##port##SET = _TRIS##port##_TRIS##port##pin##_MASK;       \
  } while(0)

#define __GPIO_CONFIGURE_AS_OUTPUT(port, pin)                     \
  do {                                                            \
    TRIS##port##CLR = _TRIS##port##_TRIS##port##pin##_MASK;       \
  } while(0)

#define __GPIO_SET(port, pin)                                     \
  do {                                                            \
    LAT##port##SET = _LAT##port##_LAT##port##pin##_MASK;          \
  } while(0)

#define __GPIO_CLR(port, pin)                                     \
  do {                                                            \
    LAT##port##CLR = _LAT##port##_LAT##port##pin##_MASK;          \
  } while(0)

#define __GPIO_INV(port, pin)                                     \
  do {                                                            \
    LAT##port##INV = _LAT##port##_LAT##port##pin##_MASK;          \
  } while(0)

#define __GPIO_VALUE(port, pin) PORT##port##bits.R##port##pin

#endif /* __INCLUDE_PIC32_GPIO_H__ */
