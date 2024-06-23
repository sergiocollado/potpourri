# Notes on 2G: Global System for Mobiles (GSM)

The European Telecommunication Standards institue (ETSI) was formed in 1988, their goal was define the standard for the firs Global System for Mobiles (GSM) in 1991. It is still used in may countries. 

In USA the digital AMPS was used. Nowadays it is obsolete. 

This 2G is a digital system, this means that the voice is digitalized and encrypted. It supports roameing. And it supports SMS (Short Message Service) and roaming. 

## 2G Architecture

![GSM architecture](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/Gsm_network_architecture.png)

![voice calls in GSM](https://raw.githubusercontent.com/sergiocollado/potpourri/master/Notes_on_protocols/Images_mobile_communication/Voice_GSM.webp)

 - reference: https://yatebts.com/documentation/concepts/gsm-functionalities/


- **Mobile station (MS)**: the first component, MS, the mobile station consists in the Mobile Equiptment (ME) and the SIM card. The SIM has the identity of the subscriber, and that identity is called IMSI (Interantional Mobile Subscriber Identity)
- **Base Station Subsisteym (BSS)**, the RAN (Radio Acess Network) in GSM is called BSS (Base Station Subsystem). A BSS, consists on a BSC, and a BSC can control more that one BTS. The interface between the BTS and BSC, is called "Abis" interface. And the interface between the BSC and the core network is called the "A" interface.
- **NSS**: The core network (CN) in the case of GSM, is called the Network Subsystem (NSS), and NSS, consists in MSC and its asociated databases: EIR, VLR, HLR, AUC.
- **GMSC**: One mobile network is connected to another network through the Gateway MSC (GMSC), for example with the fixed telephony network: PSTN (Public Switching Network), or with other mobile network which is run by other operator. 

### Base Station Subsystem (BSS)

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


 - Channel asignation on A interface.
 - Gateway MSC (GMSC) handles interface with other PLMNs/GMSC


