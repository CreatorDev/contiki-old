/**
 * @addtogroup applications
 * @{
 *
 * @defgroup lwm2m_led_app LightWeightM2M Led Application
 * @{
 *
 * This Application registers an led object and communicates with the LWM2M
 * server daemon running on Marduk gateway. LED resource that it hosts can be
 * turned on or off through Marduk gateway.
 *
 * @file lwm2m-led.c
 *
 * @author Imagination Technologies
 *
 * @copyright Copyright (c) 2015, Imagination Technologies Limited
 *
 * All rights reserved.
 *
 * Redistribution and use of the Software in source and binary forms, with or
 * without modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. The Software (including after any modifications that you make to it) must
 *    support the FlowCloud Web Service API provided by Licensor and accessible
 *    at http://ws-uat.flowworld.com and/or some other location(s) that we
 *    specify.
 *
 * 2. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 3. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 4. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this Software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contiki.h"
#include "contiki-net.h"
#include "dev/leds.h"

#include "lwm2m_core.h"
#include "lwm2m_bootstrap.h"
#include "lwm2m_registration.h"
#include "lwm2m_connectivity.h"
#include "lwm2m_security.h"
#include "lwm2m_device.h"
#include "lwm2m_object_store.h"
#include "coap_abstraction.h"
#include "lwm2m_acl.h"
#include "lwm2m_object_defs.h"
#include "lwm2m_types.h"

//! @cond Doxygen_Suppress
#define BOOTSTRAP_SERVER_URL      "coap://[fe80::1]:15685"
#define COAP_PORT                 6000
#define ENDPOINT_NAME             "LedDevice"
#define LOG_LEVEL                 DebugLevel_Debug

#define LED_OBJECT_ID             3306
#define LED_OBJECT_STR            "Actuation"
#define LED_RESOURCE_ID           5850
#define LED_RESOURCE_STR          "led"
#define LED_OBJECT_INSTANCE_ID    0
#define LED_RESOURCE_INSTANCE_ID  0

static int led_state = 0;
PROCESS(lwm2m_led_client, "LWM2M Led Client");
AUTOSTART_PROCESSES(&lwm2m_led_client);
//! @endcond
/*---------------------------------------------------------------------------*/
/**
 * @brief Register the led object to the lwm2m server
 */
static void
register_led_object(ObjectStore *store)
{
  ObjectStore_RegisterObjectType(store, LED_OBJECT_STR, LED_OBJECT_ID,
    MultipleInstancesEnum_Single, MandatoryEnum_Optional);
  ObjectStore_RegisterResourceType(store, LED_RESOURCE_STR, LED_OBJECT_ID,
    LED_RESOURCE_ID, ResourceTypeEnum_TypeBoolean, MultipleInstancesEnum_Single,
    MandatoryEnum_Mandatory, Operations_RW);
}

/*---------------------------------------------------------------------------*/
/**
 * @brief Set led resource value
 */
static void
setup_led_object(ObjectStore *store)
{
  ObjectStore_SetResourceInstanceValue(store, LED_OBJECT_ID,
    LED_OBJECT_INSTANCE_ID, LED_RESOURCE_ID, LED_RESOURCE_INSTANCE_ID,
    &led_state, sizeof(led_state));
}

/*---------------------------------------------------------------------------*/
/**
 * @brief Turn on/off led according to the state of the led resource of LWM2M
 *        object which can be updated by LWM2M server running on Marduk gateway.
 */
static void
update_led_state(ObjectStore *store)
{
  ObjectStore_GetResourceInstanceValue(store, LED_OBJECT_ID,
    LED_OBJECT_INSTANCE_ID, LED_RESOURCE_ID, LED_RESOURCE_INSTANCE_ID,
    &led_state, sizeof(led_state));
  if(led_state) {
    leds_on(LEDS_RED);
  } else {
    leds_off(LEDS_RED);
  }
}

/*---------------------------------------------------------------------------*/
/**
 * @brief Initialize the coap server, bootstrap the device and register the
 *        led object
 */
static Lwm2mContextType*
lwm2m_client_start()
{
  Lwm2m_SetOutput(stdout);
  Lwm2m_SetLogLevel(LOG_LEVEL);
  Lwm2m_PrintBanner();

  CoapInfo* coap = coap_Init("0.0.0.0", COAP_PORT, LOG_LEVEL);
  Lwm2mContextType *context = Lwm2mCore_Init(coap, ENDPOINT_NAME, NULL);

  /* Construct Object Tree */
  Lwm2m_Debug("Construct object tree\n");
  Lwm2m_RegisterObjectTypes(context->Store);
  register_led_object(context->Store);

  LWM2M_example_security(context->Store, BOOTSTRAP_SERVER_URL);
  LWM2M_device_example(context->Store);
  setup_led_object(context->Store);

  return context;
}

/*---------------------------------------------------------------------------*/
/**
 * @brief Application process that hosts an led object and turns on/off an led
 *        on the board according to the state of the led object, which can
 *        be set using LWM2M protocol.
 */
PROCESS_THREAD(lwm2m_led_client, ev, data)
{
  PROCESS_BEGIN();
  static struct etimer et;
  static Lwm2mContextType *context;
  int wait_time;

  context = lwm2m_client_start();

  while(1) {
    wait_time = Lwm2mCore_Process(context);
    etimer_set(&et, (wait_time * CLOCK_SECOND) / 1000);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    update_led_state(context->Store);
  }
  PROCESS_END();
}

/*---------------------------------------------------------------------------*/

/** @} */
/** @} */
