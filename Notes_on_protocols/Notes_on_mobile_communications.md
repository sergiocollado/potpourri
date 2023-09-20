## Some nomenclature:

- Time Division Multiple Access (TDMA)
- Orthogonal Frequency-Division Multiplexing (OFDM)
- Code Division Multiple Access (CDMA)
- Internet protocol (IP)
- General packet radio service (GPRS)
- Global System for Mobile Communications (GSM)
- evolution of UMTS referred to as Long Term Evolution (LTE)
- Internet Engineering Task Force (IETF)
- Mobile IP
- 3rd Generation Partnership Project (3GPP)
- 3rd Generation Partnership Project 2 (3GGP/2)
- Worldwide Interoperability for Microwave Access (WiMAX)


# Mobile communications evolution


It started with AMPS (Advanced Mobile Phone System)  this was the first generation of mobile cellular phone systems. This used an Analog technology based in FDMA (Frequency Division Multiple Access), it was developed by Bell Labs (1983): 

The second generation was GSM (Global system for Mobile Communications) and it was based in digital electronics. (1991). It allows for TDMA (Time Division Multiple Access) and FDMA at the same time. And like it is based in digital systems, is more robust against interferences. GSM had voice communications, but also data transfer up to 9.6 kbps, and SMS (Short Message Service), and used SIM (Subscriber Identity Module) cards, that contain the user subscription information and phone books. 

The next evolution is the IS-95 (Interim Standard -1995) which is the first 2G with CDMA (Code Division Multiple Access) that improves the performance against interference of other devices and signal fading (multipath). It supports voice and data up to 14.4 kbps

Next follows UMTS (Universal Mobile Telecommunication System), this is the 3G. It is supported by UTRA (UMTS Terrestrial Radio Access) that supports several terrestrial interfaces. Multi-user access in UTRA can be done by UTRA-FDD (Frequency Division Duplex)  or UTRA-TDD (Time Division Duplex); follows WCDMA (Wideband Code Division Multiple Access) based in UTRA-FDD. The data rate in 3Gpp ( 3rd Generation Partnership Project) reaches up to 2 Mbps (release 99): 

UMTS evolves for faster packet speeds in the HSDPA (High Speed Downlink Packet Access). Downlink means from the base station to the mobile device. The data rates reach 14 Mbps. Next came the HSDPA+ (Evolved High Speed Downlink Packet Access) is the first time MIMO (usage of multiple antennas) and a 64 QAM, is used. 

The next technology leap is LTE (Long Term Evolution). Its peak data rate is (release 8) downlink 300 Mbps  and uplink 65 Mbps. From its evolution LTE-A (LTE Advanced) is considered already as 4G. With data rates as downlink 3 Gbps  and uplink 1.5 Gbps

https://en.wikipedia.org/wiki/Comparison_of_mobile_phone_standards

https://www.3gpp.org/

## A brief description of a mobile network:

reference: https://patents.google.com/patent/US9479917B1/en

A typical mobile service provider network, or “mobile network,” includes a core packet-switched network, a transport network, and one or more radio access networks. The core packet-switched network for the mobile network establishes logical connections, known as bearers, among the many service nodes on a path between a wireless device, attached to one of the radio access networks, and a packet data network (PDN). The service nodes then utilize the bearers to transport subscriber traffic exchanged between the wireless device and the PDN, which may include, for example, the Internet, an enterprise intranet, a layer 3 VPN, and a service provider's private network. Various PDNs provide a variety of packet-based data services to wireless devices to enable the wireless devices to exchange service data with application or other servers of the PDNs. In addition, while primarily described with respect to service providers and mobile service provider networks, a mobile network may be deployed by many different types of entities, including enterprises and government agencies. Accordingly, the term “mobile network” may be used herein to encompass many different types of cellular network architectures and operators.


Mobile networks perform detailed and accurate monitoring of service usage so that proper charging information can be generated for potentially millions of customers in order to provide revenue for the service providers. In general, there are three distinct aspects to the process that translates service use into a bill for services—charging, rating and billing. Charging gathers statistics regarding service usage for each customer. Rating is the process of determining how much each service used costs each particular customer according to the service contract. Billing is the process of generated a customer's invoice for services.
The mobile network gateway anchors subscriber sessions and executes network access control functions including charging control (also known as Policy and Charging Enforcement Function for 3GPP networks), which refers to the process of associating packets that belong to a service data flow to a charging key and applying online charging and/or offline charging, as appropriate (a charging key includes information used by the charging online and offline charging servers for rating purposes). Accordingly, the mobile network gateway collects charging information related to the external data network usage and to network resource usage, such as the amount of data categorized by quality of service (QoS), the user protocols, and the usage of the packet data protocol (PDP) address.


A mobile network gateway typically cooperates with online and offline charging server to perform the charging and rating processes in order to generate the charging information. In general, offline charging denotes a charging mechanism in which charging information does not affect, in real-time, the service(s) rendered. The network reports resource usage to the billing domains after the resource usage has occurred. By contrast, online charging can affect, in real-time, the service(s) rendered and therefore requires a direct interaction between the mobile network gateway and the online charging server for subscriber session and/or service(s) control. An online charging server typically maintains subscriber accounts that may be queried prior to granting permission to use requested network resources.


