# NOTES ON MQTT

## Overview

MQTT/3.1 is publish/subscribe messaging transport protocol. Its light, open, simple, and designed to be easy implemented. This make it perfect for constrained applications, as those required for M2M (Machine to Machine) comunications, and IoT (Internet of Things)- where a small code footprint is required, and the network bandwidth is scarce.

Ref: https://xmpp.org/about/standards-process.html <br>
Ref: https://www.linux.com/news/mqtt-iot-communication <br>
Ref: http://docs.oasis-open.org/mqtt/mqtt/v3.1.1/os/mqtt-v3.1.1-os.html <br>
Ref: https://www.hivemq.com/blog/how-to-get-started-with-mqtt <br>

ref: http://www.steves-internet-guide.com/into-mqtt-python-client/

## Main elements of the communication

**Client** 

- the client is the device that always initiates the conexion request with the server, and also disconnects.
- it publish data (application messages), that even other clients might be interested in. The applications messages always have a 'Topic' defined.


**Server**

- accepts connection requests from clients.
- process the subscrition/publish requests from clients, and fowards the application messages to the clients subscribed to that topic.

## Communications propierties, networking, publish/subscribe architecture.

## underlying protocol:

The protocol MQTT/3.1 is a protocol, that must be build on top of another delivery protocols, that handle for him the lower details of the comunication, as for example: the following topics:

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


### Control packets - packet identifer


| CONTROL PACKET | PACKET ID FIELD | PAYLOAD | VALUE | DIRECTION | DESCRIPTION |
| --- | --- | --- | --- | --- | --- | 
| CONNECT | NO | Required | 1 | C -> S | Client request a connection to the Server |
| CONNACK | NO | None | 2 | S -> C | Server acknoledge connection |
| PUBLISH | YES if QoS>0 | Optional | 3 | C <-> S | message publish |
| PUBACK | YES | none | 4  | C <-> S | publish acknoledgment |
| PUBREC | YES | none | 5 | C <-> S | publish received |
| PUBREL | YES | none | 6 | C <-> S | publish released |
| PUBCOMP | YES | none | 7 | C <-> S | publish complete |
| SUBSCRIBE | YES | Required | 8 | C -> S | client subscribe request | 
| SUBACK | YES | Required | 9 | C <- S | Subscribe acknoledgement |
| UNSUBSCRIBE | YES | Required | 10 | C -> S | Unsubscribe request |
| UNSUBACK | YES | none |  11 | C -> S | Unsubscribe acknoledgement |
| PINGREQ | NO | none |  12 | C -> S | Ping request |
| PINGRESP | NO | none |  13 | C <- S | Ping response |
| DISCONNECT | NO | none |  14 | C -> S | Client is disconnecting |

The **value** field is an identifier, defined as a 4 bits (nibble) unsigned integer (range is 0-15)

## Data structure Rules

### Bits
The bits, are defined from 7 to 0, being 7 the most significant one, and 0 the least significant one.

### Integer data values
Integer data values are defined as 16 bit Big Endian. So the MSB (Most Significant Byte) is presented before the LSB (Least Significant Byte).

### Encoded Strings
Strings are encoded following the UTF-8 standard [RFC3629], which is an efficient implementation of Unicode standard.
Each String is prefixed with two bytes expresed in UTF-8 itself, that define the length of the UTF-8 string. As a result this give us
a maximum load of 65535 bytes.

The character data must be a UTF-8 compliant. Any mis-formed data will force the server or the client, to close the connection.
Characters must not include encodings between U+D800 to U+DFFF. Also the codes between: U+0001..U+001F, and U+007F..U+009F (which are
used as control characters), may cause to close the network connection.


