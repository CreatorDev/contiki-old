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

#include "platform-init.h"
#include <p32xxxx.h>
#include <pic32_irq.h>

/*---------------------------------------------------------------------------*/
void
platform_init()
{
  /* Disable interrupts */
  ASM_DIS_INT;

  /* Unlock sequence */
  SYSKEY = 0;
  SYSKEY = 0xaa996655;
  SYSKEY = 0x556699aa;
  CFGCONbits.IOLOCK=0;

  /* Configure remappable pins */

  /* Uart2 Tx : RPD11 */
  TRISDCLR = _TRISD_TRISD11_MASK;
  RPD11R = 0b0001;

  /* Uart2 Rx : RPB9 */
  ANSELBCLR = _ANSELB_ANSB9_MASK;
  TRISBSET = _TRISB_TRISB9_MASK;
  U2RXR = 0b0101;

  /* Uart3 Tx : RPF4 */
  TRISFCLR = _TRISF_TRISF4_MASK;
  RPF4R = 0b0001;

  /* Uart3 Rx : RPF5 */
  TRISFSET = _TRISF_TRISF5_MASK;
  U3RXR =  0b0010;

  /* SPI1 MISO : RPD3 */
  ANSELDCLR = _ANSELD_ANSD3_MASK;
  TRISDSET = _TRISD_TRISD3_MASK;
  SDI1R = 0b0000;

  /* SPI1 MOSI : RPD4 */
  TRISDCLR = _TRISD_TRISD4_MASK;
  RPD4R = 0b1000;

  /* SPI2 MISO : RPG7 */
  ANSELGCLR = _ANSELG_ANSG7_MASK;
  TRISGSET = _TRISG_TRISG7_MASK;
  SDI2R = 0b0001;

  /* SPI2 MOSI : RPG8 */
  ANSELGCLR = _ANSELG_ANSG8_MASK;
  TRISGCLR = _TRISG_TRISG8_MASK;
  RPG8R = 0b0110;

  #ifdef __USE_CC2520__

    /* INT1 for CC2520 FIFOP: RD5 */
    TRISDSET = _TRISD_TRISD5_MASK;
    INT1R = 0b0110;

  #elif __USE_CA8210

    /* INT1 for CA8210 NIRQ: RD1 */
    TRISDSET = _TRISD_TRISD1_MASK;
    INT1R = 0b0000;

  #endif

  /* Lock again */
  CFGCONbits.IOLOCK=1;
  SYSKEY = 0;

  /* Enable interrupts */
  ASM_EN_INT;
}

/*---------------------------------------------------------------------------*/
