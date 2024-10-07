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
  - CN (Core Network): EPC (Evolved Packed Core)
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



