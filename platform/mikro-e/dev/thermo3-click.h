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
 * 	Thermo3 click driver.
 *	http://www.mikroe.com/click/thermo3/
 *
 */

#ifndef __TMP_102_H__
#define __TMP_102_H__

#define I2C_FREQUENCY		100000

#define TMP102_REG_WRITE	0x90
/* TMP102 registers */
#define TMP102_TEMP		0x00    /* read only */
#define TMP102_CONF		0x01    
#define TMP102_TLOW		0x02    
#define TMP102_THIGH		0x03   

#define TMP102_REG_READ		0x91
/*---------------------------------------------------------------------------*/

/*init the i2c bus as per TMP102*/
void tmp102_init();

/*gives value of temperatur in degrees celsius*/
float tmp102_read_temp();

/*every time before opration select proper register*/
void tmp102_reg_select(uint8_t );

/*reads selected register*/
void tmp102_reg_read(uint8_t *);

/*write selected register except TMP102_TEMP*/
void tmp102_reg_write(uint8_t , uint8_t );

/*---------------------------------------------------------------------------*/
#endif /*  __TMP_102_H__ */
