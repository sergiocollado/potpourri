# Notes on 2G: Global System for Mobiles (GSM)

The European Telecommunication Standards institue (ETSI) was formed in 1988, their goal was define the standard for the firs Global System for Mobiles (GSM) in 1991. It is still used in may countries. 

In USA the digital AMPS was used. Nowadays it is obsolete. 

This 2G is a digital system, this means that the voice is digitalized and encrypted. It supports roameing. And it supports SMS (Short Message Service) and roaming. 

## 2G Architecture

![GSM architecture](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/Gsm_network_architecture.png)


 - reference: https://yatebts.com/documentation/concepts/gsm-functionalities/


- **Mobile station (MS)**: the first component, MS, the mobile station consists in the Mobile Equiptment (ME) and the SIM card. The SIM has the identity of the subscriber, and that identity is called IMSI (Interantional Mobile Subscriber Identity)
- **Base Station Subsisteym (BSS)**, the RAN (Radio Acess Network) in GSM is called BSS (Base Station Subsystem). A BSS, consists on a BSC, and a BSC can control more that one BTS. The interface between the BTS and BSC, is called "Abis" interface. And the interface between the BSC and the core network is called the "A" interface.
- **NSS**: The core network (CN) in the case of GSM, is called the Network Subsystem (NSS), and NSS, consists in MSC and its asociated databases: EIR, VLR, HLR, AUC.
- **GMSC**: One mobile network is connected to another network through the Gateway MSC (GMSC), for example with the fixed telephony network: PSTN (Public Switching Network), or with other mobile network which is run by other operator. 

### Base Station Subsystem (BSS)

 - Reference: https://en.wikipedia.org/wiki/Base_station_subsystem

The Base Station Subsystem (BSS) consitst of:
 - One or more Base Station Controllers (BSC)
 - One or more Base Transceiver Stations (BTS)

A RAN (Radio Access Network) may contain one or more BSSs.

The transmissiion between the BSC and the BTS is called as the front-haul link, and this link can be an electrical cable, and microwave link, or optical fibre link. 

### Base Tranceiver Station (BST)

When the mobile station connects with the mobile network, it connects through the Base Tranceiver station (BTS). The BTS contains the radio receiver/transmitter that is used to connect to the mobile station over the wireless channel. Also the digital voice that is being send to the mobile station is encripted in the BTS. While the encrypted voice that is received in the mobile station is being received by the BTS. It is decrypted, the digital voice is send to the mobile statiion, after modulating it as a wireless signal and the type of modulation that is used is GMSK (at ype of frequency shift keying). 

Whenever there is an incomming call for the mobile station the BTS informs, or in other words the BTS pages the mobile station about the incomming call. 

Also whenever a mobile station is in a call with the BTS or in other words, it is connected to the BTS, then it is not only measuring the received power of that BTS, but is also measuring the received power from the neighbouring BTSs. And this information about the other measurements is sent as a measurement reports to the BTS and the BTS, then passes this information to the Base Station Controller (BSC). 


### Base Station Controller (BSC)

A base station controller controls one or more BTSs, the traffic for different mobile stations,that a BSC is receiving from different BTSs, it aggregates that traffic and sends it to the MSC, and the traffic that the BSC is receiving from the MSC for different BTS, it switches the traffic to the corresponding BTSs, also the BSC is responsible for the management of the radio resources in the BSS and what is meant by the management of the radio resources. For example, if this mobile station wants to make a call, then it would meed channels in the Abis interface as well as in the air interface.

Also the BTS is receiving the measurement reports from the mobile station. If a mobile station is in call with a BTS, it is measuring the power of this BTS as well as the power from the neighboring BTSs. And it is sending this information as a measurement report to the BSC. If the mobile station is moving from this BTS to other BTS, which is called "the target BTS", and if the mobile station enters the coverage area of the target BTS, then the power that this mobile station is receiving from the target BTS it would increase from the power that it is receiving from its own BTS. So this information would be then sent as a measurement report to the BSC and the BSC would then decide that now it is time that this mobile station makes a handover to the target BTS. So the BSC would issue the handover command that would be sent to this BTS and then it would be passed on to this mobile station and the mobile station would then hand over to the target BTS.

Also based upon the measurement report, the BSC decides at what power this mobile station is going to transmit towards the base station and at what power, the BTS is going to transmit towards the mobile station, so that this does not cause interference to the mobile stations that are there in the neighboring cells and which are using the same channels.

### Network Subsystem (NSS)

The network subsystem consists of the MSC and its associated databases. And the main purpose of the NSS is to perform the switching and routing of the call, for example, this mobile station is calling someone in the PSTN network, then the NSS would route the call of this mobile station to the PSTN (Public Switching Telephone Network) network.Similarly, this mobile station may roam from one BTS to another BTS. So the NSS keeps track of the current location of the mobile station in the mobile network, so that if there is an incoming call for this mobile station, this mobile station may be paged or it may be informed about that incoming call.

### Mobile Switching Center (MSC)

