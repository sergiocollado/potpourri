# Mobile communications evolution


It started with AMPS (Advanced Mobile Phone System)  this was the first generation of mobile cellular phone systems. This used an Analog technology based in FDMA (Frequency Division Multiple Access), it was developed by Bell Labs (1983): 

The second generation was GSM (Global system for Mobile Communications) and it was based in digital electronics. (1991). It allows for TDMA (Time Division Multiple Access) and FDMA at the same time. And like it is based in digital systems, is more robust against interferences. GSM had voice communications, but also data transfer up to 9.6 kbps, and SMS (Short Message Service), and used SIM (Subscriber Identity Module) cards, that contain the user subscription information and phone books. 

The next evolution is the IS-95 (Interim Standard -1995) which is the first 2G with CDMA (Code Division Multiple Access) that improves the performance against interference of other devices and signal fading (multipath). It supports voice and data up to 14.4 kbps

Next follows UMTS (Universal Mobile Telecommunication System), this is the 3G. It is supported by UTRA (UMTS Terrestrial Radio Access) that supports several terrestrial interfaces. Multi-user access in UTRA can be done by UTRA-FDD (Frequency Division Duplex)  or UTRA-TDD (Time Division Duplex); follows WCDMA (Wideband Code Division Multiple Access) based in UTRA-FDD. The data rate in 3Gpp ( 3rd Generation Partnership Project) reaches up to 2 Mbps (release 99): 

UMTS evolves for faster packet speeds in the HSDPA (High Speed Downlink Packet Access). Downlink means from the base station to the mobile device. The data rates reach 14 Mbps. Next came the HSDPA+ (Evolved High Speed Downlink Packet Access) is the first time MIMO (usage of multiple antennas) and a 64 QAM, is used. 

The next technology leap is LTE (Long Term Evolution). Its peak data rate is (release 8) downlink 300 Mbps  and uplink 65 Mbps. From its evolution LTE-A (LTE Advanced) is considered already as 4G. With data rates as downlink 3 Gbps  and uplink 1.5 Gbps

https://en.wikipedia.org/wiki/Comparison_of_mobile_phone_standards

https://www.3gpp.org/




## 5G:

## Notes on 5G

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

### 5G main new uses

- eMMB: Enhaced Mobile Broad-Band: Provides connections up to 10 Gbps, instead 1 Gbps as in 4G.
- mMTC: Massive Machine Type Communications: used to connect massive number of device, for example for IoT. Provides connection for 1000000 devices per km^2, compared to 100000 in 4G. 
- URLLC: Ultra-Reliable and Low Latency Communications: Latency coud be 1 ms, instead of 10 ms in 4G. This could be usefull for self-driving cars, drone controls ... 

### Network functions

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