One application of online charging is credit control, in which delivery of subscriber services to a subscriber by the mobile network is predicated upon adequate credit in the form of a prepaid subscription, for instance. Example subscriber services include network (e.g., Internet) access, Session Initiation Protocol (SIP) services, messaging services, gaming services, and download services. For credit control, the mobile network gateway and online charging server cooperate to debit subscriber credit by rating services rendered in real-time and monitoring the subscriber account to ensure adequate credit prior to initiation of a chargeable event. The mobile network gateway and online charging server may deny the subscriber access to the requested service in the absence of adequate credit.


A single subscriber may use multiple services accessible by the mobile service provider network as part of a subscriber session. For example, during a single network access session of a subscriber session, a subscriber may use several Hypertext Transfer Protocol (HTTP) services. In some cases, the multiple services of the network access session may be subject to different cost and therefore require differential rating. To improve scalability for such scenarios, the mobile network gateway is able to consolidate different services that are subject to the same cost and rating type into a rating group, which is associated with a charging key. A subscriber session can include one or more rating groups each associated with one or more services for which the mobile network gateway applies credit control, i.e., associating packets to a rating group charging key for the services and applying online or offline charging, as appropriate. Aside from rating however, other attributes and actions of a multi-service subscriber session, such as quality of service (QoS), event triggers, and credit control failure handling, are common to all the services carried within the session bearer and are applied at the bearer level


# Notes on 5G

references:
- https://www.3gpp.org/technologies/5g-system-overview
- https://www.etsi.org/technologies/5G
- System architecture for the 5G System:  https://portal.3gpp.org/desktopmodules/Specifications/SpecificationDetails.aspx?specificationId=3144
- https://www.techtarget.com/searchnetworking/feature/An-overview-of-3GPP-5G-releases-and-what-each-one-means#:~:text=3GPP%20meets%20four%20times%20a,user%20needs%20evolve%20over%20time.
- https://en.wikipedia.org/wiki/5G
- https://mobilepacketcore.com/5g-introduction/

- simple 5g architecture video: https://www.youtube.com/watch?v=Q6YxHz_07zk


5G is the 5th generation of mobile networks. It offers highier data rates, and
lower latencies that previous generation. Also new user cases, that didn't exist 
in previous generations.

## 5G main new uses

- eMMB: Enhaced Mobile Broad-Band: Provides connections up to 10 Gbps, instead 1 Gbps as in 4G.
- mMTC: Massive Machine Type Communications: used to connect massive number of device, for example for IoT. Provides connection for 1000000 devices per km^2, compared to 100000 in 4G. 
- URLLC: Ultra-Reliable and Low Latency Communications: Latency coud be 1 ms, instead of 10 ms in 4G. This could be usefull for self-driving cars, drone controls ... 

## Network functions

The 5G System architecture consists of the following network functions (NF):
-	Authentication Server Function (AUSF): The AUSF authenticates UEs and stores authentication keys.
-	Access and Mobility Management Function (AMF): AMF receives all connection and session related information from the User Equipment (UE) (N1/N2) but is responsible only for handling connection and mobility management tasks. All messages related to session management are forwarded over the N11 reference interface to the Session Management Function (SMF). 
-	Data Network (DN), e.g. operator services, Internet access or 3rd party services.
-	Unstructured Data Storage Function (UDSF).
-	Network Exposure Function (NEF).
-	Network Repository Function (NRF): The NRF supports discovery mechanisms that allows 5G elements to discover each other and get updated status of the desired elements. The NRF supports the following functions: Maintains the profiles of the available NF instances and their supported services in the 5G core network.
-	Network Slice Admission Control Function (NSACF).
-	Network Slice-specific and SNPN Authentication and Authorization Function (NSSAAF).
-	Network Slice Selection Function (NSSF).
-	Policy Control Function (PCF).
-	Session Management Function (SMF): SMF is responsible for selecting an appropriate UPF during the setup of a PDU session. Selection for appropriate UPF depends upon appropriate load, geographic location, PDU session type etc. SMF is responsible for selecting an appropriate Policy Control Function (PCF) during setup of a PDU session. It is equivalent aprox to PGW in 4G. 
-	Unified Data Management (UDM).
-	Unified Data Repository (UDR).
-	User Plane Function (UPF).
-	UE radio Capability Management Function (UCMF).
-	Application Function (AF).
-	User Equipment (UE).
-	(Radio) Access Network ((R)AN).
-	5G-Equipment Identity Register (5G-EIR).
-	Network Data Analytics Function (NWDAF).
-	CHarging Function (CHF).
-	Time Sensitive Networking AF (TSN AF).
-	Time Sensitive Communication and Time Synchronization Function (TSCTSF).
-	Data Collection Coordination Function (DCCF).
-	Analytics Data Repository Function (ADRF).
-	Messaging Framework Adaptor Function (MFAF).
-	Non-Seamless WLAN Offload Function (NSWOF).
NOTE:	The functionalities provided by DCCF and/or ADRF can also be hosted by an NWDAF.
-	Edge Application Server Discovery Function (EASDF).
The 5G System architecture also comprises the following network entities:
-	Service Communication Proxy (SCP).
-	Security Edge Protection Proxy (SEPP).
The functional descriptions of these Network Functions and entities are specified in clause 6.
-	Non-3GPP InterWorking Function (N3IWF).
-	Trusted Non-3GPP Gateway Function (TNGF).
-	Wireline Access Gateway Function (W-AGF).
-	Trusted WLAN Interworking Function (TWIF).