It is a digital switch that performs: 
 - Call setup
 - Call routing between MS & others MSCs/external network.
 - Inter BSS, inter handovers.

Channel asignation on A interface.

Gateway MSC (GMSC) handles interface with other PLMNs/GMSC

### Home Location Registry (HLR)

Central database for subscriber/mobile users information:
 - Subscriber ID
 - Authentification key
 - Subscriber status (registered/unregistered)
 - Services a mobile subscriber can use)
 - Current location of subscriber (which VLR area)

### Authentification Center (AUC) 

The Authentification center is normally build as a part of the HLR. 

It uses the authentification key to generate parameters for:
 - user authentication/verification
 - generating ciphering key

Required when user initiates connection.

### Visitor Location Registry (VLR)

A PLMN (Public Land Mobile Network) service area, the area covered by a Mobile Network, can be seen as the sum of different MSC areas. 

A VLR may serve one or more MSCs, but normally is 1 VLR with 1 MSC. 

VLR holds temporary data to avoid overburdening HLR. 

### Equipment Identiy Registry (EIC)

The identiy of a user (a mobile subscriber) is stored in the SIM (Subscriber Identification Module) card, the Mobile Equipment has its own identity: IMEI (International Mobile Equipment Identity).

The Equipment Identiy Registry (EIC), has 3 lists:
 - Black list, list of ME (Mobile Equpment) forbidden to use the newtork, for example stolen ME.
 - Grey list, mobiles to have to be under observation or tracing.
 - White list, all the authorized mobile equipment.

When the MS (mobile station) initiates connection with the BTS/BSC, it is check using EIC if the MS is allow to use the network or if it is under observation.


### Operation and Mantenaince Center (OMC) 

 - Monitoring and performance supervision. Fault report and alarm handling.
 - Configuration management.
 - Stores data for minimum of one year.


### GSM channel types

There are two types of channels:
 - physical channesl
 - logical channels (depends upon what type of information)

### GSM Logical channels

- Traffic channels (TCHs)
   - Used for carry voice or data
- Control channels
   - Used for signaling between MS (mobile station) and BTS (Base Transceiver Station)
      - MS registration
      - Handover
      - Call generation
      - Call maintenance
    
 ### Broadcast Control Channels

 When you switch on a mobile station (MS) it captures the most powerful Broadcast Control Channel (BCCH) that it can find. Once it captures that channel, the MS sychronize itself in frequency and time with the Base station. 

 In order to do that the MS captures the frequency correction channel (FCCH) and in this way it synchronizes it frequency with the BS in a correct way. After that it decodes the synchronization channel to synchronize itself with the BS in time, by knowing the frame number of the frame that is currently transmitted. Now the MS has done this, it is able to decode the BCCH, it give the MS the identity of the network and the identity of the BS, and the BS also gets the information required to connect to the newtworkd through this BS. 


 ### Common control channels

 Common control channels are used whenever a MS wants to initizate a call with the network, connect with the BS, whenever the network wants to inform a MS of an incomming call. 

 - Paging channel (PCH)
 - Random access channel (RACH)
 - Access grant channel (AGCH)
 - Standalone dedicated control channel (SDCCH)

### Slow associated Control channel 

Now, whenever a mobile station is in call with the base station, it is assigned a TCH channel, this channel is a bidirectional 
channel that is used to carry data or voice. Now, whenever a TCH channel is assigned to a mobile station in association with this TCH channel.
A Slow Associated Control Channel (SACCH) is also assigned to this mobile station. And this slow associated control channel is bidirectional channel.
And we know that the mobile station, when it is in call with the base station, it is measuring the downlink power from its own base station 
as well as the downlink power from the neighbouring base stations. And it is also measuring the bit error on the TCH channel that has been assigned to this mobile station
in the downlink direction.

And this measurement report is sent in the uplink on the slow associated control channel and the BTS then sends this measurement report to the BSC.
And BSC decides, for example, if this mobile station is moving from this base station to this base station, then based upon the measurement 
reports, the BSC decides that when this mobile station would make hand over to the target base station, and then BSC takes the decision about 
the hand over, the BSC issues, the hand handover command that is sent to the BTS and the BTS sends that hand over command to the mobile station
on the slow associated control channel in the downlink direction and the BSC also decides that at what power this mobile station is going to transmit in the uplink,
so that this mobile station does not cause excessive interference to the mobiles that are in the neighbouring base stations and which are
using the same frequency channels. So these power control commands are issued by the BSC, which are sent to the BTS and BTS then sends those other
control commands on the downlink slow associated control channel to the mobile station. And when the call finishes with the release of the TCH 
channel, this Slow Associated Control Channel is also released by the base station.

### GSM Call Flow For Outgoing calls

