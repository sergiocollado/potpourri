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

A RAN (Radio Access Network) may contain one or more BSSs

