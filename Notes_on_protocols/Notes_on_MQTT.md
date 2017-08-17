# NOTES ON MQTT

## Overview

MQTT/3.1 is publish/subscribe messaging transport protocol. Its light, open, simple, and designed to be easy implemented. This make it perfect for constrained applications, as those required for M2M (Machine to Machine) comunications, and IoT (Internet of Things)- where a small code footprint is required, and the network bandwidth is scarce.

Ref: https://xmpp.org/about/standards-process.html <br>
Ref: https://www.linux.com/news/mqtt-iot-communication <br>
Ref: http://docs.oasis-open.org/mqtt/mqtt/v3.1.1/os/mqtt-v3.1.1-os.html <br>

The protocol MQTT/3.1 is a protocol, that must be build on top of another delivery protocols, that handle for him, the following topics:

- order of messages
- lossless transmission.
- data streamming from/to client/server.

As example MQTT, have worked with the following delivery protocols:

- TCP/IP [RFC793].
- TLS [RFC5246].
- WebSocket [RFC6455]

Watch Out!! Conectionless protocols as UDP, are not suitable for MQTT: they may loss data without warning!

## Main actors

**Client**

**Server**

## QoS levels

(QoS) stands for Quality of Service.

There are defined the following levels of QoS:

- [QoS 0]: At most once delivery.
- [QoS 1]: At least once delivery.
- [QoS 2]: Exactly once delivery.

The definition says it all.



