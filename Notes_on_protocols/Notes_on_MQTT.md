# NOTES ON MQTT

## Overview

MQTT/3.1 is publish/subscribe messaging transport protocol. Its light, open, simple, and designed to be easy implemented. This make it perfect for constrained applications, as those required for M2M (Machine to Machine) comunications, and IoT (Internet of Things)- where a small code footprint is required, and the network bandwidth is scarce.

Ref: https://xmpp.org/about/standards-process.html <br>
Ref: https://www.linux.com/news/mqtt-iot-communication <br>
Ref: http://docs.oasis-open.org/mqtt/mqtt/v3.1.1/os/mqtt-v3.1.1-os.html <br>

## Main actors

**Client** 

- the client is the device that always initiates the conexion request with the server, and also disconnects.
- it publish data (application messages), that even other clients might be interested in. The applications messages always have a 'Topic' defined.


**Server**

- accepts connection requests from clients.
- process the subscrition/publish requests from clients, and fowards the application messages to the clients subscribed to that topic.

## Communications propierties, networking, publish/subscribe architecture.

## underlying protocol:

The protocol MQTT/3.1 is a protocol, that must be build on top of another delivery protocols, that handle for him, the following topics:

- order of messages
- lossless transmission.
- data streamming from/to client/server.

As example MQTT, have worked with the following delivery protocols:

- TCP/IP [RFC793].
- TLS [RFC5246].
- WebSocket [RFC6455]

Watch Out!! Conectionless protocols as UDP, are not suitable for MQTT: they may loss data without warning!

## application messages

The application messages, must comply with some rules, these are:

- **Topic**: The device that needs it, shall subscribe to de needed 'Topic'. A 'Topic' refers to a _Topic name_ or a _Topic filter_, a topic filter, may be a reg expression. 
- **Control packets**: The type of the application message is specified by the field of 'control packet'. The most common is the PUBLISH one.
- **Quality of Service (QoS)**: - each subscription must have a maximum QoS associated to it.
- **Session**: when the is a state mantained in the system, it is call a session. Depending on the configuration it can last only during the conecction-disconnection, or longer.


### QoS levels

(QoS) stands for Quality of Service.

There are defined the following levels of QoS:

- [QoS 0]: At most once delivery.
- [QoS 1]: At least once delivery.
- [QoS 2]: Exactly once delivery.

The definition says it all.



