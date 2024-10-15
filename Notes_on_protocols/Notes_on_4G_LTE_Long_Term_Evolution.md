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


![4g architecture](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/4G_LTE_arch.PNG)


  - The UE (User Equipment) consists of the ME (Movile Equipment) + USIM 
  - The access network:  EUTRAN - Evolved Universal Terrestial Radio Access Network)
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



