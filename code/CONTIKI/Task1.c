/*
 * Copyright (c) 2007, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *      Task1. playing with rime broadcast and sensors. 
 *      
 *      references> 
 *      
 *           http://contiki.sourceforge.net/docs/2.6/a00009.html#_a2
 *           http://contiki.sourceforge.net/docs/2.6/a01782.html
 *      
 *      
 *      About sensors>
 * 
 *         http://contiki.sourceforge.net/docs/2.6/a00226_source.html
 *         http://contiki.sourceforge.net/docs/2.6/a00151_source.html
 * 
 * 
 *      Sensor functions>
 *      
 *      Each sensor has a set of functions for controlling it and query it for its state. 
 *      Some sensors also generate an events when the sensors change. A sensor must be activated 
 *      before it generates events or relevant values.
 *      
 *      SENSORS_ACTIVATE(sensor) - activate the sensor
 *      SENSORS_DEACTIVATE(sensor) - deactivate the sensor
 *      sensor.value(0) - query the sensor for its last value
 *      sensors_event - event sent when a sensor has changed (the data argument will referer to the actual sensor)
 *      Example for querying the button:
 *      
 *      SENSORS_ACTIVATE(button_sensor) - activate the button sensor
 *      button_sensor::value(0) - the button has been pressed or not
 *      
 *      
 *      
 * \modified by
 *         Sergio Gonzalez Collado
 */

#include "contiki.h"
#include "net/rime.h"
#include "net/rime/trickle.h"
#include "random.h"

#include "dev/button-sensor.h"

#include "dev/leds.h"

#include <stdio.h>


#define SEND_INTERVAL		(5 * CLOCK_SECOND)


/*---------------------------------------------------------------------------*/
PROCESS(example_task1,  "Task1assigment");
AUTOSTART_PROCESSES(&example_task1);
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
PROCESS_THREAD(example_task1 , ev, data)
{
 /*definition timing structures*/
  static struct etimer periodic_timer;

  PROCESS_EXITHANDLER(broadcast_close(&broadcast);)

  PROCESS_BEGIN();

  broadcast_open(&broadcast, 129, &broadcast_call);

  /*definition and init setting of periodic timer*/
  etimer_set(&periodic_timer, SEND_INTERVAL);

  SENSORS_ACTIVATE(button_sensor);
 
  while(1) {
    PROCESS_WAIT_EVENT_UNTIL( etimer_expired(&periodic_timer) 
				 && ev == sensors_event 
				 && data == &button_sensor);

    /*timer reset*/
    etimer_reset(&periodic_timer);

    packetbuf_copyfrom("Hi there!",13);
    broadcast_send(&broadcast);
    printf("broadcast message sent\n");

  }
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/	
