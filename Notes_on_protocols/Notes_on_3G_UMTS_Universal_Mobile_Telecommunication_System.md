# Notes on 3G Universal Mobile Telecommunication Service  (UMTS)


The 3rd generation partnership project (3GPP) was formed on 1998, to standarize the 3G. It is a consortium of interancional telecom vendors and operators. 

The International Telecommunication Union (ITU) provides technical requirements. 3GPP develops the techninical specifications. 

3G Universal Mobile Telecommunication Service (UMTS) starts in 2001. Also called Wideband CDMA (Code division Multiple Access). 

## Architectural evolution from 2G to 3G. 

References:
 - https://youtu.be/bq4GuLHShPY
 - https://youtu.be/dnPQySnSWN0
 - https://youtu.be/qNddSi0wugw
 - https://youtu.be/BDHMOVvgPTU
 - https://www.3glteinfo.com/utran-interfaces-and-protocols/

From a network architecture point of view, the network can be divided in 3 elements: first the mobile phones, second, the access network , third, the core network. 
the interesting point is that 3G uses the same core that 2G. 

The 2G access network is the BTS (base station) and BSC (Base station control).

The 3G access network is the RNS (Node B) and RNC (Radio Network Controller). The RNC has many more capabilities than the BSC. The RNS and RNC is knonw as Radio Network Subsystem, based on WCDMA radio technology. The combination of all the radio subsystems is known as UTRAN (Universal Mobile Terrestial Radio Acess Network). 

The core network initially was the same as 2G, but later it evolved, the first version was known as Release 99 (R99), later it evolved further into Release 4, and Release 5. 

![2g_to_3g_architecture](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/UMTS_architecture_2g_to_3g.PNG)


## Architecture 3G

References:
 - https://youtu.be/JtP8t-nH9Bw
 - https://youtu.be/dnPQySnSWN0

![3g_architecture](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/3G_UMTS_architecture.PNG)

The user equipment, is formed by: 
 - USIM represents the IMSI number
 - the Mobile Equipment is the IMEI number

The UE connects to the radio interface though the Uu interface. 

### UTRAN (UMTS terrestial access network)

Node B, connects with the UE over the wireless channel, with the Uu protocol. The Node B will receive the Measurements report from the UE, and pass it into the RNC (Radio Network Controller). 

The RNC: 
 - swicthes traffic and signalling from/to BSC and CN (core network)
 - manages/controls the radio resources of node B in its domain.
 - traffic agregation to/from core network.
 - admission control and code alocation.
 - packet scheduling.

### 3G Core Network

The first versions of the core network: 
 - R'99
 - Release 4
 - Release 5

### Release 99

#### SGSN (Serving GPRS Support Node)

#### GGSN (Gateway GPRS Support Node)

#### IN (Intelligent Network)
 - Handles the charging and balance of pre-paid cards. For post-paid charging, normally there is a charging gateway attached to the GGSN. And the charging-gatway connected to the charging center


### Release 4

The MSC was splitted into: 
 - MSC server: Handles signalling
 - Media Gateway: Handles traffic

### Release 5

With 3G itt is introduced the PS PACKET SWITH CORE. In release 5 it is introduced the IMS (Ip Multimedia Subsystem), with IMS it is possible to handle the voice calls as the PS calls, so voice calls can be done with the IMS in order to handle the voice calls over the IP network as packages. 



## Protocols

 - reference: https://www.3glteinfo.com/utran-interfaces-and-protocols/

| Protocol|	Description|	Standard|
| :------: |  :------: | :------: |
|MM|	Mobility Management|	3GPP TS 24.008|
|CC	|Call Control|	3GPP TS 24.008|
|SMS|	Short Message Service	3GPP TS 23.040,| 3GPP TS 24.011|
|SS|	Supplementary Service	|3GPP TS 24.080|
|GMM	|GPRS Mobility Management|	3GPP TS 24.008|
|SM	|Session Management	|3GPP TS 24.008|
|GSMS	|GPRS Short Message Service	|3GPP TS 23.040, 24.011|
|AMR|	Adaptive Multi Rate|	3GPP TS 26.071|
|IP|	Internet Protocol	|IETF RFC 791|
|PPP|	Point-to-Point Protocol	|IETF RFC 1661|
|RRC	|Radio Resource Protocol	|3GPP TS 25.331|
|PDCP	|Packet Data Convergence Protocol|	3GPP TS 25.323|
|RLC|	Radio Link Control	|3GPP TS 25.322|
|MAC|	Medium Access Control	|3GPP TS 25.321|


