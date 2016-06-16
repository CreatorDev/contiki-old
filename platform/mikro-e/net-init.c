/**
 * Copyright (c) 2016, Imagination Technologies Limited
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions
 *    and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used to
 *    endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <contiki.h>
#include <contiki-net.h>
#include <net/netstack.h>
#include <net/queuebuf.h>
#include <net/mac/frame802154.h>

#include <lib/random.h>
#include <time.h>
#ifdef __USE_CC2520__
  #include <dev/cc2520/cc2520.h>
#elif  __USE_CA8210__
  #include <dev/ca8210/ca8210-radio.h>
#endif
#define DEBUG 1
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

/*---------------------------------------------------------------------------*/
void
net_init()
{
  uint16_t shortaddr;
  uint64_t longaddr;
  linkaddr_t addr;
  uip_ds6_addr_t *lladdr;
  uip_ipaddr_t ipaddr;
  uint8_t i;

  queuebuf_init();
  #ifdef __USE_CC2520__
    cc2520_init();
  #elif  __USE_CA8210__
    ca8210_init();
  #endif

  memset(&shortaddr, 0, sizeof(shortaddr));
  memset(&longaddr, 0, sizeof(longaddr));
  #ifndef FIXED_MAC_ADDRESS
  #ifdef __USE_CC2520__
    cc2520_get_random((uint8_t *)&longaddr, sizeof(longaddr));
  #elif  __USE_CA8210__
    ca8210_get_random((uint8_t *)&longaddr, sizeof(longaddr));
  #endif
  #else
  longaddr = FIXED_MAC_ADDRESS;
  #endif
  ((uint8_t *)&shortaddr)[0] = ((uint8_t *)&longaddr)[0];
  ((uint8_t *)&shortaddr)[1] = ((uint8_t *)&longaddr)[1];

  memset(&addr, 0, sizeof(linkaddr_t));
  for(i = 0; i < sizeof(addr.u8); ++i) {
    addr.u8[i] = ((uint8_t *)&longaddr)[i];
  }
  linkaddr_set_node_addr(&addr);

  #ifdef __USE_CC2520__
    cc2520_set_channel(RF_CHANNEL);
    cc2520_set_pan_addr(IEEE802154_PANID, shortaddr, (uint8_t *)&longaddr);
  #elif  __USE_CA8210__
    ca8210_init_pib(RF_CHANNEL, IEEE802154_PANID, shortaddr, (uint8_t *)&longaddr);
  #endif

  NETSTACK_RDC.init();
  NETSTACK_MAC.init();
  NETSTACK_NETWORK.init();
  memcpy(&uip_lladdr.addr, &longaddr, sizeof(uip_lladdr.addr));
  process_start(&tcpip_process, NULL);

  lladdr = uip_ds6_get_link_local(-1);
  uip_ip6addr(&ipaddr, GLOBAL_IPv6_ADDR1, GLOBAL_IPv6_ADDR2, GLOBAL_IPv6_ADDR3, GLOBAL_IPv6_ADDR4,
    GLOBAL_IPv6_ADDR5, GLOBAL_IPv6_ADDR6, GLOBAL_IPv6_ADDR7, GLOBAL_IPv6_ADDR8);
  uip_ds6_set_addr_iid(&ipaddr, &uip_lladdr);
  uip_ds6_addr_add(&ipaddr, 0, ADDR_TENTATIVE);

  PRINTF("Short MAC address %02x:%02x\n",
    *((uint8_t *)&shortaddr), *((uint8_t *)&shortaddr + 1));

  PRINTF("Extended MAC address");
  for(i = 0; i < 8; ++i) {
    PRINTF(":%02x", ((uint8_t *)&longaddr)[i]);
  }

  PRINTF("\n%s %s, channel check interval %d Hz, radio channel %u\n",
    NETSTACK_MAC.name,
    NETSTACK_RDC.name,
    NETSTACK_RDC.channel_check_interval(),
    RF_CHANNEL);

  PRINTF("Link address: ");
  for(i = 0; i < sizeof(addr.u8); ++i) {
    PRINTF("%d.", addr.u8[i]);
  }

  PRINTF("\nTentative link-local IPv6 address ");
  for(i = 0; i < 8; ++i) {
    PRINTF(":%02x%02x", lladdr->ipaddr.u8[i * 2], lladdr->ipaddr.u8[i * 2 + 1]);
  }

  PRINTF("\nTentative global IPv6 address ");
  for(i = 0; i < 8; ++i) {
    PRINTF(":%02x%02x", ipaddr.u8[i * 2], ipaddr.u8[i * 2 + 1]);
  }
  PRINTF("\n");
}
/*---------------------------------------------------------------------------*/
