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

#include "contiki.h"
#include "pic32_irq.h"
#include "pic32_spi.h"

/*---------------------------------------------------------------------------*/
/* Definition for disable interrupt method used in cc2520.c */
int
splhigh() {
  ASM_DIS_INT;
  return 0;
}

/*---------------------------------------------------------------------------*/
/* Definition for enable interrupt method used in cc2520.c */
void
splx(int s) {
  ASM_EN_INT;
}

/*---------------------------------------------------------------------------*/
void
cc2520_arch_init(void)
{
  /* Initialise CC2520-SPI port */
  pic32_spi2_init(CC2520_SPI_BAUDRATE, SPI_DEFAULT);

  /* Configure CC2520 Chip select pin */
  GPIO_CONFIGURE_AS_OUTPUT(CC2520_CS_PORT, CC2520_CS_PIN);
  CC2520_SPI_DISABLE();

  /* Configure CC2520 Voltage regulator enable pin */
  GPIO_CONFIGURE_AS_OUTPUT(CC2520_VREG_PORT, CC2520_VREG_PIN);
  SET_VREG_INACTIVE();

  /* Configure CC2520 reset pin */
  GPIO_CONFIGURE_AS_DIGITAL(CC2520_RESET_PORT, CC2520_RESET_PIN);
  GPIO_CONFIGURE_AS_OUTPUT(CC2520_RESET_PORT, CC2520_RESET_PIN);
  SET_RESET_INACTIVE();

  /* Configure CC2520 FIFOP pin */
  GPIO_CONFIGURE_AS_DIGITAL(CC2520_FIFOP_PORT, CC2520_FIFOP_PIN);
  GPIO_CONFIGURE_AS_INPUT(CC2520_FIFOP_PORT, CC2520_FIFOP_PIN);

  /* Configure CC2520 FIFO pin */
  GPIO_CONFIGURE_AS_DIGITAL(CC2520_FIFO_PORT, CC2520_FIFO_PIN);
  GPIO_CONFIGURE_AS_INPUT(CC2520_FIFO_PORT, CC2520_FIFO_PIN);

  /* Configure CC2520 CCA pin */
  GPIO_CONFIGURE_AS_INPUT(CC2520_CCA_PORT, CC2520_CCA_PIN);

  /* Configure CC2520 SFD pin */
  GPIO_CONFIGURE_AS_INPUT(CC2520_SFD_PORT, CC2520_SFD_PIN);

}
/*---------------------------------------------------------------------------*/
