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

#ifndef __CC2520_CONF_H__
#define __CC2520_CONF_H__

#undef DEBUG /* Conflict with a macro named DEBUG defined in compiler */
#include <p32xxxx.h>
#undef DEBUG

#include <pic32_gpio.h>


/* Bit Value macro used in cc2520.c but not defined anywhere */
#define BV(x) (1 << (x))

/* Interrupt methods used in cc2520.c but not defined anywhere */
int splhigh();
void splx(int s);

#define CC2520_CONF_SYMBOL_LOOP_COUNT 13040   /* 320us for 80MHz */

/* SPI definitions for cc2520 driver */

#define SPI_TXBUF SPI2BUF
#define SPI_RXBUF SPI2BUF

#define SPI_WAITFOREOTx()         \
  do {                            \
    while(!SPI2STATbits.SPIRBF);  \
    (void)SPI2BUF;                \
  } while(0)

#define SPI_WAITFOREORx()         \
  do {                            \
    while(!SPI2STATbits.SPIRBF);  \
  } while(0)

#define CC2520_SPI_BAUDRATE 4000000  /* 4MHz */

/* Pin configuration */

/* RD5 - Input: FIFOP from CC2520 */
#define CC2520_FIFOP_PORT   D
#define CC2520_FIFOP_PIN    5

/* RB4 - Input: FIFO from CC2520 */
#define CC2520_FIFO_PORT    B
#define CC2520_FIFO_PIN     4

/* RE6 - Input: CCA from CC2520 */
#define CC2520_CCA_PORT     E
#define CC2520_CCA_PIN      6

/* RE1 - Input: SFD from CC2520 */
#define CC2520_SFD_PORT     E
#define CC2520_SFD_PIN      1

/* RE3 - Output: SPI Chip Select (CS) to CC2520 */
#define CC2520_CS_PORT      E
#define CC2520_CS_PIN       3

/* RE0 - Output: VREG_EN to CC2520 */
#define CC2520_VREG_PORT    E
#define CC2520_VREG_PIN     0

/* RE2 - Output: RESET to CC2520 */
#define CC2520_RESET_PORT   E
#define CC2520_RESET_PIN    2

/* CC2520 Pin status */

#define CC2520_FIFOP_IS_1     (GPIO_VALUE(CC2520_FIFOP_PORT, CC2520_FIFOP_PIN))
#define CC2520_FIFO_IS_1      (GPIO_VALUE(CC2520_FIFO_PORT, CC2520_FIFO_PIN))
#define CC2520_CCA_IS_1       (GPIO_VALUE(CC2520_CCA_PORT, CC2520_CCA_PIN))
#define CC2520_SFD_IS_1       (GPIO_VALUE(CC2520_SFD_PORT, CC2520_SFD_PIN))

/* CC2520 reset pin (active low) */
#define SET_RESET_INACTIVE()                                            \
  do {                                                                  \
    GPIO_SET(CC2520_RESET_PORT, CC2520_RESET_PIN);                      \
  } while(0)

#define SET_RESET_ACTIVE()                                              \
  do {                                                                  \
    GPIO_CLR(CC2520_RESET_PORT, CC2520_RESET_PIN);                      \
  } while(0)

/* CC2520 voltage regulator enable pin */
#define SET_VREG_ACTIVE()                                               \
  do {                                                                  \
    GPIO_SET(CC2520_VREG_PORT, CC2520_VREG_PIN);                        \
  } while(0)

#define SET_VREG_INACTIVE()                                             \
  do {                                                                  \
    GPIO_CLR(CC2520_VREG_PORT, CC2520_VREG_PIN);                        \
  } while(0)

/* CC2520 chip select pin (active low) */
#define CC2520_SPI_ENABLE()                                             \
  do {                                                                  \
    GPIO_CLR(CC2520_CS_PORT, CC2520_CS_PIN);                            \
    clock_delay(5);                                                     \
  } while(0)

#define CC2520_SPI_DISABLE()                                            \
  do {                                                                  \
    GPIO_SET(CC2520_CS_PORT, CC2520_CS_PIN);                            \
    clock_delay(5);                                                     \
  } while(0)

/* CC2520 change notice interrupt on FIFOP pin (RE6) */
#define CC2520_FIFOP_INT_INIT()                                         \
  do {                                                                  \
    IFS0CLR = _IFS0_INT1IF_MASK;                                        \
    INTCONSET = _INTCON_INT1EP_MASK;                                    \
    IPC1CLR = _IPC1_INT1IP_MASK | _IPC1_INT1IS_MASK;                        \
    IPC1SET = (6 << _IPC1_INT1IP_POSITION) | (3 << _IPC1_INT1IS_POSITION);  \
  } while(0)

#define CC2520_ENABLE_FIFOP_INT()                                       \
  do {                                                                  \
    IFS0CLR = _IFS0_INT1IF_MASK;                                        \
    IEC0SET = _IEC0_INT1IE_MASK;                                        \
  } while(0)

#define CC2520_DISABLE_FIFOP_INT()                                      \
  do {                                                                  \
    IEC0CLR = _IEC0_INT1IE_MASK;                                        \
  } while(0)

#define CC2520_CLEAR_FIFOP_INT()                                        \
  do {                                                                  \
    IFS0CLR = _IFS0_INT1IF_MASK;                                        \
  } while(0)

#define CC2520_FIFOP_INT_IS_1 (IFS0bits.INT1IF)

#endif /* __CC2520_CONF_H__ */