references:
 - https://yatebts.com/documentation/concepts/gsm-functionalities/
 - https://moniem-tech.com/2023/03/12/what-is-the-roaming-how-it-works-in-2g-network/

 ![voice calls in GSM](https://raw.githubusercontent.com/sergiocollado/potpourri/master/Notes_on_protocols/Images_mobile_communication/Voice_GSM.webp)

1. MS (Mobile Station) sends dialed number to BSS
2. BS sends the dialed number to MSC.
3. MSC checks with the VLR if MS is allowed to make the call
      - has credit and is a legit mobile user).
      - checks with EIR if it is blacklisted.
5. MSC allocates resources if it can make the call.
6. MSC routs the call into GMSC
7. the GSMC routes the call to the fixed telephoney netowork (PSTN)
8. When the call is answered, the flows goes back.



### GSM Identifier IMEI: International Mobile Equipment Identity

 - Reference: https://en.wikipedia.org/wiki/International_Mobile_Equipment_Identity

 - Is the identifier of the Mobile Station
 - Purpouse of the IMEI is to prevent the theft of mobile stations
 - IMEI is checed in the EIC
 - Burned into the Mobile phone.

### GSM identifiers: IMSI, TMSI, MSISDN

#### International mobile subscriber identiy (IMSI)

 Is the identity of a user, that has bought a SIM and is a subscriber. IMSI is stored in a SIM card. IMSI is unique in all countries. Roaming is only possible because of IMSI. 

 IMSI = MCC + MNC + MSIN (mobile subscriber identification number)

 MSIN is given by the mobile operator that sold the SIM.

####  Temporary Mobile Subscriber Identity (TMSI)

To make hacking of IMSI difficult, IMSI used only as an identifier when the TMSI is not available, e.g, for initial system connection.

- The VLR is responsible for the current location of subscriber and assigns a TMSI.
- Local significance in the area handled by the VLR
- TMSI changes on call basis
- MS stores the TMSI in the SIM card & VLR but not in the HLR.
- TMSI can be assigned in an Operator specific way.

- Reference: https://en.wikipedia.org/wiki/International_mobile_subscriber_identity
  
#### Mobile Subscriber ISDN (MSISDN)

 - Reference: https://en.wikipedia.org/wiki/MSISDN

MSISDN a number uniquely identifying a subscription in a Global System for Mobile communications or a Universal Mobile Telecommunications System mobile network. It is the mapping of the telephone number to the subscriber identity module in a mobile or cellular phone

### LAI (Location Area Identity)

 - Reference: https://en.wikipedia.org/wiki/Location_area_identity
 - Refernece: https://en.wikipedia.org/wiki/Mobility_management

Service areas are subdivided into location areas, 

LAI = MCC (Mobile Country Code) + MNC (Mobile Network Code) + LAC (Locatino Area Code)

In mobile networks, location area identity (LAI) is a unique identifier assigned to each location area of a Public Land Mobile Network

This internationally unique identifier is used for location updating of mobile subscribers. It is composed of a three decimal digit mobile country code (MCC), a two to three digit mobile network code (MNC) that identifies a Subscriber Module Public Land Mobile Network (SM PLMN) in that country, and a location area code (LAC) which is a 16 bit number with two special values, thereby allowing 65534 location areas within one GSM PLMN.

### Base Station Identification Code (BSIC)

 - Reference: https://en.wikipedia.org/wiki/Base_station_identity_code

The base station identity code (BSIC) is a code used in GSM to uniquely identify a base station. The code is needed because it is possible that mobile stations receive the broadcast channel of more than one base station on the same frequency. This is due to frequency re-use in a cellular network. The BSIC is defined in GSM specification 03.03 section 4.3.2.

Each base station has its own BSIC. This code is at all times transmitted on the broadcast channel, so the mobile stations can distinguish between base stations. The BSIC is composed of a 3-bit network color code (NCC) and a 3-bit base station color code (BCC). The NCC is assigned to each network provider so the mobile station can sort out which base stations it is allowed to camp on. The NCC of different providers must be different; they must also be different in national border areas. The broadcast control channel (BCCH) of each base station is assigned a frequency by the network operator, and they must be assigned such that no neighbor stations have equal BCCH and thus equal BSIC.

As long as base stations use different frequencies for their broadcasting channel, there is no problem in using the same base station identity code. Unique identification of a base station is especially important in border areas, where at both sides of the border there is a different operator who might use the same broadcasting channel on the same frequency.

## Working principle of 2.5 GPRS (General Packet Radio Service)

 - Reference: https://en.wikipedia.org/wiki/General_Packet_Radio_Service
 - Reference: https://en.wikipedia.org/wiki/GPRS_core_network#Serving_GPRS_support_node_(SGSN)

GPRS its porpouse is to increase data rate in GSM network. It is basically a packet switch service on GSM which was excusively circuit switched network. 

To achieve higher data rates in GPRS, the coding schemes CS1, CS2, CS3 and CS4 are used. 

To integrate GPRS into GSM, two nodes are added SGSN (Serving GPRS support node) and GGSN (Gateway GRPS support node)

![GSM architecture](https://en.wikipedia.org/wiki/Base_station_subsystem#/media/File:Gsm_structures.svg)
