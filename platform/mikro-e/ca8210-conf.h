/*
 * Copyright (c) 2016, Cascoda Limited
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*---------------------------------------------------------------------------*/
// CA8210 Interrupt Mapping to PIC32 INT1
/*---------------------------------------------------------------------------*/

#ifndef CA8210_CONF_H
#define CA8210_CONF_H

#undef DEBUG /* Conflict with a macro named DEBUG defined in compiler */
#include <p32xxxx.h>
#undef DEBUG

#include <pic32_gpio.h>
#include <pic32_irq.h>


/*---------------------------------------------------------------------------*/
// Initialise Interrupt
/*---------------------------------------------------------------------------*/
#define CA8210_IRQN_INIT()                                               \
  {                                                                      \
  IFS0CLR = _IFS0_INT1IF_MASK;                                           \
  INTCONCLR = _INTCON_INT1EP_MASK;                                       \
  IPC1CLR = _IPC1_INT1IP_MASK | _IPC1_INT1IS_MASK;                       \
  IPC1SET = (6 << _IPC1_INT1IP_POSITION) | (3 << _IPC1_INT1IS_POSITION); \
  IEC0SET = _IEC0_INT1IE_MASK;                                           \
  }


/*---------------------------------------------------------------------------*/
// Enable Interrupt
/*---------------------------------------------------------------------------*/
#define CA8210_IRQN_ENABLE()                                             \
  {                                                                      \
  IFS0CLR = _IFS0_INT1IF_MASK;                                           \
  IEC0SET = _IEC0_INT1IE_MASK;                                           \
  }


/*---------------------------------------------------------------------------*/
// Disable Interrupt
/*---------------------------------------------------------------------------*/
#define CA8210_IRQN_DISABLE()                                            \
  {                                                                      \
  IEC0CLR = _IEC0_INT1IE_MASK;                                           \
  }


/*---------------------------------------------------------------------------*/
// Clear Interrupt
/*---------------------------------------------------------------------------*/
#define CA8210_IRQN_CLEAR()                                              \
  {                                                                      \
  IFS0CLR = _IFS0_INT1IF_MASK;                                           \
  }


#endif /* CA8210_CONF_H */