## Comparation nodes between 4G and 5G:


| 5G \ 4G |  MME  |  S-GW  |  P-GW  |  HSS  |  PCRF  |  AF   |  New  |  Name |
| :---    | :---| |  :---: | :---:  | :---: | :---:  | :---: | :---: | :---  |
|  AMF    |   X   |        |        |       |        |       |       |  Access and Movility Management Function     |
|  SMF    |   X   |        |   X    |       |        |       |       |  Session Management Function     |
|  UPF    |       |    X   |   X    |       |        |       |       |  User Plane Function     |
|  PCF    |       |        |        |       |    X   |       |       |  Policy Control Function     |
|  AUSF   |       |        |        |   X   |        |       |       |  Authentication Server Function     |
|  UDM    |       |        |        |   X   |        |       |       |  Unified Data Management      |
|  AF     |       |        |        |       |        |   X   |       |  Application Function     |
|  NEF    |       |        |        |       |        |       |   X   |  Network Exposure Function     |
|  NRF    |       |        |        |       |        |       |   X   |  Network Repository Function     |
|  NSSF   |       |        |        |       |        |       |   X   |  Network Slice Selection Function     |


AMF is responsible for movility management. 

HSS is done it both: UDM and AUSF. UDM sends the authentication to AUSF, in order to make the subscriber
authetication during registration. 

SMF (Session Management Function) provides the session management functionality. SMF also does the job of giving IPs to the UE (user equipment).

UPF ( User Plane Function) has some functions of 4G S-GW and P-GW. Those were responsible for data traffic, and UPF handles that data transport. 
So the data traffic comes from UE to the UPF, so UPF can be thought as the gateway to internet or other networks.

Subscriber autentication during registration is managed by AUSF, wich obtains authentication vectors from UDM. 
AUSF and UDM substitute the functionality of HSS in 4G.

UDM is responsbile for generating the authentication vectors (requested by AUSF) with is similar to 4G MME. It
does this using the subscriber profiles stored in UDR. UDR is like a database to store subscriber's information, 
aplication specific data, and policies data.

Policy control is similar to the one in 4G core network but in 5G it is controllerd by PCF and PCF has someextra an new
functions compared to PCRF in 4G. 

AMF request the PCF the access and mobility policies. One of the fucntionalities of PCF is make resources reservations, 
for other services using HTTP, or XML based interface. 

NSSF is a new core network functionality in 5G, its goal is to provide a virtual network slices of RAN, core and transfer
networks.

NEF (Network Exposure Function) and Network Function Repository Function (NRF) are new functions introduced in 5G. 

## Network repository function: NRF

It is a database reporsitory that keeps the information of all network functions in the network provider. 

It enables discovery of services. 

reference: https://www.etsi.org/deliver/etsi_ts/129500_129599/129510/16.04.00_60/ts_129510v160400p.pdf

reference: https://www.etsi.org/deliver/etsi_ts/129500_129599/129510/17.06.00_60/ts_129510v170600p.pdf

## Service Communication Proxy: SCP

The Service Communication Proxy (SCP) is a new HTTP/2-based network function enabling dynamic scaling and management of communication 
and services in the 5G network. The SCP has a role that in some ways can be compared with its predecessors, such as the
Signaling Transfer Point (STP), the central signaling router used in 2G and 3G to route SS7 signaling messages, 
as well as the Diameter Signaling Controller (DSC) doing the same for Diameter messages in 4G.
 
A key difference with these legacy routers is that the SCP can be responsible to resolve Network Function (NF) discovery requests
via communication with the Network Repository Function (NRF), and can initiate Domain Name Server (DNS A-record) IP address lookups
to a DNS to locate every live instance for every available Network Function.

reference: https://moniem-tech.com/questions/what-is-service-communication-proxy-scp-in-5g/
reference: https://www.etsi.org/deliver/etsi_ts/129500_129599/129510/17.06.00_60/ts_129510v170600p.pdf


## Access and Mobility function: AMF

references: 

- https://emblasoft.com/blog/exploring-the-3gpp-amf-access-mobility-management-function#:~:text=In%205G%2C%20AMF%20terminates%20the,i.e.%2C%20access%20subscribed%20services).
- https://www.techtrained.com/network-function-access-mobility-management-function-amf-in-5g-core-network-5g-system-5gs/
- https://mobilepacketcore.com/5g-network-architecture/
- https://www.youtube.com/watch?v=eFn1REiUisk
- https://www.youtube.com/watch?v=Q6YxHz_07zk&t=4s



