/*
 * Copyright (c) 2016, Imagination Technologies Limited and/or its affiliated
 * group companies.
 *
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
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \file   
 * 	I2C driver for PIC32MX (pic32mx470f512h)
 */

#ifndef INCLUDE_PIC32_I2C_H_
#define INCLUDE_PIC32_I2C_H_

#ifdef __USE_I2C__
/*---------------------------------------------------------------------------*/
#define I2C_DEF(XX)                                          \
  uint8_t i2c##XX##_init();                                  \
  uint8_t i2c##XX##_bus_idle();                              \
  uint8_t i2c##XX##_set_frequency (uint32_t );               \
  uint8_t i2c##XX##_master_enable();                         \
  uint8_t i2c##XX##_master_disable();                        \
  uint8_t i2c##XX##_send_start();                            \
  uint8_t i2c##XX##_send_repeated_start();                   \
  uint8_t i2c##XX##_send_stop();                             \
  uint8_t i2c##XX##_byte_send(uint8_t );                     \
  uint8_t i2c##XX##_byte_receive(uint8_t *);                 \
  uint8_t i2c##XX##_burst_send (uint8_t *, uint8_t );        \
  uint8_t i2c##XX##_burst_receive(uint8_t *, uint8_t );      
/*---------------------------------------------------------------------------*/
               
#ifdef __32MX470F512H__
  #ifdef __USE_I2C_PORT1__
  I2C_DEF(1)
  #endif /* __USE_I2C_PORT1__ */

  #ifdef __USE_I2C_PORT2__
  I2C_DEF(2)
  #endif /* __USE_I2C_PORT2__ */
#endif /* __32MX470F512H__ */

#endif /* __USE_I2C__ */
  
#endif /* INCLUDE_PIC32_I2C_H_ */
