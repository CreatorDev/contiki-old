/*
 * Copyright (c) 2016, Imagination Technologies Limited and/or its affiliated group companies.
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
 * 
 * \file   pic32_i2c.c
 * \brief  I2C interface for PIC32MX (pic32mx470f512h)
 * */

#define __I2C_CODE_TEST__  0

#if __I2C_CODE_TEST__
  #ifdef __32MX470F512H__
    #define __USE_I2C__             1
    #define __USE_I2C_PORT1__       1
    #define __USE_I2C_PORT2__       1
  #endif
#endif /* __I2C_CODE_TEST__ */

#ifdef __USE_I2C__

#include <pic32_i2c.h>
/*----------------------------------------------------------------------------------------------*/
#define I2C_PORT(XX)                                                             \
  uint8_t                                                                        \
  i2c##XX##_bus_idle(void)							 \
  {										 \
    while(I2C##XX##CONbits.SEN || I2C##XX##CONbits.PEN                           \
		|| I2C##XX##CONbits.RSEN					 \
		|| I2C##XX##CONbits.RCEN					 \
		|| I2C##XX##CONbits.ACKEN                                	 \
		|| I2C##XX##STATbits.TRSTAT) {					 \
      ;                                                                          \
    }                                                                            \
  return 0;                                                                      \
  }                                                                              \
  uint8_t									 \
  i2c##XX##_init(void)								 \
  {                                                   	 			 \
    IEC1CLR = (_IEC1_I2C##XX##MIE_MASK ) | (_IEC1_I2C##XX##BIE_MASK );       	 \
    IFS1CLR = (_IFS1_I2C##XX##MIF_MASK ) | (_IFS1_I2C##XX##BIF_MASK );       	 \
    I2C##XX##CON = 0;                                                        	 \
    I2C##XX##CONSET = _I2C##XX##CON_SMEN_MASK ;					 \
    return 0;                                                                	 \
  }                                                                              \
  uint8_t									 \
  i2c##XX##_set_frequency(uint32_t baudrate)					 \
  {                             	 					 \
    I2C##XX##BRG = pic32_clock_calculate_brg(2, baudrate);                   	 \
    return 0;                                                                	 \
  }                                                                              \
  uint8_t									 \
  i2c##XX##_byte_send(uint8_t byte) 						 \
  {                                      	 				 \
    I2C##XX##TRN = byte;                                                     	 \
    i2c##XX##_bus_idle();                                                    	 \
    while (I2C##XX##STATbits.TBF) {                                         	 \
      ;                                                                		 \
    }                                                                        	 \
    if(I2C##XX##STATbits.BCL) {                                             	 \
      printf("Collision ocurred, Data is invalid\n");                 		 \
      return 1;                                                     	  	 \
    }                                                                        	 \
    if(I2C##XX##STATbits.ACKSTAT) {                                         	 \
      printf(" NACK recived\n");                                       		 \
      return 1;                                                       		 \
    }                                                                        	 \
    return 0;                                                                	 \
  }                                                                              \
  uint8_t									 \
  i2c##XX##_burst_send(uint8_t *ptr, uint8_t length) 				 \
  {                     	 						 \
    while(length) {                                                        	 \
    if(i2c##XX##_byte_send(*ptr))                                            	 \
    return 1;                                                                	 \
    ptr++;                                                          	 	 \
    length--;                                                        	 	 \
    }                                                                       	 \
    return 0;                                                                	 \
  }                                                                              \
  uint8_t									 \
  i2c##XX##_byte_receive(uint8_t *data)						 \
  {                                  	 					 \
    I2C##XX##CONSET = _I2C##XX##CON_RCEN_MASK;                               	 \
    i2c##XX##_bus_idle();                                                    	 \
    while (!I2C##XX##STATbits.RBF) {                                         	 \
      ;                                                                		 \
    }                                                                        	 \
    if(I2C##XX##STATbits.BCL) {                                             	 \
      printf("Collision ocurred, Data is invalid\n");                  		 \
      return 1;                                                        		 \
    }                                                                        	 \
    I2C##XX##CONbits.ACKEN = 1;                                                  \
    i2c##XX##_bus_idle();                                                    	 \
    *data = I2C##XX##RCV & 0x000000ff;                                       	 \
    return 0;                                                                	 \
  }                                                                              \
  uint8_t									 \
  i2c##XX##_burst_receive(uint8_t *ptr, uint8_t length)				 \
  {                  	 							 \
    while(length) {                                                         	 \
    if(i2c##XX##_byte_receive(ptr)) {                                            \
      return 1;                                                                  \
    }										 \
    ptr++;                                                         	         \
    length--;                                                        	 	 \
    }                                                                        	 \
    return 0;                                                                	 \
  }                                                                              \
  uint8_t									 \
  i2c##XX##_send_start(void)							 \
  {                                             	 			 \
    I2C##XX##CONSET = _I2C##XX##CON_SEN_MASK;                                	 \
    while(I2C##XX##CONbits.SEN) {                                           	 \
      ;                                                                		 \
    }                                                                        	 \
    return 0;                                                                	 \
  }                                                                              \
  uint8_t									 \
  i2c##XX##_send_repeated_start(void)						 \
  {                                    	 					 \
    I2C##XX##CONSET = _I2C##XX##CON_RSEN_MASK;                               	 \
    while (I2C##XX##CONbits.RSEN) {                                          	 \
      ;                                                                		 \
    }                                                                        	 \
    return 0;                                                                	 \
  }                                                                              \
  uint8_t									 \
  i2c##XX##_send_stop(void)							 \
  {                                              	 			 \
    I2C##XX##CONSET = _I2C##XX##CON_PEN_MASK;                                	 \
    while (I2C##XX##CONbits.PEN) {                                           	 \
      ;                                                                		 \
    }                                                                        	 \
    return 0;                                                                	 \
  }                                                                              \
  uint8_t									 \
  i2c##XX##_master_disable(void)						 \
  {                                          	 				 \
    I2C##XX##CONCLR = _I2C##XX##CON_ON_MASK;                                 	 \
    return 0;                                                                	 \
  }                                                                              \
  uint8_t									 \
  i2c##XX##_master_enable(void)							 \
  {                                           	 				 \
    I2C##XX##CONSET = _I2C##XX##CON_ON_MASK;                                 	 \
    return 0;                                                                    \
  }                                                                            
/*--------------------------------------------------------------------------------------------*/

#ifdef __32MX470F512H__
  #ifdef __USE_I2C_PORT1__
  I2C_PORT(1)
  #endif /* __USE_I2C_PORT1__ */

  #ifdef __USE_I2C_PORT2__
  I2C_PORT(2)
  #endif /* __USE_I2C_PORT2__ */
#endif

#endif /* __USE_I2C__ */
