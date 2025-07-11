# Notes on 4G LTE long term evolution

References: 
 - https://yatebts.com/documentation/concepts/lte-concepts/
 - Introduction to 4G LTE: Technology, Architecture and Protocols Course: https://youtu.be/MT7KT4TjNx8
 - 4G LTE Network Architecture Simplified: https://youtu.be/dBwSoJH6Njk
 - An Explanation of the Driving Factors for LTE & LTE Network Architecture With Mpirical: https://youtu.be/aGRTBA1tYRo
 - Basic LTE Architecture Video | E-UTRAN, eNodeB, EPC, SGW, PGW, MME, HSS, PDN by TELCOMA Global: https://youtu.be/ZlQkHQbHQ_E
 - 3.1 - LTE 4G ARCHITECTURE BASICS - INTRODUCTION: https://youtu.be/1j4UwsdD9Qs
 - 3.3 - LTE 4G Evolved Packet Core (EPC) - Real Life Analogy - Air Travel: https://youtu.be/GFoGiatdkRY
 - Learn 4G LTE Network Architecture: https://youtu.be/-nDjkV-NulM
 - LTE Attach Procedure - Introduction: https://youtu.be/m9nmSgYnGfE
 - LTE yt channel: https://www.youtube.com/channel/UCf5srFJ-JofnE8r-bn1o1VA
 - https://hackmd.io/@jonathanrichard/S1geBs-g_
 - https://www.tutorialspoint.com/lte/lte_basic_parameters.htm


![4g architecture](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/4G_LTE_arch.PNG)


  - The UE (User Equipment) consists of the ME (Movile Equipment) + USIM 
  - The access network: in 4G,  EUTRAN - Evolved Universal Terrestial Radio Access Network)
  - CN (Core Network): in 4G, the core network is known as EPC (Evolved Packed Core)
  - UEs don't communicate directly with the CN, but CN is responsible for overall control of UE and call stablishment. 
 
The Access Network consists on a base stations, the bases station in 4G is known as eNodeB (eNBs) 

The core network consists in nodes as: MME, HSS, PCRF,  and routers (or gateways) as: S-GW (serving gateway), P-GW (packet(data) gateway). 

4G can interwork with 3G



![4G LTE arch and protocols](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/LTE_arch_and_protocols.PNG)



### Overall 4G architecture

In the 3G architecture the RNC (radio network controller) is connected to one or more NodeBs, but in 4G there is not RNC, some  functions of the RNC, are moved
to the eNodeB (enhaced NodeB), and other functions are moved to the core network. So the architecture is flatter, and that implies less latency. 

4G is an all IP architecture, in contrast with 3G. In 3G there was a circuit-switch core and a packet-switch core, but in the case of 4G there is no circuit-switch core, 
only packet-switch core. So the voice is also carried with IP packets. 


### Evolved Node B (eNB)

 - Radio transmission/reception
 - Radio resource management (RRM)
    -  admission control
    -  resource block allocation in UL & DL
 - Encryption of user data & signalling
 - Co-ordination for handover with other eNB


### EPS bearer

EPS bearer is like an IP tunnel that extends from the UE, to the eNodeB , to the SGW up to the PDN gateway. 

 - refernece: https://telecompedia.net/eps-bearer/#:~:text=EPS%20bearer%20or%20with%20long,known%20as%20default%20EPS%20bearer.

 - 4G is an all IP system
 - 4G provides data/IP connectivity to UE as EPS Beares
 - EPS bearer QoS characterized by:
     - datarate: guaranteed or non-guaranteed
     - latency
     - priority


### Mobility Management Entity (MME)

Is similar to the VLR (visitor location register) in 2G/3G. in 4G the temporary data of an user UE is stored on the MME. So 
the signaling load on the HSS is reduced. 

MME manages the UE registration, it verify that the UE is valid, it authenticates the UE with its security keys, that
are retrieved from the HSS. Using that security keys the MME validates the UE. Once the UE is validated, it is assigned
a temporary identifier that is used between the UE and the MME. 

