# Notes on 3G Universal Mobile Telecommunication Service  (UMTS)


The 3rd generation partnership project (3GPP) was formed on 1998, to standarize the 3G. It is a consortium of interancional telecom vendors and operators. 

The International Telecommunication Union (ITU) provides technical requirements. 3GPP develops the techninical specifications. 

3G Universal Mobile Telecommunication Service (UMTS) starts in 2001. Also called Wideband CDMA (Code division Multiple Access). 

## Architectural evolution from 2G to 3G. 

References:
 - https://youtu.be/bq4GuLHShPY
 - https://youtu.be/qNddSi0wugw
 - https://youtu.be/BDHMOVvgPTU

From a network architecture point of view, the network can be divided in 3 elements: first the mobile phones, second, the access network , third, the core network. 
the interesting point is that 3G uses the same core that 2G. 

The 2G access network is the BTS (base station) and BSC (Base station control).

The 3G access network is the RNS (Node B) and RNC (Radio Network Controller). The RNC has many more capabilities than the BSC. The RNS and RNC is knonw as Radio Network Subsystem, based on WCDMA radio technology. The combination of all the radio subsystems is known as UTRAN (Universal Mobile Terrestial Radio Acess Network). 

The core network initially was the same as 2G, but later it evolved, the first version was known as Release 99 (R99), later it evolved further into Release 4, and Release 5. 

![2g_to_3g_architecture](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/UMTS_architecture_2g_to_3g.PNG)


## Architecture 3G

 - Reference: https://youtu.be/JtP8t-nH9Bw

![3g_architecture](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/3G_UMTS_architecture.PNG)

The user equipment, is formed by: 
 - USIM represents the IMSI number
 - the Mobile Equipment is the IMEI number

The UE connects to the radio interface though the Uu interface. 

