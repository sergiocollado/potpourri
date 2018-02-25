/*
* Copyright (c) 2007, Swedish Institute of Computer Science.
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
* 3. Neither the name of the Institute nor the names of its contributors
*    may be used to endorse or promote products derived from this software
*    without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
* SUCH DAMAGE.
*
* This file is part of the Contiki operating system.
*/

 

/**
* \file
*         Modified - Demonstrating the energest application with broadcasts
* \author
*         Adam Dunkels <adam@sics.se>
*
* \modified+
*         Sergio G Cllado @ Contiki2.7
*/

/* The makefile should be as follows:
CONTIKI_PROJECT = example-MyEnergestExample
CONTIKI = /home/user/contiki
CFLAGS	+= -DPROJECT_CONF_H=\"project-conf.h\"
all: $(CONTIKI_PROJECT)

include	$(CONTIKI)/Makefile.include
*/

/*the project-conf.h should be as follows
#define NETSTACK_CONF_RDC_CHANNEL_CHECK_RATE	4
#define NETSTACK_CONF_MAC	csma_driver // Define the MAC driver to use
#define NETSTACK_CONF_RDC	contikimac_driver // Define the RDC driver to use
*/

/* The Target is the Tmote sky board. According the datasheet, the consuption are:
*
*      Supply Voltage Max: 3.6 V
*      Current consumption: MCU on, radio Rx: 23 mA
*      Current consumption: MCU on, radio Tx: 21 mA
*      Current consumption: MCU on, radio off: 2400 uA
*      Current consumption: MCU idle, radio off: 1200 uA
*      Current consumption: MCU standby: 21 uA
*
*      reference: http://www.eecs.harvard.edu/~konrad/projects/shimmer/references/tmote-sky-datasheet.pdf
*/    

//building instructions: run: $$make TARGET=sky clean &&  make TARGET=sky example-powertrace

#include "contiki.h"
#include "net/rime.h"
#include "net/mac/rdc.h"
#include "net/mac/mac.h"
#include "net/mac/contikimac.h"
#include "net/mac/csma.h"
#include "sys/energest.h"
#include "random.h"
#include "dev/button-sensor.h"
#include "dev/leds.h"
#include <stdio.h>

//reference for network layers:   http://anrg.usc.edu/contiki/index.php/MAC_protocols_in_ContikiOS


/*---------------------------------------------------------------------------*/

PROCESS(example_broadcast_process, "BROADCAST example");

AUTOSTART_PROCESSES(&example_broadcast_process);

/*---------------------------------------------------------------------------*/

static void

broadcast_recv(struct broadcast_conn *c, const rimeaddr_t *from)

{
  printf("broadcast message received from %d.%d: '%s'\n",

         from->u8[0], from->u8[1], (char *)packetbuf_dataptr());
}

static const struct broadcast_callbacks broadcast_call = {broadcast_recv};

static struct broadcast_conn broadcast;

/*---------------------------------------------------------------------------*/

PROCESS_THREAD(example_broadcast_process, ev, data)
{

  static struct etimer et;
  clock_time_t time1, time2; //definition in core/sys/clock.h
 
  unsigned long rx_start_duration;
  unsigned long cpu, lpm, transmit, listen, time, radio;

  //for the target, the datasheet max consumption values:

  const unsigned long Vsupply= 3600; //mV
  const unsigned long i_rx = 23000; //uA  - MCU on, radio Rx:   23 mA
  const unsigned long i_tx = 21000; //uA  - MCU on, radio Tx:   21 mA
  const unsigned long i_mcu_on = 2400; //uA -  MCU on, radio off: 2400 uA
  const unsigned long i_mcu_idle = 1200; //uA - MCU idle, radio off: 1200 uA
  const unsigned long i_standby = 21; //uA - MCU standby: 21 uA

  //estimation of energy - zero initialized.

  unsigned long e_tx = 0;
  unsigned long e_rx = 0;
  unsigned long e_mcu_on = 0;
  unsigned long e_low_pwer = 0;

  PROCESS_EXITHANDLER(broadcast_close(&broadcast);)
 
  PROCESS_BEGIN();

  rx_start_duration = clock_seconds();

  broadcast_open(&broadcast, 129, &broadcast_call);

  energest_init();

  printf("PROGRAM STARTED\n");
  printf("CLOCK_SECOND: %lu\n", CLOCK_SECOND);

  while(1) {

	    //set the time to just 5 seconds. So when printing the output, this 
	    //should be pi
	    etimer_set(&et , CLOCK_SECOND * 5);  

	    time2 = clock_time()/CLOCK_SECOND;

	    // Flush all energest times so we can read latest values
	    // reference: https://github.com/contiki-ng/contiki-ng/wiki/Documentation:-Energest
            //by the way.- this also resets the variable time2 :(
	    //energest_flush();  

	    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

	    time1 = clock_time()/CLOCK_SECOND;

	    packetbuf_copyfrom("Hello!", 7);
	    broadcast_send(&broadcast);

	    rx_start_duration = clock_seconds();
	 
	    cpu = energest_type_time(ENERGEST_TYPE_CPU);
	    lpm = energest_type_time(ENERGEST_TYPE_LPM);
	    transmit = energest_type_time(ENERGEST_TYPE_TRANSMIT);
	    listen = energest_type_time(ENERGEST_TYPE_LISTEN);


	    time = cpu + lpm;
	    radio = transmit + listen;

	    /*for the target (sky mote), the datasheet max consumption values:
	    Vsupply= 3600; //mV
	    i_rx = 23000; //uA  - MCU on, radi o Rx:       23 mA
	    i_tx = 21000; //uA  - MCU on, radio Tx:       21 mA
	    i_mcu_on = 2400; //uA -  MCU on, radio off: 2400 uA
	    i_mcu_idle = 1200; //uA - MCU idle, radio off: 1200 uA
	    i_standby = 21; //uA - MCU standby: 21 uA
	    */

	    e_tx = (transmit)*Vsupply*i_tx/CLOCK_SECOND/1000000;
	    e_rx = (listen)*Vsupply*i_rx/CLOCK_SECOND/1000000;
	    e_mcu_on = (cpu)*Vsupply*i_mcu_on/CLOCK_SECOND/1000000;
	    e_low_pwer = (lpm)*Vsupply*i_standby/CLOCK_SECOND/1000000;

	    //the units will be: mV*uA = 1e-3*1e-6 W = 1e-9 W = nanoWatts

	    printf("\n(mW): Etx %lu      Erx %lu        Eon %lu          Elwp %lu      time %lu(s)", e_tx, e_rx, e_mcu_on, e_low_pwer, time1);

	    energest_type_set(ENERGEST_TYPE_CPU, 0);
	    energest_type_set(ENERGEST_TYPE_LPM, 0);
	    energest_type_set(ENERGEST_TYPE_TRANSMIT,0);
	    energest_type_set(ENERGEST_TYPE_CPU, 0);
	    energest_type_set(ENERGEST_TYPE_LISTEN, 0);
	    
  }
 

  PROCESS_END();

}

/*---------------------------------------------------------------------------*/