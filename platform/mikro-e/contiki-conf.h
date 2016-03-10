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

#ifndef CONTIKI_CONF_H
#define CONTIKI_CONF_H

#include <inttypes.h>
#include "cc2520-conf.h"

/* Include project config file if defined in the project Makefile */
#ifdef PROJECT_CONF_H
  #include "project-conf.h"
#endif /* PROJECT_CONF_H */

#define CCIF
#define CLIF

typedef uint16_t uip_stats_t;
typedef uint32_t clock_time_t;
typedef uint32_t rtimer_clock_t;

#define RTIMER_CLOCK_LT(a,b) ((int32_t)((a)-(b)) < 0)

#define CLOCK_CONF_SECOND                       1024

#define NETSTACK_CONF_WITH_IPV6                 1
#define NETSTACK_CONF_RADIO                     cc2520_driver
#define NETSTACK_CONF_FRAMER                    framer_802154
#ifndef NETSTACK_CONF_RDC
  #define NETSTACK_CONF_RDC                     nullrdc_driver
#endif
#define NETSTACK_CONF_MAC                       nullmac_driver
#define NETSTACK_CONF_NETWORK                   sicslowpan_driver
#ifndef RF_CHANNEL
  #define RF_CHANNEL                            26
#endif
#ifndef IEEE802154_PANID
  #define IEEE802154_PANID                      0xABCD
#endif
//#define FIXED_MAC_ADDRESS                     0xDEADBEEFDEADBEEF

#define UIP_CONF_ROUTER                         0
#define LINKADDR_CONF_SIZE                      8
#ifndef UIP_CONF_BUFFER_SIZE
  #define UIP_CONF_BUFFER_SIZE                  1024
#endif

/* UDP configuration options */
#define UIP_CONF_UDP                            1
#define UIP_CONF_UDP_CHECKSUMS                  1
#define UIP_CONF_UDP_CONNS                      10

/* 6lowpan options (for ipv6) */
#define SICSLOWPAN_CONF_COMPRESSION             SICSLOWPAN_COMPRESSION_HC06
#define SICSLOWPAN_CONF_MAX_ADDR_CONTEXTS       2
#define SICSLOWPAN_CONF_COMPRESSION_THRESHOLD   63
#define SICSLOWPAN_CONF_FRAG                    1
#define SICSLOWPAN_CONF_MAXAGE                  8


/* General uip configuration options */
#define UIP_CONF_STATISTICS                     0
#define UIP_CONF_LOGGING                        0
#define UIP_CONF_BROADCAST                      1
#define UIP_CONF_LLH_LEN                        0
#define UIP_CONF_LL_802154                      1


/*
 * There are 2 red LEDs on the board, LED1 is mapped to the Contiki LEDS_RED
 * and LED2 is mapped to LEDS_GREEN
 */
#define LED1                                    LEDS_RED
#define LED2                                    LEDS_GREEN

#ifndef GLOBAL_IPv6_ADDR
  #define GLOBAL_IPv6_ADDR1                     0x2001
  #define GLOBAL_IPv6_ADDR2                     0x1418
  #define GLOBAL_IPv6_ADDR3                     0x0100
  #define GLOBAL_IPv6_ADDR4                     0x823c
  #define GLOBAL_IPv6_ADDR5                     0x0
  #define GLOBAL_IPv6_ADDR6                     0x0
  #define GLOBAL_IPv6_ADDR7                     0x0
  #define GLOBAL_IPv6_ADDR8                     0x0
#endif

#endif /* CONTIKI_CONF_H */