The MME stores the temporary data, also known as the context of the UE. Part of that that is downloaded from the HSS. 
When the UE moves to other area, its data will be transferred to other MME, and deleted from the previous MME. 

MME is also responsible of the stablishment and management of the EPS bearer. When a UE registers itself in a 4G network
is assigned a default EPS bearer. If that UE wants to make a video call an additional EPS bearer will be assigned to it. 

As part of the stablishment of the EPS bearer the MME uses the P-GW and the S-GW through which that EPS bearer is passing. 


### Serving gateway (S-GW)

It handles the user data connectivity b/w UE and the EPC. 

The S-GW is simply a router, it routes the data received from the UE to the PDN-gateway (P-GW) (PDN: packet data network)

Other important function of the S-GW, is inserting QOS (Quality of Service) markers (DiffServ Code Points) into the IP header. 
Because differente EPS bearers have different QOS requierents. 

"Anchor mobility" is other important function for the S-GW. In case the UE changes the eNodeB where it is transmitting, the 
eNodeB will change and a handover with the previous eNodeB, but it will be still linked to the original S-GW. So the point
of contact with the core network remains the same. The same will happen in a handover from a 2G/3G network. 

Other function is the "IDLE mode downlink package buffering", the SGW will buffer incomming data for the UE. The SGW
will inform the MME about this incomming data, and the MME will inform the UE about this incomming data. 

Other function is the "lawful interception", lawful monitoring of UE. As all the data passes through the SGW is a good place
to monitor data. 

### Packet data gateway (P-GW)

Allocates IP addresses to UE during bearer establishment.

### HSS Home Subscriver Service
 Like the HLR in 2G/3G

### Equipement Identity Register - EIR
 Terminal database of terminals stolen- interface S13 with MME

### Policy and Charging Rules Function - PCRF

the Policy and Charging Rules Function (PCRF) is a critical component of the Evolved Packet Core (EPC) that handles policy enforcement and charging. It dynamically allocates network resources and enforces policies based on user needs, ensuring optimal network performance and user experience. The PCRF manages Quality of Service (QoS) parameters, access control, and charging rules, supporting various network services and subscriber plans. 

### Policy and Charging Enforcement Function - PCEF

The PCEF is a DPI (Deep Packet Inspection) device responsible for the enforcement of rules which have been configured statically or supplied to the PCEF dynamically from the PCRF (Policy and Charging Rules Function). The PCEF sits on the user plane, ensure that subscriber traffic flows are treated in accordance with network policy e.g. implementing QoS, throttling traffic, blocking traffic, etc. Crucially, the PCEF will ensure that services are billed accordingly.

Tipically integrated in the PGW.

ref: https://youtu.be/Wcoj4aw_X78

## 4G charging

 - reference: https://www.etsi.org/deliver/etsi_ts/132200_132299/132240/14.03.00_60/ts_132240v140300p.pdf


### Interfaces

![4g arch protocosl](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/4g_arch_interfaces.PNG)

- Sgi interface between PWG and the external IP network (internet)
- S5 intereface between the SGW and the PGW (same network), transporting user data + a few signaling messages
- S11 interface between the SGW and the MME, tranporting signalling messages
- S6a interface between the MME and the HSS, transporting signalling messages
- S1-MME interface between the eNodeB and the MME, transporting signalling messages
- S1-U interface between the eNodeB and the SGW, transporting user data, no signalling exchanges.
- X2 interface between 2 eNodeBs, transporting user data and signaling messages
- Uu transmission in the radio channel between the UE and the eNodeB, transporting using data and signalling messages
- S8 interface, between the SGW and the PGW of diffeRent networks (roaming)
- Gx between the PGW and PCRF
- S13 interface between the EIR and the MME


![4g radio interface diagram](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/4G_radio_interface_diagram.PNG)
