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

  /* Uart1 Rx : RPF4 */
  TRISFSET = _TRISF_TRISF4_MASK;
  U1RXR = 0b0010;

  /* Uart1 Tx : RPF5 */
  TRISFCLR = _TRISF_TRISF5_MASK;
  RPF5R = 0b0011;

  /* TODO : Configure SPI and other pins */

  /* Lock again */
  CFGCONbits.IOLOCK=1;
  SYSKEY = 0;

  /* Enable interrupts */
  ASM_EN_INT;
}

/*---------------------------------------------------------------------------*/
