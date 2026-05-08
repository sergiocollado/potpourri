 - 5g systems approach: https://5g.systemsapproach.org/
 - How to build a opensource based 5G network: https://ubuntu.com/blog/introduction-to-open-source-private-lte-and-5g-networks
 - https://www.free5gtraining.com/
 - https://training.linuxfoundation.org/training/introduction-to-free5gc-lfs114/
 - https://github.com/emanuelfreitas/3gpp-documentation
 - https://github.com/open5gs/open5gs
 - https://github.com/Citrayaf/How-to-build-OpenCore-and-OpenRAN-for-5G
 - https://open5gs.org/open5gs/docs/guide/02-building-open5gs-from-sources/
 - Vodafone unveils prototype 5G network built on a Raspberry Pi computer: https://youtu.be/PAu_45Yn4cA?si=bQRXmO076lVRLYMo
 - A private 5G campus network enabled and powered by OpenStack and StarlingX: https://youtu.be/xnnw_9UIoS0
 - 5g data session: end to end - deep dive: https://medium.com/@anand.hv123/5g-data-session-an-end-to-end-call-flow-deep-dive-ac896df596e6
 - 5G Session Management Signalling Decoded: In-Depth Analysis: https://youtu.be/WR_fpFVuilg?si=Dys6v-oZGcNfwQre

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

![evolution mobile communications](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/evolution_mobile_communications.PNG)

### 1G
It started with AMPS (Advanced Mobile Phone System)  this was the first generation of mobile cellular phone systems. This used an Analog technology based in FDMA (Frequency Division Multiple Access), it was developed by Bell Labs (1983): 

### 2G
The second generation was GSM (Global system for Mobile Communications) and it was based in digital electronics. (1991). It allows for TDMA (Time Division Multiple Access) and FDMA at the same time. And like it is based in digital systems, is more robust against interferences. GSM had voice communications, but also data transfer up to 9.6 kbps, and SMS (Short Message Service), and used SIM (Subscriber Identity Module) cards, that contain the user subscription information and phone books. 

The next evolution is the IS-95 (Interim Standard -1995) which is the first 2G with CDMA (Code Division Multiple Access) that improves the performance against interference of other devices and signal fading (multipath). It supports voice and data up to 14.4 kbps

### 3G
Next follows UMTS (Universal Mobile Telecommunication System), this is the 3G. It is supported by UTRA (UMTS Terrestrial Radio Access) that supports several terrestrial interfaces. Multi-user access in UTRA can be done by UTRA-FDD (Frequency Division Duplex)  or UTRA-TDD (Time Division Duplex); follows WCDMA (Wideband Code Division Multiple Access) based in UTRA-FDD. The data rate in 3Gpp ( 3rd Generation Partnership Project) reaches up to 2 Mbps (release 99): 

UMTS evolves for faster packet speeds in the HSDPA (High Speed Downlink Packet Access). Downlink means from the base station to the mobile device. The data rates reach 14 Mbps. Next came the HSDPA+ (Evolved High Speed Downlink Packet Access) is the first time MIMO (usage of multiple antennas) and a 64 QAM, is used. 

### 4G
The next technology leap is LTE (Long Term Evolution). Its peak data rate is (release 8) downlink 300 Mbps  and uplink 65 Mbps. From its evolution LTE-A (LTE Advanced) is considered already as 4G. With data rates as downlink 3 Gbps  and uplink 1.5 Gbps

https://en.wikipedia.org/wiki/Comparison_of_mobile_phone_standards

https://www.3gpp.org/

## Basic components of a mobile telephony network:

#### 1 - Mobile station/User equipment
 This is the mobile phone and it SIM (Subscriber Identification Module) cardio, the SIM has an IMSI (International Mobile Subscriber Identity) 

#### 2 - Radio Access Netowork (RAN) / Acess network
 The base station connects to the ME

#### 3 - Core network
 The core network is responsible for the overall control of the mobile station, establishment and routing of the call. The call can be routed
 in the same mobile network or be routed to an external network .

#### 4 - Backhaul network
 Connects the Radio Acess Network (RAN) with the Core Network (CN). It can be a microwave link or an electrical or optical fiber cable (most common). 
 

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
 - https://5g.systemsapproach.org/index.html
 - https://yatebts.com/documentation/concepts/5g-core-network/
 - https://youtu.be/4NbDhxPw4i4
 - https://www.itu.int/en/mediacentre/backgrounders/Pages/5G-fifth-generation-of-mobile-technologies.aspx
 - https://www.etsi.org/technologies/5G
 - System architecture for the 5G System:  https://portal.3gpp.org/desktopmodules/Specifications/SpecificationDetails.aspx?specificationId=3144
 - https://www.techtarget.com/searchnetworking/feature/An-overview-of-3GPP-5G-releases-and-what-each-one-means#:~:text=3GPP%20meets%20four%20times%20a,user%20needs%20evolve%20over%20time.
 - https://en.wikipedia.org/wiki/5G
 - https://mobilepacketcore.com/5g-introduction/
 - https://www.sharetechnote.com/html/5G/Handbook_5G_Index.html
 - simple 5g architecture video: https://www.youtube.com/watch?v=Q6YxHz_07zk


5G is the 5th generation of mobile networks. It offers highier data rates, and
lower latencies that previous generation. Also new user cases, that didn't exist 
in previous generations.

IMT-2020 standard defines the requirements for 5G


## SDN (Software defined networking)

Data plane is where the data is actually flowing through, and where all  the switching happens. 

Control plane, is the central controller which makes the decisions about how to route traffic. Control plane can be centralized or distributed. 

The reason for separating control plane and data plane, is because it causes massive improvement in the throughput. 


## 5G main new uses

There are new use case not presetn in previous mobile generations:

- eMMB: Enhaced Mobile Broad-Band: Provides connections up to 10 Gbps, instead 1 Gbps as in 4G.
- mMTC: Massive Machine Type Communications: used to connect massive number of device, for example for IoT. Provides connection for 1000000 devices per km^2, compared to 100000 in 4G. 
- URLLC: Ultra-Reliable and Low Latency Communications: Latency coud be 1 ms, instead of 10 ms in 4G. This could be usefull for self-driving cars, drone controls ... 

## 5G timeline

5g related 3gpp releases:
- Rel-19
- Rel-18
- Rel-17
- Rel-16
- Rel-15

## 5g basic principles of the architecture  

 A diagram of the simplified 5g architecure is: 

 ![5g_simplified_architecure](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_simplified_architecture.png)

 The 5G core network is build on the IP network, so the data units are: (IP packets, ethernet frames and other) and are transported in IP packages

 The basic dataflow management is reused from 4G:
  - Tunneling: encapsulation of data unit in IP package
  - Use of GTP-U protocol (GPRS Tunneling Protocol in the User Plane)

![5g_arch](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g.PNG)

The base stations (gNB) foward the UE packages to the UPF (User Plane Function), there can be more than one UPF, the UPF can be considered the 5G equivalent to the 4G SGW (Serving Gateway) and PGW (packet gateway).

Some functions of the UPF (user plane function):
- The UPF must connect to the data network, even if the UE moves, that is known as 'Movility anchoring' 
- The UPF is also involve in packet fordwarding for data PDUs when tunneling is enforced, that is: it adds or removes tunnel-related headers

It has other more particular functions like: 
- It can also analyze or detect packages according to some defined flow templates
- Also applys policies of QoS (quality of services), prioritizing some packages over others.

The 4G MME, is replaced in 5G by AMF (Access and Mobility Management Function) and SMF (Session Management Function): 
![5g_arch](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_2.PNG)

The AMF enables NAS dialogs between the UE and the AMF, (passing thought the gNB, but the messages are not process there)

The AMF can exchange sigalling wwith the UE, and manages: 
   - registration
   - mobility
   - connection
   - reachability
 - Ciphering and integrity protectionof NAS signalling message.
 - access authentification and access authoritzation.
 - provide transport for other services as location services.
 - UE mobility event notification.

The SMF (Session Management Function) controls the UPF, and handles the PDU session controls. 
 - It can exchange messages with the UE when the PDU session is required (the messages go through the AMF and gNB)
 - manages the PDU sessions, by seting it up, modification and its release.
 - manages addresses, allocates IP addresses for the UEs.


![5g_arch](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5_sbi_service_based_interface.PNG)

Other change between 4G and 5G is that the HSS is replaced by the AUSF and the UDM in 5G.

![5g_arch_3](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_3.PNG)

AUSF (Authetication Server Function) is the authentication server function.

UDM (Unified Data management function) manages users and subscriptions identifications. like the front-end of all the data related to a UE subscription. and user's informaciton (SUPI handling) 
It also stores the information of the AMF that manages each UE, as well as the SMF when there are multiple PDUs sessions for a UE. It will also record the SMS gateway manageing a given UE. 

## Is 5G really so simple?

No, it is not, for example a SMS service: 


The SMS is send from the UE to the AMF, and from there to the SMSF (Short Message Service Function), that SMSF is like a gateway between the SMS server and the 5G network, the SMSF can also check the user profile and communicate the UDM if the subscriber has that SMS service "in the control plane".

![arch_5g_SMSF](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_SMSF.png)


## PFCP protocol: How does a SMF control a UPF? 

The SMS controls the UPF with a specific protocol PFCP (Packet Forwarding Control Protocol). SMF or UPF can start dynamically in the network, so each one needs to know the characteristics of each other, so this is the assciatioon procedure between SMF and UPF. The goal of the protocol is the stablishment or modifications of PDU sessions. ​To do this, a set of messages will be defined to ​set or modify the rules for a PDU session. Also there may be counters in ​the UPF on how many packets meet a certain criterion. ​When there is an event in ​the user plane related to ​a counter threshold being exceeded, ​for example, the UPF can send a report to the SMF. 

reference: 3GPP TS 29.244 : Interface between the Control Plane and the User Plane nodes

PFCP runs on top of UDP. ​UDP does not ensure reliability. To allow reliable control, ​PFCP includes an acknowledgment and ​retransmission of messages by ​PFCP when messages are lost. ​

Let's look at the association procedure. ​It is usually triggered by ​the SMF that wants to take control of the UPF. ​The SMF sends a message association setup request. 

![arch_5g_SMF_UPF_association_setup_request](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/5g_SMF_UPF_association_setup_request.png)

The SMF sends a message association setup request. 
​It sets a unique identity and sends ​the list of the characteristics of ​the processing it is doing in the control plane. ​In response, the UPF indicates its unique identity and ​also the list of characteristics of how ​it processes data in the user plane. ​An example of characteristics ​is the allocation of the TEID, ​which can be done either by the SMF or by the UPF. ​Do not forget that an SMF can control multiple UPF. ​There are therefore multiple possible associations. ​There are, of course, ​similar procedures for updating ​associations or ending associations, ​if, for example, a UPF stops. ​The association procedure isn't done very often. 

​The main purpose is to ​establish PDU sessions, that means tunnels. ​It's important to remember that there can be ​hundreds or thousands or ​millions of tunnels managed by a UPF. ​Each tunnel, and therefore, ​each PDU session must be uniquely identified. ​In the user plane, ​we have the TEID, ​which uniquely identifies a tunnel locally. ​But we do not use this identity to guarantee ​complete decorrelation between the user plane ​and the control plane. ​Each PDU session is therefore identified by ​an identifier called the Session Endpoint Identifier. ​This identifier is, in fact, ​local to each piece of equipment. 
​We find an identifier on ​the UPF side and an identifier on the SMF side. ​The SEID is coded on 64 bits, ​which makes it possible to manage ​a considerable number of PDU sessions. 


​Let's look at the establishment of a PDU session, ​in the case where it is the UPF that chooses the TEID.

![arch_5g_UPF_selects_TEID](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5_UPF_selects_TEID.png)

​The SMF selects one of the UPF ​with which it is associated and chooses the rules. ​The rules are packet detection, PDR, ​or forwarding action, FAR, ​or quality of service, and so on. ​The SMF chooses an SEID value, ​not yet allocated locally, ​in its reference system. ​It sends a message session establishment request ​with the SEID it has ​chosen and the description of the rules. 

​In turn, in order to have a unique identification, ​the UPF chooses an SEID value, ​chooses TEID (since we have ​assumed that it is the UPF that chooses the TEID) ​and applies the rules that have been provided. ​It responds to the session establishment request, ​specifying the SEID chosen by ​the SMF so that ​the response corresponds uniquely to the request, ​it indicates the SEID that the UPF has chosen. ​We have similar procedures for ​modifying or deleting a session. ​To conclude, PFCP ​stands for Packet Forwarding Control Protocol. ​It is a protocol between the SMF and UPF. ​It works above UDP but incorporates ​a mechanism from making the link ​reliable by retransmitting lost messages. ​An SMF can be associated with ​different UPFs by means of the association procedure, ​and can establish, modify, ​or release PDU sessions, ​specifying the set of rules ​to be applied to each session. 

## Session stablisment with CUPS: How a PDU session is setup in 5G? 

​Let's consider the initial state. ​Let's start with the terminal, the UE (User Equipment), which is in the network. ​Let's suppose that it's already known by the network. ​We also have the gNB which makes up the radio access network, or RAN (Radio Access Networkd). ​We have the UPF, user plane function, and ​finally the AMF, Access and Mobility Function, ​and the SMF, Session Management Function. 

![PDU_session_stablisment](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_PDU_session_stablisment_TEID.png)

​For simplicity's sake, ​we assume that the two functions are merged, and ​that we are not interested in the exchanges between the AMF and the SMF. ​That's the initial state. ​So, where do we want to go? ​Well, we want a tunnel between the RAN and the UPF. ​When we have a tunnel, we need a TEID at each end. ​So, we call that TEID_RAN ​the radio access network end, ​and TEID_U at the UPF end. ​We need to be aware that the objective for ​it to work is that, each end knows not ​only the TEID it has chosen of course, ​but also the TEID of the other end. 


![PDU_session_stablisment_messages](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_pdu_session_stablishment.png)

​We assume in this case that it is the SMF that ​chooses the TEID and not the UPF, ​as both are possible in 5G. ​The UE sends a PDU session establishments request message. ​There are a number of security functions ​to verify the authorization of the terminal, ​and also to verify that it is who it says it is. ​That is to say, that it is authenticated. ​Finally, there is SMF selection. ​The SMF which is selected, will then ​select the UPF that it is associated ​with from the set of possible UPFs. ​It chooses an SEID_S, ​namely the SEID on the SMF end. 

​And it also chooses the TEID to be used by the UPF. ​That is the assumption we are working under. ​The SMF sends a session establishment ​request indicating the chosen SEID, ​the set of packet detection rules and ​forwarding rules, and ​the TEID that the UPF will use. ​In order to identify the session, ​the UPF chooses an SEID called SEID_U. ​It also applies the relevant policies and rules and ​response with a Session Establishment Response, ​in which it indicates the SEID at the SMF end ​to reference to the request... ​and it also indicates the selected SEID_U. ​The SMF sends ​Session Resource Setup ​request to the gNB via the AMF. ​This message contains the TEID ​chosen by the SMF at the UPF end. 

​The radio connection is then modified to enable ​data flow transmission on the radio link. ​And as soon as this happens, ​we can see that the uplink data ​can circulate through the 5G ​network as the gNB knows the TEID used by the UPF. ​Now, the gNB needs to choose a TEID_RAN and ​transmit it to the UPF. ​In response to the previous message, ​the gNB therefore sends a message containing the TEID that it had chosen. ​This TEID will get to the UPF via ​Session Modification Request. ​When the UPF has all this information, it can establish ​the full set of packet detection rules and forwarding rules. ​Once the SMF and the UPF each knows ​the SEID chosen by the other part, ​the messages refer to a particular PDU session.

​Each time, they indicate the SEID on the SMF end for ​the message sent by the UPF, ​or the SEID on the UPF end for ​the messages sent by the SMF. ​The data flow can now circulate in both directions. ​It should be noted that the gNB has both functions in the control plane and ​in the user plane, since it forwards all the user data from the data flow. ​In conclusion, we have seen how to establish a PDU session. ​It is mainly controlled by the SMF. ​It involves the gNB, which retains its function in ​the control plane and in the user plane. ​The gNB-UPF tunnel is set up in two stages. 
​First, establishing the tunnel at the SMF's request, ​indicating the TEID on the UPF end. ​And then, modification by the SMF to ​tell the UPF which TEID is selected by ​the gNB on the radio access side. ​[MUSIC] 

More on:  5g data session: end to end - deep dive: https://medium.com/@anand.hv123/5g-data-session-an-end-to-end-call-flow-deep-dive-ac896df596e6

## Initialization of a terminal in 5G

How does a terminal attach itself to the 5G network? Or, in other words, what happens when a movile phone is tuned on in the 5G network? ​The procedure that enables this to happen is called **Network Registration**. ​Here, we can see the network with the gNB, the UPF, the AMF, the SMF, the AUSF for security functions, and the UDM. The UDM contains the subscriber profile. And of course, we have the UE. 

![network registration](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_network_registration.png)

​To begin with, the UE is in RM-Deregistered state. It is unknown to the AMF. RM stands for **Registration Management**. ​The UE sends a registration request message containing its identity. Of course, this message is sent over the radio link, and arrives at the gNB or the radio access network. ​The gNB selects the AMF. Indeed, it can be connected to multiple AMFs. 

![network registration messages](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/5g_arch_network_registration_messages.png)

​And it sends the request, in accordance with the Non-Access Stratum principle, NAS. It sends this request to the AMF. ​The AKA procedure provides security. AKA stands for Authentication and Key Agreement. This procedure involves the UE, the AMF, the AUSF and the UDM. ​Once the UE has been authenticated, the AMF needs to check with the UDM that the subscriber can register. This is the Registration message; ​the UDM responds with Yes or No. For the sake of this demonstration, we will suppose it says Yes. 

​Between the AMF and the UDM there is an interface, which a Service-Based Interface, or SBI. ​This means that all of the exchanges are broken down into simple request-responses, with a near-immediate response from the server that receives the request. ​Here, and we will see this again later, we have a second request so that the AMF can retrieve the subscriber profile from the UDM. ​This profile concerns network access rights and, when necessary, mobility rights. ​Then, the AMF can request notification of any profile modifications concerning this subscriber. This is a service that the AMF can sign up to. ​The UDM will respond Yes or No. Let us suppose that there is a positive response. 

​Once the AMF has retrieved the profile and, of course, the UE can be taken on, it will choose a temporary identity. ​This is known as a **Globally Unique Temporary Identity**, or GUTI. This is the same as in 4G, but we add the prefix 5G in order to differentiate between 4G GUTI and 5G-GUTI. ​This GUTI is sent to the terminal in a Registration Accept message. The terminal will store the GUTI and, once it is sure it will be taken on by the network, it will complete the registration procedure by sending a Registration Complete message. ​So, what’s the situation at the end of this procedure? ​The UE switches to RM-Registered state and has a 5G-GUTI. 

![network registration final state](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_network_registration_final_state.png)

![network registration PDU session set up](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_network_registration_PDU_session_set_up.png)

​And, in the AMF, a context is open for this UE, where the AMF will memorize/record the state of the terminal, along with some other information such as the GUTI. ​It should be noted that, up to this point, the SMF has not been involved in the procedures at all. In addition, data cannot be exchanged between the UE and the data network. ​To do this, we need the PDU session establishment procedure, which we have already seen. Let’s take another look at this procedure to examine some specific points in more detail. ​The UE sends a session establishment request, specifying the 5G-GUTI. The AMF will select the SMF and transfer a message requesting the creation of a session to the SMF. 

​The SMF will first check that the subscriber profile is compatible with the establishment of this session. ​This is a very similar procedure to that which we saw earlier. ​But here, we retrieve the subscriber profile for everything that relates to session establishment: what type of session it can establish, and the corresponding characteristics. ​As in the previous case, it is possible to subscribe to a profile modification notification service. ​The SMF informs the AMF that everything is in order, and then selects a UPF to establish the PDU session. It then chooses an IP address to allocate to the terminal. ​We will not go over the session setup again, the exchanges between SMF and UPF, but remember that either the UPF or the SMF will choose a TEID at the UPF end. 

​First and foremost, this TEID must be transmitted to the gNB. This is done by a message sent from the SMF to the AMF, then from the AMF to the gNB. ​The UE also needs to be informed of the IP address that it has been allocated. But this IP address concerns neither the AMF nor the gNB; they don’t need to know it. ​A message is defined according to the Non-access stratum principle, extended to the UE-SMF exchange. This message is called a Session Establishment Accept. ​The important thing to remember is that it is sent by the AMF, then by the gNB with absolutely no interpretation. 

​It is transported completely transparently. The UE will of course store the IP address. And we have already seen what happens next, so we won’t go over it again here. ​What is the final state once the session is established? ​The terminal, the UE, is in an RM-Registered and CM-connected state, indicating that there is a radio connection that can send the data and a data tunnel between the gNB and the UPF. ​It should be noted that the UE also stores the IP address of the terminal ​and that there is a context in the AMF which contains the terminal’s state, as well as a context in the SMF which is linked to the PDU session. ​In conclusion, in 5G, we have a registration procedure in the network which is completely distinct from the PDU session establishment procedure, unlike in 4G, where the two procedures are merged. 

​In 5G, the IP address is allocated by the SMF. ​There is the same general overall philosophy as in 4G, as tunnels are also established, but we can see that there are more messages exchanged in the procedures due to the separation between the SMF and the AMF. ​Finally, the UPF is controlled by the SMF according to the CUPS principle. 


## Security in 5G: Security network functions

### ARPF 
"Authentication credential Repository and ​Processing Function" or ARPF: it stores the subscribers' permanent keys, ​which never leave the ARPF, ​and it creates authentication vectors, ​including a result used to verify authentication, ​master keys for integrity and encryption. ​In concrete terms, ​as we have said, ​the ARPF is located in the UDM. ​

### SUCI
There is another function located in ​the UDM that has to do with identity concealment. ​The permanent identity in 5G is called ​the **"SUbscription Permanent Identifier"** or **SUPI**. This identity is not transmitted over the radio channel. ​Instead, a new identity is defined. ​It is called **"SUbscription Concealed Identifier"** or **SUCI**. ​The SUCI is an encrypted version of ​the SUPI and is ​protected against modification by an attacker. 

### SIDF
​Then a function called the **SIDF**, ​or **"Subscription Identifier De-concealing ​Function"** takes the SUCI that has ​been created by the UE and gets its SUPI. ​The SIDF is located in the UDM, ​but it could also be ​a function completely external to the UDM. ​

### AUSF
The AUSF is the authentication server. It calculates authentication vectors ​for each network that requests them. ​It transmits one vector each time and no more. ​The AUSF verifies the authentication of the subscriber, ​and this is important, ​is always located in the subscriber's **home network**.

### SEAF 
​In the **visited network**, ​the element that allows ​the authentication to be pre-checked, ​and that takes on the role of an authenticator, ​is called the **SEAF**, **"SEcurity Anchor Function"**. ​It pre-verifies the authentication, as we said, ​and it also calculates the child key ​from the parent key sent by the AUSF. ​For integrity and for encryption, again, ​it doesn't reserve any authentication vectors. ​The SEAF is located in the AMF. 

​From a practical point of view, ​the SEAF is within the AMF, ​but the AMF also plays a role as an AMF for security. ​It's the AMF that encrypts and ​controls the integrity of ​the Non Access Stratum messages ​(the NAS messages), which are ​exchanged between the UE and the AMF, ​and that physically pass through the gNB. ​The gNB also manages encryption for ​all data and messages transmitted on the radio channel. ​The role of the gNB and the AMF is ​to calculate the encryption and integrity keys, ​which are always deduced from the parent keys. ​Also, for each transmitted block, ​the gNB and the AMF manage integrity. ​When transmitting, they calculate ​the message integrity or message authentication code. ​They verify it when receiving a message. They also carried out encryption and decryption. ​

In conclusion, the network functions ​that ensure security are ​the UDM because it integrates the function of ARPF, ​(long-term key storage) ​and SIDF to reveal ​the permanent identity from the concealed one. ​On the other end, ​we can't forget the authentication server, ​which is always in the home network. ​There's also the AMF in its role as SEAF because it acts ​as a security anchor and ​manages the security of the NAS messages. ​Last but not least, ​we mustn't forget the gNB for ​everything that is related to radio transmission. 

![security functiosn 5g](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_SIDF.png)

## How to identify an UE without transmitting its permanent indentity in clear text over radio?


Acronims: 
- MCC: Mobile Country Code
- MNC: Mobile Network Code
- MSIN: Mobile ​Subscriber Identification Number
- IMSI: International Mobile ​Subscriber Identifier. IMSI = MCC + MNIC + MSIN
- SUPI: SUbscription Permanent ​Identifier
- SUCI: Subscription Concealed Identifier

The **SUPI** or "SUbscription Permanent ​Identifier" is the globally unique permanent ​identifier of UE in a 5G network. ​Quite often, the SUPI is an IMSI or "International Mobile ​Subscriber Identifier" which was defined in previous generations. ​Keeping the IMSI simply allows interworking for ​example with 4G networks but also 3G and 2G networks. ​The IMSI is formed by a network ​identity which is itself made ​up of a "Mobile Country Code" (MCC) and ​a "Mobile Network Code" (or MNC). 

​Each operator assigns to each subscriber ​a serial number known as the "Mobile ​Subscriber Identification Number" or ​MSIN, which is unique in its network. ​When a user travels abroad, I mean, ​in the case of international roaming, at the network request ​the UE indicates its permanent identifier, the IMSI. ​Why is this? ​Because it is generally not possible to route the attachment ​request correctly using the temporary identity also known as the GUTI. ​What is done with IMSI? ​In the visited network, ​there is an analysis of the Mobile Country Code and ​the Mobile Network Code in order to route to the right home network. ​But in the home network, ​there may be several HSS databases. 

IMSI = MNC + MCC + MSIN


![IMSI](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_IMSI.PNG)


​HSS means "Home Subscriber Server" in the case of 4G. ​And we can have several UDM instances in the case of 5G. ​Each HSS or UDM instance, ​manages a range of MSIN numbers. ​Therefore, in the home network, the first digits of MSIN or ​in other words the most significant bits ​must be analyzed to route to the right HSS, ​namely the one that manages the subscriber. ​Our objective is to disguise the SUPI by creating a SUCI or ​Subscription Concealed Identifier, ​but we must be able to continue routing ​in the case of international roaming. ​For this to be possible, the MNC and ​MCC remain in clear text and ​only the MSIN will be encrypted. ​Since 2G, security procedures have been based on asymmetric key. 

![Encripted_IMSI](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/encripted_IMSI.png)

​This means that the same subscriber ​specific key K is stored in the SIM card and ​in the security database. ​In 5G, it's the ARPF. ​Each subscriber has their own key. ​When there is an attachment request, ​the AMF, for example, makes a request for ​a security vector for the IMSI. ​From the knowledge of the MSIN contained ​in the IMSI, we can determine the key K and ​generate the encryption key that is ​therefore specific to the requesting UE. ​If we encrypt the IMSI from ​the key K we would have a version ​of the encrypted MSIN. ​To decrypt, we need access to the key ​K which requires the MSIN in clear text. 

​So, there is a chicken and egg problem to solve. ​The goal is to have a key that is ​shared between the UE and the SIDF ​and to keep it secret with messages exchange in clear text. ​This is possible, thanks to Diffie-Helmann key ​exchange which is based on asymmetric cryptography. ​We have a specific video in the mooc for ​people who are not familiar with this kind of key exchange. ​So how is the SUCI built? ​Well, we have just said that the asymmetric key principle is used. ​There is a first key pair with a private ​key stored in the SIDF and the corresponding ​public key that is stored in the sim card. 

​For all subscribers, it's the same public key. ​And there is a second key pair that will change over time. ​The UE randomly draws a secret key and ​deduces the corresponding public key, ​which can therefore be transmitted externally. ​From the public key transmitted by the UE and ​the private key stored in the SIDF, ​the later calculates key and ​the same key is obtained by the UE ​taking this time the public key stored ​by the operator in the SIM card and ​the secret key generated by the UE. ​All this makes it possible to have ​one shared key, which was our goal. ​This key is referred to as ephemeral because ​it's only used to create the SUCI. ​This shared ephemeral key is used ​to calculate an encryption sequence. 

​Here, XOR means "exclusive OR" as usual. ​The UE XORes this sequence with the MSIN, ​(the serial number) and creates ​an encrypted version of the MSIN. ​The UE transmits this encrypted version of the MSIN and ​adds the public key it created. ​The SIDF for its part takes ​the private key it has stored and ​with the public key that is received, ​calculates the shared ephemeral key. ​It then deduces the same encryption sequence as the UE and ​by XORing the encrypted version of the MSIN, ​it is able to deduce the plaintext MSIN. ​An attacker might decide to modify the SUCI that is transmitted. ​So, we need to protect the SUCI with ​a Message Authentication Code or MAC. 

​This message authentication code is ​calculated from the shared secret key and ​it's added to that what we have seen in the SUCI. ​When the SIDF receives a SUCI, it will first check ​that there have been no changes along the way. ​It will therefore check with the shared ​secret key that the MAC is valid. ​If the MAC is not valid, we stop. ​If the MAC is valid then the MSIN is decrypted. ​Note that this avoids having a change in the SUCI along the way. ​However, it's very easy for ​an attacker to create a valid SUCI from any IMSI. 

​So verifying the MAC of a SUCI is not an authentication of the SUPI. ​On the other hand, it is possible that ​the private key might be broken. ​In this case the operator will try to use a new key but ​should not have to modify the SIM cards. ​So, he does not prepare a single private key and ​its corresponding public key. ​Instead, he prepares a set, which ​means that we have to indicate the number ​of the key that is used in the SUCI. ​So, we integrate this number into the SUCI. ​So we have a SUCI that is relatively complex. 

​In the SUCI we must first indicate the following elements, ​the type of the SUPI: it's 0 when it is an IMSI that has been used. ​The identity of the home network: ​the MCC mobile country code and the MNC mobile network code. ​We add the routing indications which ​are the equivalent of the MSIN most significant bits. ​We add an indicator because the SUCI might evolve ​in the future and we can use other algorithm and ​we integrate the network public key number. ​The UE public key itself is transmitted. ​Note that it is between 256 and 264 bits. ​Finally, we add the encrypted MSIN as ​well as the MAC to verify integrity. 

![structure of the suci](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/structure_of_the_SUCI.png)

​
This gives us a SUCI that is typically 400 bits long, ​which can be compared to the 60 bits of SUPI when it's an IMSI. ​The SUCI is therefore relatively longer. ​The terminal with the SIM card creates the SUCI. ​It transmits it to the AMF. ​The AMF as we have seen analyzes the PLMN ​code to route to the right home network. ​In the home network, there is ​an analysis of the routing indication ​in order to route to the right UDM instance. ​The SUCI is sent to the UDM and ​the SIDF function provides the SUPI, which ​can then be transmitted to the visited network or ​more precisely to the AMF of the visited network. 

​To sum up, in 5G we have the SUPI or ​the permanent identity, which in practice is ​equivalent of the IMSI we are familiar with in 4G networks. ​Normally, the SUPI is never transmitted and ​a concealed version called SUCI (SUbscription ​Concealed Identifier) is created. ​Part of the SUPI is encrypted using asymmetric cryptography. ​And we also use protection by the Message Authentication Code known as the MAC. ​The disclosure of the SUPI from the SUCI is ​provided by the SIDF of the home network. ​Note that the GUTI for "Globally-Unique Temporary ​Identifier" is still used most of the time. ​The main purpose of the SUCI is that when the GUTI cannot be used or ​is not available because it's the first time the UE is being used, ​using SUCI avoids transmitting the SUPI in clear text. 

​The limitation of the SUCI is that it's an optional mechanism. ​Therefore, there can be no absolute guarantee of security, ​since it might not be used. ​On the other hand, there is a certain operational cost for ​the operator to implement SUCI. ​The private public key pairs need to be created. ​The same cards have to be updated and the SIDF ​must be implemented. 

## UE Authentication

What are the differences between 4G and 5G ​when it comes to authentication? The general principle of authentication does not ​change in 5G compared to previous generations. ​Authentication is based on a long term symmetric key. ​In other words, it's stored both in the SIM card and in the ​ARPF ​This key is of course ​specific to each subscriber. ​The home network generates 128 bit random number. ​This number is used by the sim card ​to calculate a signed result ​RES based on the long term key. 

![UE_authentication](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/UE_authentication_1.png)

​The same calculation is done by the home network. ​An expected result called XRES is calculated and ​if there is a difference between the two, ​it means that the subscriber does not have the long term key that he or ​she tried to take a random key and therefore the UE ​is rejected. ​If RES equals XRES, then the subscriber is accepted. ​This is the authentication of the UE. Network ​authentication is also carried out with a similar ​principle. Specifically, the UE authenticates ​the network by computing an authentication token. ​As far as network authentication is concerned, ​there is no change in 5G compared to 4G. 
​
![UE_authentication](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/UE_authentication_2.png)


On the other hand, for UE ​authentication, there is an evolution: ​there is no a primary trust in the visited network and ​it's the home network that always verifies that ​the expected result and the result written by the ​UE are the same. ​Also the signed result is linked to ​the identity of the visited network ​from the country code MCC ​and the network code MNC. ​We create a string ending with .3gppnetwork.org ​and this constitutes the serving network identity. ​The visited network does indicates its identity to the home network ​and the function that calculates the expected ​result uses this serving network identity as input. ​More precisely, the network sends the RAND to the terminal and ​the terminal sends RAND to the SIM card. ​The SIM card calculates the result. Because it ​does not necessarily know the visited network, ​the first result it does is independent of the visited network, ​and from this first result we calculate ​a 2nd result called RES*, ​Which depends on the visited network. 

​We have two functions f1 and ​f2 which are applied successively and ​the same thing on the network side. ​If the results are the same, ​we accept the UE. ​If they are different, we reject it. ​Two procedures are available for authentication. ​These procedures are called AKA for ​"Authentication and Key Agreement" because ​with the same round in addition to XRES*, ​we also generate ciphering keys. ​The first procedure is called 5G-AKA. ​It's a procedure that is specific to the 5G network and ​it is optimized. With standard IETTF protocols ​We can also use a procedure called EAP AKA'. EAP stands for ​"Extensible Authentication Protocol", which is an IETF protocol. 

![UE_authentication](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/UE_authentication_3.png)

​The common thread is that in every case ​authentication is made by the home network. ​The objective of 5G-AKA is to eliminate ​illegal access in the visited network. ​It's also a way to prevent Denial Of Service known as DOS, ​at least to minimize the DOS risk. ​So, what is the solution? ​The solution is to calculate a hash from XRES*. ​This hash is called HXRES* and ​is provided to the visited network. ​The authentication is ultimately done by the home network. 


![UE_authentication](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/UE_authentication_4.png)

​Let's see how it works. ​The visited network indicates its identity: SN ID ​for Serving Network IDentity. ​The expected result XRES* is ​calculated using a random number RAND and ​from XRES* and the same random number ​the HRES* (the hash) is calculated. ​As before, the whole network ​sends the RAND to the SIM card and ​sends the HXRES* to the visited network. ​When the UE sends ​RES* back, the visited ​network is able to calculate ​HRES* using the same hash function ​from RAND and RES*. ​If there is a difference, access is immediately ​denied to the UE ​that requested it. ​If they are the same, we can continue: ​the visited network sends back ​the RES* (the value it has received) and ​the home network makes sure that the expected result ​XRES* star is the same as the RES* sent ​by the UE. Note that this expected result ​XRES* is never transmitted ​to the visited network but ​instead remains in the home network. 

​In conclusion, in 5G, ​we have mutual authentication like in 4G ​based on the long term symmetric key with ​a challenge-response type exchange. ​In previous generations, we trusted other networks ​delegating authentication to the visited network and ​sometimes we reserved authentication vectors. ​For 5G, the constraint is security. ​There is still mutual authentication, but ​it's done by the home network and more precisely ​by the AUSF, ​and it's forbidden to make reserves of authentication vectors. ​There are two protocols: ​5G-AKA, which has a hashing mechanism to allow ​the visited network to reject illegal access, ​and EAP-AKA', which reuses the IETF Protocols. 


![UE_authentication](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/UE_authentication_5.png)

5G-AKA (Authentication and Key Agreement) is the primary, mandatory authentication protocol for 5G networks, specified in 3GPP TS 33.501. It enables mutual authentication between the User Equipment (UE) and the home network (HN), providing security for 5G services, subscriber identity privacy via encrypted SUPI (Subscription Permanent Identifier), and key agreement for session encryption.

## Serviced Based Interfaces

## What is a network function?

​What is a network function? ​How is the core 5G network ​different from previous generations? ​That's what we will be looking at in this video. ​When engineers define a mobile network, ​they identify the functions and ​distribute them across different nodes. ​From 2G to 4G, ​they were trying to minimize ​the number of functions and each function ​carried out a wide range of tasks with ​the different elements in ​these tasks nested within one another. ​The functions were monolithic. ​In general, each function ​was managed by a specific piece of equipment, ​by a specific node. 

​For each pair of nodes that interacted, ​they specified the reference point. ​For example, between the MME and the HSS, ​we find reference points S6a. ​For each reference point, ​they define a protocol stack, for example, ​S6a is based on Diameter ​over the SCTP transport protocol over IP. ​But for reference point S11, ​between the MME and the Serving Gateway, ​the protocol stack is different. ​We use GTP-C, ​GPRS Tunneling Protocol in ​the control plane over UDP, over IP. ​For specifications, engineers defined ​message formats in such a way ​that you would minimize the size of the message. ​When a piece of information had ​already been sent during an exchange, ​they tried not to send it again. 

​And in addition, when we consider the exchange rules, ​they tried to limit the number of messages sent. ​That was because, particularly for 2G, ​the nodes were limited in terms of processing ​capacity and the links between nodes were also limited. ​This is no longer true with ​5G and we have a different approach. ​We specify network functions, ​but rather than trying ​to minimize the number of functions, ​we try to specialize them, ​they will be more functions, ​but they will be specialized. ​For example, the MME was replaced ​by the AMF and the SMF. ​Each network function, or NF, ​offers a kind of common interface, ​which means the same protocol stack is used everywhere. ​And we will use HTTP/2 application protocol. 

​In terms of message format, ​the organization is the same for every exchange. ​We use the term service-based ​interface because each NF here, ​the UDM, offers an interface to access a service. ​The interface is referenced by a sequence of letters. ​It's pretty logical. ​It starts with N for ​new generation and then the name of the NF, ​so NUDM for the UDM. ​The NF acts as ​a server and we call this the service producer. ​Any other NF can use the service and, that's important, ​we no longer think in terms of pairs of nodes. 

​However, an NF can use ​the service only if it is authorized to do so. ​The authorization criteria can be defined by ​the operators and are not given in the specifications. ​When an NF send request to another NF, ​we refer to the requesting NF as the service consumer. ​For example, we can say that the services provided by ​the UDM are used by the AMF and the SMF. ​The AMF and the SMF are service consumers. ​However, when we analyze the situation, ​although the principle is that any NF can be ​a service consumer of an NF service producer, ​in practice, only very few NFs ​really use the services of another NF. ​For example, in the case of UDM, ​only the AUSF, the AMF, ​and the SMF use the UDM's services. 

​That is to say that we can find the definition of ​reference point for a pair of NFs. ​The reference point is also identified ​by a code, here N13. ​It should be noted that at the heart ​of a procedure such as setting up a PDU session, ​we use the services of the SMF via the NSMF interface. ​It's the AMF that will use these services. ​But throughout the procedure, ​the SMF send requests to the AMF too, ​which means that the AMF will ​also behave as a service producer. ​So, within a given procedure, ​each NF can alternate ​between a service producer and consumer. ​When we consider all the NFs in a network, ​this gives us the concept of ​Service-Based Architecture, or SBA. 

​So what does it mean? ​A service-based architecture is ​a system architecture in ​which the system functionality is carried out by ​a set of NFs providing services to ​all the NFs that are authorized to access their services. ​The definition is a little complex. ​What it means is that when we consider the SBA, ​we don't represent the reference points, ​but instead, we illustrate the fact that each NF provides ​a service via an interface and that's ​all the NFs can access to this service. ​It should be noted that this representation ​might make you think that ​all the NFs are on the same bus. ​But of course, this is more of a mind map and ​not a physical representation ​of the connections in reality. ​Frankly speaking, it's a way ​of masking the complexity of interactions. 

### How are the services of NF organized? 

How are the services of an NF organized? ​​To answer this question we build on the example of the UDM. ​The UDM is a network function or ​an NF which is capable of supplying subscription data. ​This includes data about the services the subscriber is signed up for, ​but it can also memorize certain contextual information. ​For example, the tracking area ​in which the UE is located. ​The UDM can provide authentication vectors and ​can also monitor a certain number of events and ​supply information that the UE can use. 

​This means different services. ​Each service can be accessed through an API or ​"Application Programming Interface". ​Each API is identified by a name. ​Here, it's nudm-sdm, ​nudm because the NF is UDM ​and sdm for "Subscriber Data Management". ​There are constraints in defining the different services. ​Each NF service must be self contained, reusable and ​with a management cycle which is independent of the other ​NF services. The NF service must be stateless and ​must be managed separately from the other NF services provided by the same NF. 

​What does that mean? ​Let's take the example of the UDM. ​The UDM provides the subscription data without ​ever using the authentication service. ​This is typical of its self contained independent ​nature. In the same way, the context is managed ​independently from authentication or ​management of subscription data. ​What kind of interactions are there between NFs? ​There are two. 
​The first kind are Request-Response. ​That's pretty standard ​when we consider one client and one server. ​The response must be unique and provided within a given time limit. ​One NF can, for example, ask to know ​the data concerning subscriber services. ​It sends a request and ​then a response is sent by the UDM. ​There is also another kind of interaction, which is called Subscribe-Notify. ​Let's suppose that an NF wants to be notified. 

​If the operator changes the subscriber profile, ​that's NF will subscribe to update notifications. ​The NF sends subscription request, and ​if the operator updates the profile, ​modifies something in the subscriber profile, ​a notification is sent by the UDM to the NF that requested it. ​It should be noted that it's possible for ​one NF to subscribe to notifications on behalf of another NF. ​So, what have we seen in these two videos? ​The network is organized as a set of network functions or NFs. ​Each network function can be accessed ​through a "Service-Based Interface" or SBI. ​We use a client- ​server approach: ​an NF can be a service producer, ​any other NF can use the service, ​in which case we refer to that NF as a service ​consumer and NF can offer different NF services and ​each NF service must be self-contained, managed ​independently of the other NF services. 

​There are two main types of interactions:
 - Request-Response
 - Subscribe-Notify

when we consider all of the ​NF, which will interact which one another via SBIs, ​we get SBA, or "Service-Based Architecture".

### What is the protocol stack for an SBI?

What is the protocol stack for an SBI interface? ​How are the interactions between NFs organized? ​That's what we will see in this video. ​We have already mentioned ​that HTTP/2 is used for dialogues between NFs. ​It's an evolution of HTTP/1.1, ​providing smaller latency and greater reliability. ​In 5G, messages are encoded in JSON. ​The advantage of this format is that it's text-oriented. 


![REST_1](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_REST_1.png)

​To interpret the messages, ​it's enough to read them. ​The emphasis is therefore on ​readability and also ease of evolution. ​To avoid having messages that are too long, ​we can use a compression algorithm, ​such as the well-known gzip, ​but also other algorithms ​currently on the rise like Brotli. ​Whenever possible, a REST approach is used. ​We will look at that in a few minutes. ​To make sure exchanges are secured, ​the TLS protocol, ​"Transport Layer Security" is proposed by default. ​Operators can use other means ​of security if they wish to do so. 

![REST_2](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_REST_2.png)

​We have the following protocol stack between ​service consumer and service producer with HTTP/2, ​possibly over TLS, which is ​always over TCP itself, over IP. ​What do we mean by REST? ​REST stands for "REpresentational State Transfer". ​It's a very general concept that was defined in ​the 2000s by Roy Thomas Fielding in his doctoral thesis. ​One central notion in REST is the resource. ​What is a resource? ​A resource is an object with a type, associated data, ​and methods that allow you to operate on this object ​and it might possibly also have ​relationships with other objects, ​in other words, ​relationships between different resources. 

​Let's look at a few examples ​to help us understand what we are talking about. ​A resource can be a text file, ​it can be an HTML page, an image, a video; ​but to take a more 5G context, ​it can be a subscriber profile or the status of a UE, ​I mean, for example the technology ​it is positioned on (4G, ​5G or WI-FI) or it could be pointer, for example, ​to a video and so we find relationships between ​resources. For an API to be REST compatible, ​or what we call RESTful API, ​there are six constraints defined by Fielding. ​The first is to have ​a uniform interface to access or modify a resource. ​The second is a client-server approach. ​This is what we have in 5G. ​The third is what we call a stateless dialogue. 

![REST_3](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_REST_3.png)

​This means that the server must treat ​each request as if it's a new request. ​It's not required to refer to any history or ​the elements needed to process ​the request are present in the request. ​There is no notion of session. ​We have a property related to this, known as idempotence. ​If we consider multiple successive identical requests, ​they must have the same effect as a single request. ​This means that there is ​the possibility of caching items. ​If several requests are sent and they are ​identical, an intermediary device ​can store the response it saw on the first request and ​respond directly to the subsequent requests ​to offload the server. 

​There is the possibility of having a layered system. ​In this context, it's not about OSI layers. Rather, ​it's a question of so-called multi-tier architectures, ​where for example, ​we will separate the representation of data, ​the processing itself, and the storage, ​which can be implemented in different hardware. ​The sixth property is ​"code on demand", which is optional. ​With code on demand, ​a client can request the runtime code from a server. ​As we mentioned, one central notion ​in REST is the resource. ​Each resource in a 5G core network is accessed ​by its URI or "Uniform Resource Identifier", ​which has the following format.

![REST_4](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_REST_4.png)

​We start with a field called apiRoot, ​which includes the protocol used (HTTP or ​HTTPS when using TLS) and then includes the authority. ​The authority allows us to be ​sure that the resource is unique. ​An authority can be, for the operator Syldavia Telecom, ​http://syltel.com ​or https://5Goperator.fr for ​another operator in France. ​It could also be an IP address. ​This APIroot part is specific to the network operator. ​Then, there's something we've already seen: ​the name of the API, ​for example nudm-sdm for ​the UDM and the subscriber- data-management service, ​(of course, there are many other possible APIs) ​the API version to make it possible for the system to ​evolve and then an API specific part. ​This whole part is ​completely specified in the 3GPP recommendations. 

​There is no flexibility unlike with the apiRoot. ​It's important to note that ​there is a hierarchical structure. ​We can define a parent and children, ​grandchildren, and so on. ​For an example of ​a URI that can correspond to resource in 5G, ​we have http://syltel.com, ​that's the apiRoot, ​nudm-sdm is the name of the API. ​We have then the version (V2). ​Then we specify the subscriber ​(SUPI, the identity) ​and the specific string "am-data" for ​the subscription data related to access and mobility. ​This hierchical structure can be represented as a tree. 

​We can see for example the resources of ​the UDM as a tree and the root being the APIroot. ​We see the name of the API, then the version, ​which means for example that the profile ​of each subscriber will be indicated ​by a URI where we are going to ​find the IMSI of the subscriber, ​since in most cases, ​the SUPI is equal to the IMSI. ​The URI of a different subscriber ​with a different IMSI will have the same structure, ​but of course may have a different subscriber profile. ​Those are just a few examples. ​What is important is to see that here we ​define the resource and identify it ​without being concerned about where ​the corresponding data are physically stored. ​To conclude, in the REST approach, ​the central notion is the resource. ​With a slight exaggeration, ​we can say: everything is a resource. 

​Each resource is identified by each URI, ​"Uniform Resource Identifier", ​which starts with the variable ​operator-dependent APIroot part, ​as well as a fully specified service-dependent part. ​Actions on resources are possible with HTTP/2, ​which can be used on top of TLS for ​security and is always above TCP/IP. 

​
![REST_5](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_REST_5.png)



### How it is possible to act in a resource?

How is it possible to act on a resource? There are two main types of operations possible. ​The most common one is called CRUD, ​Create, Read, Update, Delete. ​These are Standard Restful operations that ​allow you to manipulate resource, to read it, ​to change its state, or to delete it. ​There are also, certain so-called custom ​operations that can be associated with resource ​(we have the standard format as we saw (for the URI) or ​not associated with a resource but rather with a service and ​thus we have a slightly different format. ​All operations are implemented with standard HTTP methods. 
​

![API_1](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_API_1.png)


In HTTP, we talk about methods rather than commands. ​The method involved are: PUT, POST, ​DELETE, and sometimes PATCH. ​For each request, there is a response with ​a code in the form of a three-digit number. ​When we have 200, 201, or the subsequent numbers, ​it means that the operation has been carried out successfully. ​When it's 300, 307, 308, and ​subsequent numbers, the server indicates redirection, ​usually to another server, 307 and ​308 correspond to either permanent or ​temporary redirections. ​When there is a client errors, (for example, ​the URI does not correspond to any existing resource) ​we have a response of type 404, 401, ​or the subsequent ones, this is client error. ​When for example, the server is overloaded or ​there is a problem and it cannot process the operation, ​then a response of type 500 is sent. 
​
Let's look at some examples of operations. ​The simplest operation is reading. ​In everything we look at, we assume that the TCP connection and ​possibly the TLS connection are already established. ​A reading is done with an `HTTP GET method`. ​We have the name of the method, which ​is in the message in text mode and ​then the URI of the resource we want ​to read without the API root part. ​Here, we find a format that we have already studied. ​The UDM wants to read the subscriber profile. 


![API_2](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_API_2.png)


​So, it places the name of the API ​in the URI, which in this case is nudm-sdm, ​and specifies that he wants ​the profile linked to sessions. ​The UDM consults the subscriber profile and ​responds with a 200 OK message in ​which it will place the subscriber ​profile related to the PDU sessions. ​Here, we have an example of an **idempotent operation**: ​if several successive GETs are done with ​the same URI, the response should be the **same**.

​Let's look at an example of a create operation. ​Creation is done with a `PUT` or `POST` method. ​Let's consider the case of a UE that registers in the network. ​The fact that this UE is reachable and ​that it is in a certain tracking area is taken care ​by the UDM with the "context management" service. 


![API_3](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_API_3.png)


​It is therefore a resource in the UDM. ​The URI of the resource created and sent ​In the response is precisely in the HTTP location header ​The URI still has the same format ​(we won't go back to it) ​and the AMF in order to request the creation ​of the resource does `PUT`, indicates the URI. 
 
 ​The UDM creates the resource and ​the whole URI is returned in the response. ​Let's look at some possible errors. ​If the SUPI is not known or it doesn't ​correspond to a subscriber, at this point the ​UDM will return `404 Not Found` response. ​If there are access restrictions, for example, ​if the terminal is not allowed to access this AMF or ​to be in the tracking area, it will get a "403 Forbidden" response. 
  
​Another example of creation is: setting up a PDU session. 


![API_4](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_API_4.png)


​The existence and characteristics of the session ​correspond to a resource in the UDM, always for ​the same context management service. ​The SMF at the time of creation ​sends a PUT, indicating the URI. ​Here, we can notice that there is an additional ​field that gives a session identifier ​because the same UE can do several sessions. ​The resource is created and ​again the whole URI is given in the response. ​

When the UE ends the PDU session, ​the resource must be deleted. ​This is done with a `DELETE` method. ​Consistently, the URI is indicated in the request. 


![API_5](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_API_5.png)


​The SDM deletes the resource and ​with the resource being correctly deleted ​we have a positive 200 type response. 


​Now, let's see some examples of updates. ​Updates are done with a `PUT` or a `POST` method. ​We consider, for example, ​the mobility of UE: a UE changes AMF. ​Here, we have what is considered a major modification of the resource. ​A `PUT` is sent with the URI of the resource. ​The resource is updated and ​a `204 no content` is returned. 


![API 6](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5G_API_6.png)


​The case of deregistering a UE is not a deletion like we have seen for ​the session but a **partial update**, ​because we actually want to keep the information that the UE is ​indeed in the network, that it still exists. ​And this partial update just corresponds to placing ​a flag to say that the UE is no longer reachable. ​So, we just modify a field of the resource. ​And in this case, a **PATCH method** is used.

![API 7](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5G_API_7.png)


​Finally, let's look at an example of a custom operation. ​Let's consider the AUSF that requests ​an authentication vector from the UDM. ​At first glance, we might think that this is done with a **GET method**. 

![API 8](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5G_API_8.png)

Well, in fact, no because the resource did not exist beforehand. ​So, a **POST** is specified. ​A specific URI is indicated to ​the UDM with the supi or suci. ​A fresh authentication vector is generated, which ​is returned in the 200 OK response with positive response. ​This is not a CRUD operation and it's **not idempotent**. ​Why is it not idempotent? ​Because if the AUSF sends a second request for ​a vector, obviously, ​a different vector is going to be returned. 

​Clearly, there is **no idempotent** in this example. ​More generally **POST commands are not idempotent**. 


​The set of methods, ​the set of URIs that are provided by an NF ​is specified with the open API 3.0 ​methodology, which uses the YAML language. ​YAML is a text-oriented language. ​Without going into details, looking at this example, ​we can see the following elements, ​the title of the service which is nudm-sdm (as we saw earlier); ​a description, nudm subscriber data management service; ​the URI that is specified with ​the name of the API; the version; ​and as always the API roots field that ​is available for the operator. ​The rest of the URI is indicated. ​Then, we list the methods: in this case, GET method. 

​
![API 9](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5G_API_9.png)


The name of the operation is indicated: ​Get SMF cell data, as well as the different ​parameters that can be sent and ​that sometimes are required. ​All possible response are then listed, ​a positive 200 response or 400, ​404, or several cases 505, 503. ​For all NFs and all services, such specifications ​are available on the 3GPP server. ​To conclude, we have seen that resources ​are mainly manipulated via CRUD operations, ​Create with an HTTP, PUT or POST method. ​Read with an HTTP GET method, Update with an HTTP PUT or ​PATCH method, and Delete with HTTP DELETE. ​In all cases, the resource being ​acted on is indicated by the URI, ​which thus plays a fundamental role

The 3GPP organization publishes official OpenAPI specification files that define the service-based interfaces (SBIs) for 5G core network functions. Think of these files, written in standard YAML or JSON format, as a strict API contract or a detailed blueprint for communication. They serve as the authoritative definition of how network functions must interact, ensuring that a compliant NF from one vendor can seamlessly communicate with one from another.

This blueprint is a machine-readable file that precisely defines every aspect of an NF's interface, leaving no room for ambiguity.

reference:
https://www.3gpp.org/technologies/openapis-for-the-service-based-architecture
https://forge.3gpp.org/rep/all/5G_APIs

#### API endpoints
The exact URL paths that each network function must expose for its services.

#### HTTP method
The correct method (GET, POST, etc.) to be used for each specific operation.

#### Parameters
A full definition of all required and optional parameters for any given API call.

#### Message structure
The exact structure of request and response messages, ensuring all NFs "speak" the same language.

#### Data models
The specific data types and validation rules for every field to ensure data integrity.

#### Error responses
A complete list of possible success and error status codes, so a client application knows how to handle any outcome. The exact structure of request and response messages, ensuring all NFs "speak" the same language.

The free5GC developers can access these specifications from:
 - 3gpp web site: https://www.3gpp.org/ftp/Specs/archive/29_series/

OpenAPI specifications create a shared language between all 5G Core Network Functions. By defining every endpoint, method, and message structure, they make true interoperability and vendor neutrality possible.

## Virtualiation: How is it possible to have both a dynamic and elastic 5G core network ?

​How is it possible to have both a dynamic and ​elastic 5G core network? ​To begin with, let's clarify the vocabulary. ​When we talk about network function or NF, ​we mean something that is defined to receive and ​send packets in order to provide a certain service. ​If we set aside the UPF, which is not what we are talking ​about here, all NFs are in the control plane. ​In other words, the packets are control ​messages, namely PUTs and GETs, as we have seen. ​When we talk about an NF instance, ​we mean something that actually receives and sends packets, ​I mean that is deployed in the network, that is active. 


​Strictly speaking, control messages are not exchanged ​between NFs but rather between NF instances. ​We can consider two properties, ​the first property is "elasticity", which can be ​seen at the ability of new instances identical ​to existing ones to start and of course to stop. ​And the second property is dynamicity, which can be seen ​at the possibility of starting new instances with different services and ​different characteristics from the existing instances. ​This is the case, for example, when we want to ​deploy a new network slice to offer specific services, ​an instance can be reached in one of two ways. ​First, it can be reached by indicating ​a symbolic name, which is called ​the **Fully Qualified Domain Name (FQDN)**. ​For example, the operator Syldavia Telecom ​will have a symbolic name for an SMF, ​let's say smf.sytel.com. ​Or if the operator has an SMF that is in Klow (a city) ​the choice might be to make smf.klow.syltel.com. 


![nf 1](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_NF_1.png)


​Or an SMF linked to a particular slice ​smf2.slicev2x.syltel.com. ​The second way that an instance can be reached ​is by directly indicating the IP address. ​If you indicate a symbolic name, then you have to go through a DNS server, ​which will convert the symbolic name into an IP address. ​If you enter the IP address directly, ​there is of course no DNS, but you lose flexibility. ​To uniquely identify each instance in the network, ​we use a mechanism specified by the IETF and ​an identity called the **"Universally Unique IDentifier" or UUID**. ​If you are interested in this, ​you might want to check out RFC 4122 ​where version 4 of the UUID is used for 5G. ​The UUID is chosen by each instance and ​its uniqueness across space and time is guaranteed. 


This is facilitated by the fact that ​the UUID is encoded on 128 bits, which gives ​us 10 to the power 38 different UUID values. ​Each instance can correspond to a single hardware. ​Note, for example, it might be a specific piece of hardware running somewhere or ​it may be a virtual machine on generic hardware. ​It might also be a distributed instance spread across multiple machines. ​I'd like to emphasize the difference between the UUID and the FQDN. ​The UUID is only a unique identifier of the instance ​regardless of the network configuration ​while the FQDN is a symbolic name that allows you ​to reach the instance, with a DNS of course. 


![nf 2](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_NF_2.png)

​
​To know the number and the instances that are active at a given time, ​since this can change over time, we need a repository service. ​This service is provided by the **NRF** or **​"Network-Function Repository Function"**. ​The NRF maintains a list of the NF instances that are available and ​the services provided by each instance. ​An instance can also register with the NRF when ​it starts or de-register when it stops. ​Let's note that there is the possibility of doing things ​the old-fashioned way; by this, I mean that the list of instances ​is stored and configured in the NRF by the operator. ​Of course, in this case, we lose the elastic ​nature of the network, thanks to the NRF. ​The other instances are notified ​of instances that start and stop. 


​And finally, the NRF plays the role of an authorization server. ​We will see this in the specific session on this topic. ​Let's look at the registration procedure of an NF instance:

![nf 3](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_NF_3.png)

​There is an API name associated with ​this procedure, **nnrf-nfm** for ​"network function management". ​In the NF instance, we configure ​the FQDN of NRF that is available. ​The general principle of the procedure is shown here. ​But let's look at it more closely in practice. 


![nf 4](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_NF_4.png)

Let's assume that a new SMF instance starts and ​registers with the NRF. **We'll ignore all the security ​related procedures to focus on the registration itself**. ​The SMF is configured with the symbolic name of the NRF instance. ​It makes a DNS query to get the IP address of that NRF. ​It establishes a TCP connection with ​the NRF and then chooses UUID. ​In the context of 3GPP standards, ​the UUID is called nfinstanceID for ​"network-function instance IDentifier". ​For each active instance in the network, ​there is a corresponding resource in the NRF. 


In other words, to indicate the instance that is starting, ​we create this resource and therefore sends a PUT. ​We use the API that we have already seen and ​the SMF instance implements the UUID that it has chosen. ​Within the parameters of the method, ​we again indicate this instance identity, ​the fact that it's an SMF and ​either the symbolic name of the SMF or ​the IP address along with other parameters. ​All this make the NF profile. ​As I mentioned, the NRF creates resource ​corresponding to the instance that has just started and ​therefore returns a 201 created with ​the corresponding URI as an echo. ​The uniqueness of the UUID ensures that the URI is also unique. ​In the reply, there is a time value. 

Indeed, if an instance of an SMS were to fail suddenly, ​we would still have the resource on the NRF side and ​not truly active instance in the network. ​So, we need to avoid this problem. ​We do this by defining a maximum duration ​called `heartBeatTimer`. At the end of this ​duration, the SMF must report to the NRF. ​This requires using a `PATCH` method and ​it re-specifies the URI of the resource ​corresponding to the instance in the PATCH. 


![nf 5](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_NF_5.png)


Of course, there is de-registration scenario. ​If the SMF instance stops, ​we sent a `DELETE` method with the URI ​without the root API corresponding ​to the resource that bound to the instance, ​and then the SMF instance can actually stop. 


![nf 6](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_NF_6.png)


Now, let's have a look at the discovery procedure ​that allows an NF instance to discover the other ​NF instances and the services they offer. ​We have different service, therefore a different ​API name: here, nnrf-disc for discovery. ​The operation principle is shown here. ​We've already said that there can be a positive or ​a negative answer but we will explain it ​using a more concrete example. ​We do not consider security in the same way as before. ​Let's assume that the NRF points directly to the IP address. 

![nf 7](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5G_NF_7.png)


​The AMF, for example, is looking for ​an SMF instance to establish PDU sessions. The AMF instance sends GET with a URI ​corresponding to the discovery service and ​indicates that it looks for an SMF. ​For example, as one criterion, it specifies the list ​of tracking areas that should be covered by the SMF instance ​that it is looking for and there are other criteria. ​In the 3GPP recommendations, ​there are more than 90 specified criteria! ​The NRF looks for an SMF instance that meets the criteria and ​will return a 200 OK message ​indicating the unique identity UUID or ​NF instance identity corresponding to the NF instance plus, ​in our example, the IP address. ​Then it just needs to establish a TCP ​connection and the AMF can send PUT, ​POST, or GET to use SMS services. ​When a symbolic name is used, the procedure is very similar in principle. ​The response to the GET contains the symbolic name, ​which means that the AMF instance has to ​do DNS query to convert the symbolic name ​to an IP address, the rest is the same.

![nf 8](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/atch_5g_NF_8.png)

The AMF instance sends `GET` with a URI ​corresponding to the discovery service and ​indicates that it looks for an SMF. ​For example, as one criterion, it specifies the list ​of tracking areas that should be covered by the SMF instance ​that it is looking for and there are other criteria. ​In the 3GPP recommendations, ​there are more than 90 specified criteria! ​The NRF looks for an SMF instance that meets the criteria and ​will return a 200 OK message ​indicating the unique identity UUID or ​NF instance identity corresponding to the NF instance plus, ​in our example, the IP address. ​Then it just needs to establish a TCP ​connection and the AMF can send `PUT`, `​POST`, or `GET` to use SMS services. ​When a symbolic name is used, the procedure is very similar in principle. ​The response to the GET contains the symbolic name, ​which means that the AMF instance has to ​do DNS query to convert the symbolic name ​to an IP address, the rest is the same. 
​
![nf 9](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_NF_9.png)

​
​To summarize what we've seen here, ​it's possible in the 5G network to start and stop NF instances. ​The NRF plays a central role, ​it is a repository of active instances. ​There is a procedure for discovering NF instances ​that can be used by each authorized NF. ​In the request, the type of NF and the criteria are indicated, ​there can be a fair number of criteria. ​In the response, the NRF instance ​indicates the NF instance in the form ​of either an IP address or an FQDN. ​Finally, there is a procedure for ​registering each new NF instance with the NRF.


![nf 10](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_NF_10.png)

## How does the notification service work? 

​The network is aware of ​a large number of events that occur. ​For example, with respect to user actions, ​when we have a mobility event due ​to a UE changing tracking areas, ​there is a location update that is managed by the AMF. ​This event is therefore known to the AMF. ​When a terminal gets ​turned on or off by a user, ​there is a registration and deregistration of the UE. ​These are managed by the AMF, ​which is therefore aware of them.

![notification](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_notification_01.PNG)

​In the same way, ​the SMF manages the setup and release of PDU sessions. ​There are other possible events: for example, ​the modification of the subscriber profile ​in the UDM or the ​modification of the QoS level ​for a PDU session managed by the PCF. ​We have a large number of events ​that are managed by the different NFs. ​Event notification can open the field ​to a wide range of value added services. ​There's a lot of potential. ​There is a definition of ​notification services and in order to have them, ​the NF that wants to be notified must subscribe. ​We have a subscription procedure ​and unsubscription procedure. 

​Let's have a look at the general principle, ​which we have already mentioned a little. ​We have a consumer NF, ​which wants to be notified ​of events occurring in a producer NF. ​To do this, the consumer NF sends ​a POST method which is ​positively acknowledged with a 200 response. ​When the event occurs in the producer NF, ​the producer NF is the one that will notify and ​thus send a post with a response hopefully positive. ​During this phase, the producer NF acts as ​an HTTP client and ​the consumer NF acts as an HTTP server. ​We have a role reversal. ​The producer NF becomes ​the consumer NF and vice versa on the other side. 

![notification_subscription](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_notification_04_subscription.PNG)


​When the event occurs, ​as we have said, a POST is sent. ​This POST corresponds to a URI. ​This URI is linked to ​a resource on the side of the consumer NF. ​At the time of the subscription, ​a callback URI has to be created on the consumer NF side. ​This callback URI is sent in the initial POST, ​stored by the producer NF, ​and as soon as the event occurs, ​this callback URI that is associated with ​the POST is the one that is sent by the producer NF. ​The consumer NF has to be able ​to stop the subscription if it wishes to. ​To do this, we will use a DELETE method. 

​But by the same reasoning we need a URI. ​In this DELETE method, ​there may be several NF's ​that have subscribed to ​notifications from this producer NF. ​Each subscription must be identified in a unique way. ​To do this, the producer ​NF chooses a subscription identity and ​uses it to create ​a URI that gets sent in the subscription response. ​This URI is stored by the consumer NF, ​and if the consumer NF wants to stop the subscription, ​it will use this URI that has ​been created in the request. ​The resource that corresponds ​to the subscription gets deleted. ​Like any subscription, ​this subscription is created for a limited time. 
​
We will therefore add ​a time limit in the form of an expiration date. ​There is a date which is requested by ​the consumer and the date chosen by the producer, ​which must be sooner or equal to the proposed date. ​When this date arrives, ​this corresponds to maximum subscription period ​and the resource is deleted. 

![notification delete](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_notification_05_subscription_DELETE.PNG)


​Let's look at a slightly more specific example ​of a notification scenario. ​The SMF here is looking to be ​notified of the user profile changes in the UDM. ​This is a service that is provided by the UDM ​in the nudm-sdm API, ​sdm for subscriber data management. ​This subscription is set up for a given subscriber, ​a given UE, identified by its SUPI, ​and then the keyword sdm-subscriptions ​corresponds to this particular service. 

![notification_example](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_notification_02_example.PNG)


​We have the callback URI that we have already mentioned, ​as well as the other fields. ​The callback URI is stored, ​the UDM chooses a subscription identity, ​and this identity is used to ​create the URI corresponding to the subscription. ​We reuse the previous request fields ​and create a child resource, ​adding the subscription identity. ​If the SMF wants to stop the subscription, ​it uses this URI as we can see in the example. ​When the event occurs, as before, ​the callback URI is used. ​

In summary, notification services ​start with a subscription phase. ​The consumer NF places ​the callback URI in the subscription requests. 
​The produce rule NF creates ​a new resource with the subscription ID ​and places the newly formed URI ​in the subscription response. ​When the event requiring notification occurs, ​the rules change: the producer NF becomes a consumer, ​and the consumer NF becomes a producer. ​There are two cases for the end of the subscription, ​either it can be deleted by ​a DELETE or there is a timeout.

![notification_summary](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/arch_5g_notification_03_summary.PNG)
​
## 5G Architectures: Stand Alone (SA) and Non Stand Alone (NSA)

5g is aware that the adoption of 5G networks will not happen in a day. The firs step is comply with  eMMB: Enhaced Mobile Broad-Band, 
the other key points:  mMTC(Massive Machine Type Communications) and URLLC (Ultra-Reliable and Low Latency Communications) will come later. 

So the migration path for every operator MNO will be a little different, and the 3gpp consortium has given a lot of options to the 
operatators to choose from. 

From the RAN (Radio Access Network) point of view, there are: 
 - LTE RAN
 - 5G RAN
 - Master LTE RAN + Support 5G RAN. The 5G ran connects to the core network though the LTE RAN.
 - Master 5G RAN + Support LTE RAN. 
 
 From the core network point of view, the options are: 
 - LTE EPC (Evolved Packet Core) (the core of a 4G network)
 - 5G Core
 
 
 | Connectivity Options | Core Network | Master RAT | Secondary RAT | 3GPP term | 3GPP release |
 |  :-: |  :-: |  :-: | :-: | :-: | :-: | 
 | Option 1 | EPC | LTE | - | LTE | Rel. 8|
 | Option 3 | EPC | LTE | NR | EN-DC | Rel. 15, Dec 2017|
 | Option 2 | 5G  | NR | - | NR | Rel. 15, June 2018|
 | Option 4 | 5G  | NR | eLTE | NE-DC | Rel. 15, March 2019|
 | Option 5 | 5G  | eLTE | - | eLTE | Rel. 15, June 2018|
 | Option 7 | 5G  | eLTE | NR | NGEN-DC | Rel. 15, March 2019|

 
 references: 
 - https://www.gsma.com/futurenetworks/wp-content/uploads/2018/04/Road-to-5G-Introduction-and-Migration_FINAL.pdf
 - https://blog.3g4g.co.uk/2017/10/5g-architecture-options-for-deployments.html
 - https://devopedia.org/5g-deployment-options
 - https://www.ericsson.com/en/reports-and-papers/ericsson-technology-review/articles/simplifying-the-5g-ecosystem-by-reducing-architecture-options
 
 
 
 ## 5G Deployment architectures:

 ![5G Deployment architectures](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/5g_deployment_models.PNG)

 - reference: 5G Deployment and Architecture: https://youtu.be/ZLSKDxoqw6o

 At the 3gpp RT 21.915, two deployment options are defined for 5G:
 
 - NSA (Non-Stand Alone) architecture, where the 5G radio access network (AN) and its New Radio (NR) 
 interface is used in conjunction with the existing LTE and EPC infraestructure Core Network (respectively
 4G radio and 4G core), thus making the NR technology available without network replacement. In this configuration, 
 only the 4G services are supported, but enjoying the capacities offered by the 5G New Radio (lower lattency, etc). 
 The NSA is also known as "E-UTRA-NR Dual connectivity (EN-DC)" or "Architecture Option 3". 
 
 - SA (Stand-Alone) architecture, where the NR is connected to the 5G CN. Only in this configurartion, the
 full set of 5G Phase 1 services are supported. SA is known as "Architecture Option 2". 
 
 Benefits of 5g NSA: 
 - deliver high-speed connectivity to consumers with 5G-enabled services
 - leverage existing network investments in transpor and mobile core. 
 
 Benefits of 5g SA: 
 - MNOs can launch new 5G services such as smart cities, and smart factories. 
 - It is fully virtualized, cloud-native architecture (CNA), which introduces new ways to develop, deploy and manage services. 
 - The architecture enables end to end slicing to logically separate services. 
 - Automation drives up efficencies while driving down the cost of operating the network. 
 - By standardizing on a cloud-native approach, MNOs can also rely on best of breed innovation from vendors and open-source communities. 
 - By choosing a cloud-native microservice-based architecture, MNOs can also decide on a variety of deployment models such as on-prem
 private cloud, public cloud, or hybrid to meet their bussines objetives. 
 
 references:
  - https://www.gsma.com/futurenetworks/wiki/5g-implementation-guidelines/
  - https://www.gsma.com/futurenetworks/wp-content/uploads/2019/03/5G-Implementation-Guidelines-NSA-Option-3-v2.1.pdf
 

## 5G Core enabling technologies 

The 5G core relies on the following technologies:

- Virtualization:
- Cloud Native
- Containers
- Microservices
- Automation and orchestration

### Virtualization

Traditionally mobile core applications relied on propietary custom HW. In this HW the OEMs deployed their custom applications.
That dedicated HW equiptment was optimized for a given speed and performance and had a fixed capacity. Capacity incrase often
required HW update or add additional resources (CPU, storage, memory...). That model is not cost effective nowadays. 

Virtualization allows running applications on virtual machines, which run on COTS hw. This enables decoupling of the
application and HW and therefore offers great flexibility at a lower cost. 


### Cloud Native

Cloud native architectures have gained a lot of attention as operators try to follow the same architecture principles as hyperscallers like Google, Amazon ...

Cloud native is not a single concept but instead is a set of principles. Some of these: 

- Infraestructure agnostic - apps don't depend on HW and resources. 
- Software decomposition and Life Cycle Management - apps run in smaller and manageable pieces unlike a monolithic application. 
- Resilience - due the distributed nature of applications impact on local maintenance of faults is isolated to local instances and doesn't affect overall functionality. 
- Orchestration and Automation - Apps can be managed using orchestrators like Kubernetes or OpenStak. Turn-up/down, scaling and mainteinance (upgrade, logging ...) is automated. 

### Containers 

Containers are independent hosts for applications that use a single, stripped-down version of an operating system to run. 

Virtual machines are a full version of an operating system. Containers run a virtualized workload, processed by an application 
broken up into microservicies, making them more ligthweight and flexible than VM. 

vm can run a full, unaltered aplication orchestated by an hypervisor. 

Both scale up and down quickly an easily. 

### Microservices

Microservices refers to the architectural and organizational approach to software development where applicantion is composed of smaller 
independent services that interact with each other over well defined APIs. 

Form the basis for service based architecture (SBA).

Several benefits: 
- Components have limited scope  and therefore changes can be made quickly and efficently. 
- Instances can be added, removed on demand adding ease scalability.
- Independent software upgrades
- Ease of debugging due to limited scope of components. 

#### Automation

5G needs to support rapid scaling up/down and life cycle management of network applications (turn up/down, upgrade, logging etc)

Automation technologies for orchestration can help achieve these goals. 

So far SON (Self-Optimized-networks) capabilities have been leveraged on the RAN side. For example - automatic neighbor relations

Operators 

## 5G core architecture

There are two ways of virtualizing the architecture: 
 - serviced base architecture view
 - point to point interface based architecture
 
 
 ### SBA (Serviced Base Architecture)
 
 - reference: https://www.3gpp.org/technologies/5g-system-overview
 
## Specifications

The 5G system is described in over a thousand 3GPP Technical Reports (TRs) and Technical Specifications (TSs).

To help you find more information, e.g. on the dynamic behaviour of 5GS (procedures, etc) or on some specific aspect of 5G, some key TRs and TSs are listed here:

 - 5G charging: https://www.etsi.org/deliver/etsi_ts/132200_132299/132290/16.07.00_60/ts_132290v160700p.pdf
 - [TS 22.261](https://portal.3gpp.org/desktopmodules/Specifications/SpecificationDetails.aspx?specificationId=3107), "Service requirements for the 5G system".
 - [TS 23.501](https://portal.3gpp.org/desktopmodules/Specifications/SpecificationDetails.aspx?specificationId=3144), "System architecture for the 5G System (5GS)" - 
 - [TS 23.502](https://portal.3gpp.org/desktopmodules/Specifications/SpecificationDetails.aspx?specificationId=3145) "Procedures for the 5G System (5GS)
 - [TS 32.240](https://portal.3gpp.org/desktopmodules/Specifications/SpecificationDetails.aspx?specificationId=1896) “Charging management; Charging architecture and principles".
 - [TS 24.501](https://portal.3gpp.org/desktopmodules/Specifications/SpecificationDetails.aspx?specificationId=3370) "Non-Access-Stratum (NAS) protocol for 5G System (5GS); Stage 3"
 - [TS 38.300](https://portal.3gpp.org/desktopmodules/Specifications/SpecificationDetails.aspx?specificationId=3191) "NR; NR and NG-RAN Overall description; Stage-2"
 - Referenced Specifications:
[TS 22.278](https://portal.3gpp.org/desktopmodules/Specifications/SpecificationDetails.aspx?specificationId=641), "Service requirements for the Evolved Packet System (EPS)".
 - [TS 22.011](https://portal.3gpp.org/desktopmodules/Specifications/SpecificationDetails.aspx?specificationId=566), "Service accessibility".
 - [TS 22.101](https://portal.3gpp.org/desktopmodules/Specifications/SpecificationDetails.aspx?specificationId=605), "Service aspects; Service principles".
 - [TS 22.185](https://portal.3gpp.org/desktopmodules/Specifications/SpecificationDetails.aspx?specificationId=605), "Service requirements for V2X services".
 - [TS 22.071](https://portal.3gpp.org/desktopmodules/Specifications/SpecificationDetails.aspx?specificationId=584), "Location Services (LCS); Service description".
 - [TS 22.115](https://portal.3gpp.org/desktopmodules/Specifications/SpecificationDetails.aspx?specificationId=608), "Service aspects; Charging and billing".
 - [TS 22.153](https://portal.3gpp.org/desktopmodules/Specifications/SpecificationDetails.aspx?specificationId=617), "Multimedia priority service".
 - [TS 22.173](https://portal.3gpp.org/desktopmodules/Specifications/SpecificationDetails.aspx?specificationId=620), "IP Multimedia Core Network Subsystem (IMS) Multimedia Telephony Service and supplementary services".
 - [TS 22.186](https://portal.3gpp.org/desktopmodules/Specifications/SpecificationDetails.aspx?specificationId=3180), "Service requirements for enhanced V2X scenarios".
 - [AMF](https://portal.3gpp.org/desktopmodules/Specifications/SpecificationDetails.aspx?specificationId=3445) "AMF specs" - https://www.etsi.org/deliver/etsi_ts/129500_129599/129518/16.04.00_60/ts_129518v160400p.pdf
 - [SMF](https://portal.3gpp.org/desktopmodules/Specifications/SpecificationDetails.aspx?specificationId=3448) SMF specifications.
 
## System architecture for the 5G system (5GS)

 - reference: https://www.3gpp.org/technologies/5g-system-overview

```
       ┌─────────┐     ┌───────┐  ┌───────┐  ┌────────┐  ┌───────┐ ┌────────┐     
       │  NSSF   │     │  NEF  │  │  NRF  │  │  PCF   │  │  UDM  │ │   AF   │                NSSF: Network Slice Selection Function - slicing in 5G
       └────┬────┘     └───┬───┘  └───┬───┘  └───┬────┘  └───┬───┘ └───┬────┘                NEF:  Network Exposure Function - (5G security related)
            │              │          │          │           │         │                     NRF:  Network Repository Function -  stores the profiles of the other NFs by providing support for NF register, deregister and update service to NF and their services.
            │              │          │          │           │         │                     PCF:  Policy Control Function - controls that the user data traffic does not exceed the negotiated bearer(s) capacities
            │              │          │          │           │         │                     UDM:  Unified Data Management - functionally similar to 3G and 4G's HSS (and 2G's HLR)
    ───────┬┴──────────────┴────┬─────┴─────┬────┴───────────┴─────────┴─────────            AF:   Application Function - controlling the application(s)
           │                    │           │                                                AUSF: Authentication Server Function - (5G security related) - This is what authenticates UEs.
           │                    │           │                                                AMF:  Access and Movility Management Function
           │                    │           │                                                SMF:  Session Management Function - handles the calls and sessions, and contacts the UPF accordingly
       ┌───┴────┐         ┌─────┴───┐    ┌──┴───┐                                            RAN:  Radio Access Network
       │  AUSF  │         │   AMF   │    │ SMF  │                                            UPF:  User Plane Function -  handling the user data
       └────────┘        /└────┬────┘    └──────┘\                     Control Plane         DN:   Data Network
                        /      │                  \              --------------------                 
                       /       │                   \                   User Plane
                    N1/        │N2                  \ N4                            
                     /         │                     \                            
                    /          │                      \                           
           ┌──────┐/       ┌───┴───┐        N3         ┌─────┐     N6     ┌──────┐
           │  UE  ├────────┤ (R)AN ├───────────────────┤ UPF ├────────────┤  DN  │
           └──────┘        └───────┘                   └─────┘            └──────┘
                                                                                  
                                                              
                                                                                  
    SYSTEM  ARCHITECTURE FOR THE 5G SYSTEM (5GS) IN SERVICE BASED REPRESENTATION
```

   
## 5G Core Network <a name="5GCoreNetwork"></a>

- reference: https://github.com/emanuelfreitas/3gpp-documentation

* [TS 23.501 - System Architecture for the 5G System](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2023.501%20-%20System%20Architecture%20for%20the%205G%20System/Rel-17/ts_123501v170900p.pdf)
* [TS 23.502 - Procedures for the 5G System (5GS)](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2023.502%20-%20Procedures%20for%20the%205G%20System%20(5GS)/Rel-17/ts_123502v170900p.pdf)
* [TS 23.503 - Policy and Charging Control Framework for the 5G System](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2023.503%20-%20Policy%20and%20Charging%20Control%20Framework%20for%20the%205G%20System/Rel-17/ts_123503v170900p.pdf)
* [TS 29.501 - Principles and Guidelines for Services Definition](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.501%20-%20Principles%20and%20Guidelines%20for%20Services%20Definition/Rel-17/ts_129501v170700p.pdf)
* [TS 29.571 - Common Data Types for Service Based Interfaces](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.571%20-%20Common%20Data%20Types%20for%20Service%20Based%20Interfaces/Rel-17/ts_129571v170900p.pdf)
* [TS 33.501 - Security architecture and procedures for 5G System](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2033.501%20-%20Security%20architecture%20and%20procedures%20for%205G%20System/Rel-17/ts_133501v171000p.pdf)

###### Common APIs
* [TS 29.571 Common Data Types](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29571_CommonData.yaml)
* [TS 29.122 Common Data Types](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29122_CommonData.yaml)

### Architecture <a name="5GArchitecture"></a>
#### 5G System architecture
![5G System architecture](https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/documentation/images/5G%20System%20architecture.png "5G System architecture")

#### PCF/CHF Interfaces
![PCF Interfaces](https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/documentation/images/PCF%20Interfaces.png "PCF Interfaces")

### Reference points <a name="5GReferencePoints"></a>
| Interface | Description |
|:---------:|:------------|
| N1 | Reference point between the UE and the AMF |
| N2 | Reference point between the (R)AN and the AMF |
| N3 | Reference point between the (R)AN and the UPF |
| N4 | Reference point between the SMF and the UPF |
| **N5** | Reference point between the PCF and an AF |
| N6 | Reference point between the UPF and a Data Network |
| **N7** | Reference point between the SMF and the PCF |
| N8 | Reference point between the UDM and the AMF |
| N9 | Reference point between two UPFs |
| N10 | Reference point between the UDM and the SMF |
| N11 | Reference point between the AMF and the SMF |
| N12 | Reference point between AMF and AUSF |
| N13 | Reference point between the UDM and Authentication Server function the AUSF |
| N14 | Reference point between two AMFs |
| **N15** | Reference point between the PCF and the AMF in the case of non-roaming scenario, PCF in the visited network and AMF in the case of roaming scenario |
| N16 | Reference point between two SMFs (in roaming case between SMF in the visited network and the SMF in the home network) |
| N17 | Reference point between AMF and 5G-EIR |
| N18 | Reference point between any NF and UDSF |
| N22 | Reference point between AMF and NSSF |
| **N23** | Reference point between PCF and NWDAF |
| **N24** | Reference point between the PCF in the visited network and the PCF in the home network |
| N27 | Reference point between NRF in the visited network and the NRF in the home network |
| **N28** | Reference point between PCF and OCS |
| N31 | Reference point between the NSSF in the visited network and the NSSF in the home network |
| N32 | Reference point between SEPP in the visited network and the SEPP in the home network |
| N33 | Reference point between NEF and AF |
| N34 | Reference point between NSSF and NWDAF |
| N35 | Reference point between UDM and UDR |
| **N36** | Reference point between PCF and UDR |
| N37 | Reference point between NEF and UDR |
| **N40** | Reference point between SMF and the CHF |
| N50 | Reference point between AMF and the CBCF | 

### Services <a name="5GServices"></a>
| Producer | Consumer | Service | Standard | API |
|:--------:|:--------:|:--------|:--------:|:----|
| [PCF](#PCF)     | AF           | Npcf_PolicyAuthorization  | [TS 29.514](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.514%20-%20Policy%20Authorization%20Service/Rel-17/ts_129514v170900p.pdf) | [PCF Policy Authorization Service](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29514_Npcf_PolicyAuthorization.yaml) |
|                 | SMF          | Npcf_SMPolicyControl      | [TS 29.512](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.512%20-%20Session%20Management%20Policy%20Control%20Service/Rel-17/ts_129512v171100p.pdf) | [Session Management Policy Control Service](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29512_Npcf_SMPolicyControl.yaml) |
|                 | AMF          | Npcf_AMPolicyControl      | [TS 29.507](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.507%20-%20Access%20and%20Mobility%20Policy%20Control%20Service/Rel-17/ts_129507v170900p.pdf) | [Access and Mobility Policy Control Service](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29507_Npcf_AMPolicyControl.yaml) |
|                 | NEF          | Npcf_EventExposure        | [TS 29.523](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.523%20-%20Policy%20Control%20Event%20Exposure%20Service/Rel-17/ts_129523v170800p.pdf) | [PCF Event Exposure Service](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29523_Npcf_EventExposure.yaml) |
|                 |              | Npcf_BDTPolicyControl     | [TS 29.554](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.554%20-%20Background%20Data%20Transfer%20Policy%20Control%20Service/Rel-17/ts_129554v170400p.pdf) | [PCF BDT Policy Control Service](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29554_Npcf_BDTPolicyControl.yaml) |
| [NWDAF](#NWDAF) | PCF          | Nnwdaf_EventsSubscription | [TS 29.520](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.520%20-%20Network%20Data%20Analytics%20Services/Rel-17/ts_129520v171100p.pdf) | [Nnwdaf_EventsSubscription Service API](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29520_Nnwdaf_EventsSubscription.yaml) |
|                 |              | Nnwdaf_AnalyticsInfo      | [TS 29.520](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.520%20-%20Network%20Data%20Analytics%20Services/Rel-17/ts_129520v171100p.pdf) | [Nnwdaf_AnalyticsInfo Service API](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29520_Nnwdaf_AnalyticsInfo.yaml) |
| [CHF](#CHF)     | PCF          | Nchf_SpendingLimitControl | [TS 29.594](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.594%20-%20Spending%20Limit%20Control%20Service/Rel-17/ts_129594v170500p.pdf) | [Spending Limit Control](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29594_Nchf_SpendingLimitControl.yaml) |
|                 | NF           | Nchf_ConvergedCharging    | [TS 32.291](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2032.291%20-%205G%20system,%20charging%20service;%20Stage%203/Rel-17/ts_132291v170700p.pdf) | [Converged Charging](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS32291_Nchf_ConvergedCharging.yaml) |
|                 | NF           | Nchf_OfflineOnlyCharging  | [TS 32.291](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2032.291%20-%205G%20system,%20charging%20service;%20Stage%203/Rel-17/ts_132291v170700p.pdf) | [Offline Only Charging](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS32291_Nchf_OfflineOnlyCharging.yaml) |
| [UDR](#UDR)     | PCF          | Nudr_DataRepository       | [TS 29.504](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.504%20-%20Unified%20Data%20Repository%20Services/Rel-17/ts_129504v171100p.pdf) | [Unified Data Repository Service](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29504_Nudr_DR.yaml) |
| [BSF](#BSF)     | PCF, NEF, AF | Nbsf_Management           | [TS 29.521](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.521%20-%20Binding%20Support%20Management%20Service/Rel-17/ts_129521v170900p.pdf) | [Binding Support Management Service API](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29521_Nbsf_Management.yaml) |
| [NRF](#NRF)     | ALL NF       | Nnrf_NFManagement         | [TS 29.510](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.510%20-%20Network%20Function%20Repository%20Services/Rel-17/ts_129510v171000p.pdf) | [NRF NFManagement Service](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29510_Nnrf_NFManagement.yaml) |
|                 |              | Nnrf_NFDiscovery          | [TS 29.510](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.510%20-%20Network%20Function%20Repository%20Services/Rel-17/ts_129510v171000p.pdf) | [NRF NFDiscovery Service](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29510_Nnrf_NFDiscovery.yaml) |
|                 |              | Nnrf_AccessToken          | [TS 29.510](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.510%20-%20Network%20Function%20Repository%20Services/Rel-17/ts_129510v171000p.pdf) | [NRF OAuth2 Authorization](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29510_Nnrf_AccessToken.yaml) |

### Network Functions and entities  <a name="5GNetworkFunctions"></a>

#### AMF (Access and Mobility Management Function)<a name="AMF"></a>

###### APIs
* [Communication](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29518_Namf_Communication.yaml)
* [Event Exposure](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29518_Namf_EventExposure.yaml)
* [Location](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29518_Namf_Location.yaml)
* [MT](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29518_Namf_MT.yaml)

#### AUSF (Authentication Server Function)<a name="AUSF"></a>
* [TS 29.509 - Authentication Server Services](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.509%20-%20Authentication%20Server%20Services/Rel-17/ts_129509v170900p.pdf)
###### APIs
* [UE Authentication](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29509_Nausf_UEAuthentication.yaml)
* [SoR Protection](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29509_Nausf_SoRProtection.yaml)

#### BSF (Binding Support Function)<a name="BSF"></a>
* [TS 29.521 - Binding Support Management Service](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.521%20-%20Binding%20Support%20Management%20Service/Rel-17/ts_129521v170900p.pdf)

#### CHF (Charging Function) <a name="CHF"></a>
* [TS 29.594 - Spending Limit Control Service](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.594%20-%20Spending%20Limit%20Control%20Service/Rel-17/ts_129594v170500p.pdf)
* [TS 32.240 - Telecommunication management; Charging management; Charging architecture and principles](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2032.240%20-%20Charging%20architecture%20and%20principles/Rel-17/ts_132240v171000p.pdf)
* [TS 32.255 - Telecommunication management; Charging management; 5G data connectivity domain charging; Stage 2](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2032.255%20-%20Telecommunication%20management;%20Charging%20management;%205G%20data%20connectivity%20domain%20charging;%20Stage%202/Rel-17/ts_132255v171000p.pdf)
* [TS 32.290 - Telecommunication management; Charging management; 5G system; Services, operations and procedures of charging using Service Based Interface (SBI)](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2032.290%20-%20Services,%20operations%20and%20procedures%20of%20charging%20using%20Service%20Based%20Interface%20(SBI)/Rel-17/ts_132290v170700p.pdf)
* [TS 32.291 - 5G system, charging service; Stage 3](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2032.291%20-%205G%20system,%20charging%20service;%20Stage%203/Rel-17/ts_132291v170700p.pdf)

#### NEF (Network Exposure Function) <a name="NEF"></a>
* [TS 29.551 - 5G System; Packet Flow Description Management Service; Stage 3](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.551%20-%205G%20System;%20Packet%20Flow%20Description%20Management%20Service;%20Stage%203/Rel-17/ts_129551v170800p.pdf)

###### APIs
* [Packet Flow Description (PFD) Management](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29551_Nnef_PFDmanagement.yaml)

#### NRF (NF Repository Function) <a name="NRF"></a>
* [TS 29.510 - Network Function Repository Services](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.510%20-%20Network%20Function%20Repository%20Services/Rel-17/ts_129510v171000p.pdf)

#### NWDAF (Network Data Analytics Function) <a name="NDAF"></a>
* [TS 29.520 - Network Data Analytics Services](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.520%20-%20Network%20Data%20Analytics%20Services/Rel-17/ts_129520v171100p.pdf)

#### PCF (Policy Control Function) <a name="PCF"></a>
* [TS 29.244 - Interface between the Control Plane and the User Plane nodes](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.244%20-%20Interface%20between%20the%20Control%20Plane%20and%20the%20User%20Plane%20nodes/Rel-17/ts_129244v170900p.pdf)
* [TS 29.507 - Access and Mobility Policy Control Service](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.507%20-%20Access%20and%20Mobility%20Policy%20Control%20Service/Rel-17/ts_129507v170900p.pdf)
* [TS 29.512 - Session Management Policy Control Service](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.512%20-%20Session%20Management%20Policy%20Control%20Service/Rel-17/ts_129512v171100p.pdf)
* [TS 29.513 - Policy and Charging Control signalling flows and QoS parameter mapping](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.513%20-%20Policy%20and%20Charging%20Control%20signalling%20flows%20and%20QoS%20parameter%20mapping/Rel-17/ts_129513v171100p.pdf)
* [TS 29.514 - Policy Authorization Service](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.514%20-%20Policy%20Authorization%20Service/Rel-17/ts_129514v170900p.pdf)
* [TS 29.523 - Policy Control Event Exposure Service](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.523%20-%20Policy%20Control%20Event%20Exposure%20Service/Rel-17/ts_129523v170800p.pdf)
* [TS 29.525 - UE Policy Control Service](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.525%20-%20UE%20Policy%20Control%20Service/Rel-17/ts_129525v170900p.pdf)
* [TS 29.554 - Background Data Transfer Policy Control Service](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.554%20-%20Background%20Data%20Transfer%20Policy%20Control%20Service/Rel-17/ts_129554v170400p.pdf)
* [TS 29.594 - Spending Limit Control Service](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.594%20-%20Spending%20Limit%20Control%20Service/Rel-17/ts_129594v170500p.pdf)

#### SMF (Session Management Function)<a name="SMF"></a>
* [TS 29.502 - Session Management Services](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.502%20-%20Session%20Management%20Services/Rel-17/ts_129502v170900p.pdf)
* [TS 29.508 - Session Management Event Exposure Service](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.508%20-%20Session%20Management%20Event%20Exposure%20Service/Rel-17/ts_129508v171000p.pdf)
###### APIs
* [PDU Session](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29502_Nsmf_PDUSession.yaml)
* [Event Exposure](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29508_Nsmf_EventExposure.yaml)

#### UDR (Unified Data Repository) <a name="UDR"></a>
* [TS 29.504 - Unified Data Repository Services](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.504%20-%20Unified%20Data%20Repository%20Services/Rel-17/ts_129504v171100p.pdf)
* [TS 29.519 - Usage of the Unified Data Repository service for Policy Data, Application Data and Structured Data for Exposure](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.519%20-%20Usage%20of%20the%20Unified%20Data%20Repository%20service%20for%20Policy%20Data,%20Application%20Data%20and%20Structured%20Data%20for%20Exposure/Rel-17/ts_129519v171000p.pdf)
###### APIs
* Data Repository
  * [Subscription Data](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29505_Subscription_Data.yaml)
  * [Policy Data](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29519_Policy_Data.yaml)
  * [Exposure Data](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29519_Exposure_Data.yaml)
  * [Application Data](https://editor.swagger.io/?url=https://raw.githubusercontent.com/emanuelfreitas/3gpp-documentation/master/apis/TS29519_Application_Data.yaml)

## Policy and Charging Control <a name="PCC"></a>
* [RFC 6733 - Diameter Base Protocol](https://tools.ietf.org/pdf/rfc6733.pdf)
* [RFC 8506 - Diameter Credit-Control Application](https://tools.ietf.org/pdf/rfc8506.pdf)
* [TS 23.167 - IP Multimedia Subsystem (IMS) emergency sessions](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2023.167%20-%20IP%20Multimedia%20Subsystem%20(IMS)%20emergency%20sessions/Rel-17/ts_123167v170200p.pdf)
* [TS 23.179 - Functional architecture and information flows to support mission critical communication services](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2023.179%20-%20LTE%20-%20Functional%20architecture%20and%20information%20flows%20to%20support%20mission%20critical%20communication%20services%20-%20Stage%202/Rel-13/ts_123179v130500p.pdf)
* [TS 23.203 - Policy and charging control architecture](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2023.203%20-%20Policy%20and%20charging%20control%20architecture/Rel-17/ts_123203v170200p.pdf)
* [TS 23.228 - IP Multimedia Subsystem (IMS) - Stage 2](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2023.228%20-%20IP%20Multimedia%20Subsystem%20(IMS)%20-%20Stage%202/Rel-17/ts_123228v170300p.pdf)
* [TS 23.401 - General Packet Radio Service (GPRS) enhancements for Evolved Universal Terrestrial Radio Access Network (E-UTRAN) access](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2023.401%20-%20General%20Packet%20Radio%20Service%20(GPRS)%20enhancements%20for%20Evolved%20Universal%20Terrestrial%20Radio%20Access%20Network%20(E-UTRAN)%20access/Rel-17/ts_123401v170800p.pdf)

* [VoLTE Service Description and Implementation Guidelines](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/GSMA/VoLTE%20Service%20Description%20and%20Implementation%20Guidelines.pdf)

#### OCS (Online Charging System) <a name="OCS"></a>
* [TS 29.219 - Policy and charging control: Spending limit reporting over Sy reference point](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.219%20-%20Policy%20and%20charging%20control%20-%20Spending%20limit%20reporting%20over%20Sy%20reference%20point/Rel-17/ts_129219v170000p.pdf)
* [TS 32.240 - Telecommunication management; Charging management; Charging architecture and principles](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2032.240%20-%20Charging%20architecture%20and%20principles/Rel-17/ts_132240v171000p.pdf)
* [TS 32.251 - Telecommunication management;Charging management;Packet Switched (PS) domain charging](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2032.251%20-%20Telecommunication%20management;Charging%20management;Packet%20Switched%20(PS)%20domain%20charging/Rel-17/ts_132251v170000p.pdf)
* [TS 32.260 - IP Multimedia Subsystem (IMS) charging](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2032.260%20-%20IP%20Multimedia%20Subsystem%20(IMS)%20charging/Rel-17/ts_132260v170500p.pdf)
* [TS 32.270 - Multimedia Messaging Service (MMS) charging](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2032.270%20-%20Multimedia%20Messaging%20Service%20(MMS)%20charging/Rel-17/ts_132270v170000p.pdf)
* [TS 32.274 - Short Message Service (SMS) charging](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2032.274%20-%20Short%20Message%20Service%20(SMS)%20charging/Rel-17/ts_132274v170200p.pdf)
* [TS 32.276 - Voice Call Service (VCS) charging](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2032.276%20-%20Voice%20Call%20Service%20(VCS)%20charging/Rel-17/ts_132276v170000p.pdf)
* [TS 32.296 - Telecommunication management; Charging management; Online Charging System (OCS): Applications and interfaces](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2032.296%20-%20Online%20Charging%20System%20(OCS)%20-%20Applications%20and%20interfaces/Rel-17/ts_132296v170000p.pdf)
* [TS 32.299 - Diameter charging applications](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2032.299%20-%20Diameter%20charging%20applications/Rel-17/ts_132299v170000p.pdf)

| Interface  | Standard |
|------------|----------|
| Sy         | [TS 29.219 - Policy and charging control: Spending limit reporting over Sy reference point](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.219%20-%20Policy%20and%20charging%20control%20-%20Spending%20limit%20reporting%20over%20Sy%20reference%20point/Rel-17/ts_129219v170000p.pdf) |
| Ro - Gy    | [TS 32.251 - Telecommunication management;Charging management;Packet Switched (PS) domain charging](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2032.251%20-%20Telecommunication%20management;Charging%20management;Packet%20Switched%20(PS)%20domain%20charging/Rel-17/ts_132251v170000p.pdf) |
| Ro / Rf    | [TS 32.299 - Diameter charging applications](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2032.299%20-%20Diameter%20charging%20applications/Rel-17/ts_132299v170000p.pdf) |

#### PCRF (Policy and Charging Rule Function) <a name="PCRF"></a>
* [TS 29.211 - Rx Interface and Rx-Gx signalling flows](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.211%20-%20Rx%20Interface%20and%20Rx-Gx%20signalling%20flows/Rel-6/ts_129211v060400p.pdf)
* [TS 29.213 - Policy and charging control signalling flows and Quality of Service (QoS) parameter mapping](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.213%20-%20Policy%20and%20charging%20control%20signalling%20flows%20and%20Quality%20of%20Service%20(QoS)%20parameter%20mapping/Rel-17/ts_129213v170200p.pdf)
* [TS 23.380 - IMS Restoration Procedures](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2023.380%20-%20IMS%20Restoration%20Procedures/Rel-17/ts_123380v170100p.pdf)

| Interface  | Standard |
|------------|----------|
| Gx         | [TS 29.212 - Policy and Charging Control (PCC); Reference points](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.212%20-%20Policy%20and%20Charging%20Control%20(PCC);%20Reference%20points/Rel-17/ts_129212v170300p.pdf) |
| Rx         | [TS 29.214 - Policy and charging control over Rx reference point](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.214%20-%20Policy%20and%20charging%20control%20over%20Rx%20reference%20point/Rel-17/ts_129214v170500p.pdf) |
| Sy         | [TS 29.219 - Policy and charging control: Spending limit reporting over Sy reference point](https://github.com/emanuelfreitas/3gpp-documentation/raw/master/documentation/TS%2029.219%20-%20Policy%20and%20charging%20control%20-%20Spending%20limit%20reporting%20over%20Sy%20reference%20point/Rel-17/ts_129219v170000p.pdf) |

#### NRF Network Repository Function 
Stores the profiles of the other NFs by providing support for NF register, deregister and update service to NF and their services.
The profile includes information like the type of network function, the address in the network, the capacity, services that are provided.
When a service consumer wants to finde a service provider, it communicates with the NRF, to find the address in which find the service provider,
for example, when the AMF, wants to find the SMF it checks with the NRF to find what is the address of the SMF, how many instances of SMF are running now,
what is the capacity ...
With the NRF the service consumer can discover and select suitable service providers without having to be configured before hand.

#### AMF Authentication and Mobility Function
To register and authentificate UEs, to support mobility between different radio cells.
Also relays, all session management related signal messages, between the devices and the SMF network function.
The AMF interact with the gNodeB with the N2 interface, and with UE with N1 interface, all the rest interaction with network functions
are done via service based interfaces.

#### SMF Session Management Functionality
SMF manages the user session, it is responsible for accepting the connection from the UE towards the data network.
It is the control function that manages the user sessions, that includes, the stablishment, modification and release of session. And allocation of
IP addresses for PDU UPF sessions. SMF also selects and controls the different network functions in the network over the N4 interface.
It also interacts with the PCF to retrieve the policies to configure the UPF accordingly. It is also responsible for collecting charging data
 and controls the charging functionality in the UPF.

#### AUSF Authentication Server Function
The AUSF is in the subscribers home network. It is responsible for handling the authentication in the home network
based on the information received from the UE, on one side, and information retrieved from the UDM on the other side.

#### PCF: Policy control function
The PCF provides policy control function in different areas. 
 - First, it provides session managements related policies to SMF like quality of service policies.
 - It works with AMF for access and mobility related policies like radio frequency, selection priority or service area restrictions, etc.
 - It also works with the UE via AMF for policy related to how the UE should work with non-3gpp networks, like wi-fi or for network slice selection, etc.

#### UDR and UDM - The User Data Repository (UDR) and User Data Management (UDM)
The UDR, is the database that stores the subscription data, and the data that defines different types of network. The UDM is a front-end for the subscription data, stored in the UDR. The UDM uses the subscription data stored in the UDR to carry functions like generating authentification credentials, and to do registration management when the UE tries to
register with the network.

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
| :---    | :---  |  :---: | :---:  | :---: | :---:  | :---: | :---: | :---  |
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


AMF is responsible for movility management. https://www.sharetechnote.com/html/5G/5G_Core_AMF.html

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

 - reference: https://moniem-tech.com/questions/what-is-service-communication-proxy-scp-in-5g/
 - reference: https://www.etsi.org/deliver/etsi_ts/129500_129599/129510/17.06.00_60/ts_129510v170600p.pdf

## Access and Mobility function: AMF

references: 
 - https://www.sharetechnote.com/html/5G/5G_Core_AMF.html
 - https://portal.3gpp.org/desktopmodules/Specifications/SpecificationDetails.aspx?specificationId=3445
 - https://emblasoft.com/blog/exploring-the-3gpp-amf-access-mobility-management-function#:~:text=In%205G%2C%20AMF%20terminates%20the,i.e.%2C%20access%20subscribed%20services).
 - https://www.techtrained.com/network-function-access-mobility-management-function-amf-in-5g-core-network-5g-system-5gs/
 - https://mobilepacketcore.com/5g-network-architecture/
 - https://www.youtube.com/watch?v=eFn1REiUisk
 - https://www.youtube.com/watch?v=Q6YxHz_07zk&t=4s

AMF interacts with NG-RAN over the N2 interface.

AMF interacts with the UE (user equipment) over N1 interface for authentication, registration and handovers. Also responsible for paging of idle mode UEs.

AMF interacts with SMF (Session Management Function) with the N11 interface

One UE is connected to one AMF at a time. 

AMF relays all session management-reltaed signals between the SMF (session management function) and UE. 

Relays all SMS messages between UE and SMSF (SMS function)

Relay for Location service messages between UE and LMF (Location Management Function)

Unlike 4G UEs in 5G have specific interface between UE and AMF, known as N1. 

Relay for messages between UE and PCF (Policy Control Function).

Includes security functionality for authentication, authorization of UE (in cooperation with AUSF (Authentication User Server Function) and UDM (Unified Data Management)).

Responsible for deriving keys for integrity and ciphering - RRC and User plane.

In many ways is similar to the 4G MME (Mobility Management Entity).

AMF Interfaces with MME in 4G for context transfer when interworking with EPC is deployed, by means of the interface N26. 

### AMF registration management states

References:
- https://www.sharetechnote.com/html/5G/5G_Core_AMF.html
- https://www.tech-invite.com/3m23/toc/tinv-3gpp-23-501_t.html
- https://portal.3gpp.org/desktopmodules/Specifications/SpecificationDetails.aspx?specificationId=3144

The Registration Management is used to register or deregister a UE/user with the network, and establish the user context in the network. The Connection Management is used to establish and release the signalling connection between the UE and the AMF.

A UE/user needs to register with the network to receive services that requires registration. Once registered and if applicable the UE updates its registration with the network (see TS 23.502):
periodically, in order to remain reachable (Periodic Registration Update); or
upon mobility (Mobility Registration Update); or
to update its capabilities or re-negotiate protocol parameters (Mobility Registration Update).
The Initial Registration procedure involves execution of Network Access Control functions as defined in clause 5.2 (i.e. user authentication and access authorization based on subscription profiles in UDM). As result of the Registration procedure, the identifier of the serving AMF serving the UE in the access through which the UE has registered will be registered in UDM.
The registration management procedures are applicable over both 3GPP access and Non-3GPP access. The 3GPP and Non-3GPP RM states are independent of each other, see clause 5.3.2.4.

TAU - Tracking Area Update ; TAI - Tracking Area see TS 37.340

Two RM states are used in the UE and the AMF that reflect the registration status of the UE in the selected PLMN:
RM-DEREGISTERED.
RM-REGISTERED.

#### RM-DEREGISTERED state  

In the RM-DEREGISTERED state, the UE is not registered with the network. The UE context in AMF holds no valid location or routing information for the UE so the UE is not reachable by the AMF. However, some parts of UE context may still be stored in the UE and the AMF e.g. to avoid running an authentication procedure during every Registration procedure.

In the RM-DEREGISTERED state, the UE shall:

- attempt to register with the selected PLMN using the Initial Registration procedure if it needs to receive service that requires registration (see clause 4.2.2.2 of TS 23.502).
- remain in RM-DEREGISTERED state if receiving a Registration Reject upon Initial Registration (see clause 4.2.2.2 of TS 23.502).
- enter RM-REGISTERED state upon receiving a Registration Accept (see clause 4.2.2.2 of TS 23.502).
- 
When the UE RM state in the AMF is RM-DEREGISTERED, the AMF shall:

 - when applicable, accept the Initial Registration of a UE by sending a Registration Accept to this UE and enter RM-REGISTERED state for the UE (see clause 4.2.2.2 of TS 23.502); or
 - when applicable, reject the Initial Registration of a UE by sending a Registration Reject to this UE (see clause 4.2.2.2 of TS 23.502).

#### RM-REGISTERED state 

In the RM-REGISTERED state, the UE is registered with the network. In the RM-REGISTERED state, the UE can receive services that require registration with the network.

In the RM-REGISTERED state, the UE shall:
perform Mobility Registration Update procedure if the current TAI of the serving cell (see TS 37.340) is not in the list of TAIs that the UE has received from the network in order to maintain the registration and enable the AMF to page the UE;

NOTE:
Additional considerations for Mobility Registration Update in case of NR satellite access are provided in clause 5.4.11.6.

perform Periodic Registration Update procedure triggered by expiration of the periodic update timer to notify the network that the UE is still active.

perform a Mobility Registration Update procedure to update its capability information or to re-negotiate protocol parameters with the network;

perform Deregistration procedure (see clause 4.2.2.3.1 of TS 23.502), and enter RM-DEREGISTERED state, when the UE needs to be no longer registered with the PLMN. The UE may decide to deregister from the network at any time.

Enter RM-DEREGISTERED state when receiving a Registration Reject message or a Deregistration message. The actions of the UE depend upon the 'cause value' in the Registration Reject or Deregistration message. See clause 4.2.2 of TS 23.502.

When the UE RM state in the AMF is RM-REGISTERED, the AMF shall:

 - perform Deregistration procedure (see clause 4.2.2.3.2 of TS 23.502, clause 4.2.2.3.3 of TS 23.502), and enter RM-DEREGISTERED state for the UE, when the UE needs to be no longer registered with the PLMN. The network may decide to deregister the UE at any time;
 - perform Implicit Deregistration at any time after the Implicit Deregistration timer expires. The AMF shall enter RM-DEREGISTERED state for the UE after Implicit Deregistration;
when applicable, accept or reject Registration Requests or Service Requests from the UE.


```
┌──────────────────────┐                                ┌────────────────────┐
│                      │     REGISTRATION ACCEPTED      │                    │
│    RM-DEREGISTERED   ├───────────────────────────────►│   RM-REGISTERED    │
│                      │                                │                    │
│                      │◄────────────────────────────── │                    │
└─────┬────────────────┘        DEREGISTRATION          └────┬───────────────┘
      │           ▲                                          │           ▲
      │           │          REGISTRATION REJECTED           │           │
      │           │                                          │           │
      │           │                                          │           │
      │           │                                          │           │
      │           │                                          │           │
      └──────────►┘                                          └───────────►

     REGISTRATION REJECTED                             REGISTRATION UPDATE ACCEPT

#made with https://asciiflow.com/#/
```


## 5G private Networks - (NPN: Non-Public-Networks)

References
 - Non-Public Networks (NPN): https://www.3gpp.org/technologies/npn
 - https://www.techtarget.com/searchnetworking/tip/Private-5G-in-a-box-simplifies-deployment-mobility
 - What is Private 5G? Private 5G vs. Wi-Fi: https://youtu.be/UCLtahIJfYY
 - Private 5G Networks - Mpirical: https://youtu.be/gdi4eJfTP2w
 - Advanced: Private Networks & 5G Non-Public Networks: https://youtu.be/rF3yyjfx1YA

### NPN Non-public-networks deployment models

Private Networks (NPN)
 - Standalone Non-public Networks (SNPN)
 - Public Networks integrated Non-public Networks (PNI-NPN)
     - Share RAN
     - Share RAN & control-plane
     - Hosted by public network
  
#### Standalone Non-public Networks (SNPN)
This is an isolated and independent system, it has no dependences on public network. 

It operates, like a regular 5G network. NPN services require subscription. 

The SNPN needs and ID, the SNPN ID, and is a combination of: 
 - the Public Land Mobile Networkd (PLMN) ID (based on MCC (mobile country code) asigned by ITU), 
 - Network ID, which can be self assigned or by national regulator.

#### How to build private 5G network

 - https://www.theregister.com/2023/04/25/building_private_5g/
 - https://open5gs.org/
 - https://free5gc.org/

 - https://youtu.be/itkJdKgkyFk
 - https://youtu.be/BAf-LG103ZQ
 - https://youtu.be/NxFOqR_41Bs

 - https://www.youtube.com/watch?v=Nx8G3ln0NX0
 - https://github.com/Amin-Sedighfar/Open5GS-OAI



## NGAP - Next Generation Aplication Protocol

 - reference: https://techlteworld.com/ngap-ng-application-protocol-in-5g-nr/
 - reference: Tutorial on communication between access networks and the 5G core: https://arxiv.org/pdf/2112.04257
 - reference: specs: https://www.etsi.org/deliver/etsi_ts/138400_138499/138413/16.07.00_60/ts_138413v160700p.pdf

![NGAP specs](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/5g_NGAP_spec.PNG)


NGAP, the Next Generation Application Protocol, serves as the essential language for communication between the core network and radio access network (RAN) in 5G. It’s the protocol designed specifically for 5G and beyond, enabling efficient and secure messaging between the heart of the network (core) and the frontline troops (radio access).

![NGAP stack](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/5g-NGAP.PNG)

 The NGAP architecture is built on the N2 interface, which connects the gNB (RAN) and the AMF (core network). This interface facilitates the exchange of control plane signaling messages. The NGAP architecture consists of the following layers:

 - **Application layer**: This layer contains the NGAP protocol entities, which are responsible for generating and processing NGAP messages.
 - **Transport layer**: This layer is responsible for the reliable delivery of NGAP messages between the gNB and the AMF. It typically uses the SCTP (Stream Control Transmission Protocol) protocol.
 - **Security layer**: This layer is responsible for providing security services for NGAP messages, such as authentication, integrity protection, and confidentiality. It typically uses the TLS (Transport Layer Security) protocol.

The NGAP architecture also includes the following entities:

 - **gNB** This is the base station in the 5G network. It is responsible for providing radio access to UEs (User Equipment).
 - **AMF** (Access and Mobility Management Function): This is a core network entity that is responsible for managing the mobility of UEs and providing access to network services. (https://techlteworld.com/amf-access-management-function-in-5g-nr/)
 - **UPF** (User Plane Function): This is a core network entity that is responsible for forwarding user plane data between the gNB and the core network.NGAP ensures smooth boarding, seamless handovers between stations (cells), and efficient resource allocation, all while keeping everything secure (https://techlteworld.com/upf-user-plane-function-in-5g-nr/).

### How NGAP works?

NGAP operates on a dedicated line, the N2 interface, connecting the radio access (gNB) and the core network (AMF). Imagine this as a dedicated communication channel for important updates and instructions. Through a series of procedures and messages, NGAP manages everything from user authentication to mobility and service activation.

![NGAP N2](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/5g_NGAP_n2.PNG)

### NGAP Features and Functionalities

Let’s explore its key features and functionalities:

#### NAS Signaling:
Imagine it as the network’s passport control. NGAP facilitates NAS (Non-Access Stratum) signaling, responsible for user authentication, mobility management, and bearer services management. This ensures secure access and seamless service experience across different radio access technologies.

#### Control Plane Separation:
Think of it as dedicated lanes for traffic. NGAP maintains a clear separation between the control plane (signaling) and the user plane (data). This allows for efficient resource management and scalability, handling information flow without data traffic interference.

#### Security Mechanisms:
Like robust encryption in online banking. NGAP incorporates robust security measures like mutual authentication and integrity protection. This safeguards against cyber threats and ensures secure communication, protecting network integrity and user data.

#### Flexibility and Extensibility:
Think of it as a future-proof design. NGAP is designed to be flexible and adapt to emerging needs. Its modular architecture allows for easy integration of future enhancements and new services, paving the way for B5G evolution and unforeseen advancements.

#### User Equipment (UE) Management:
This is like managing passengers on a high-speed train. NGAP establishes and manages UE contexts, handling user authentication, registration, and mobility procedures. It ensures smooth onboarding, seamless handovers, and continuous connectivity as users move across the network.

#### Radio Resource Management:
Think of it as allocating seats efficiently. NGAP assists in allocating and managing radio resources for UEs, optimizing network performance and ensuring fair and optimal resource utilization for each connected device.

#### Service Management:
Imagine ordering different meals on a flight. NGAP enables the establishment and management of diverse services for UEs, facilitating data, voice, video, IoT connectivity, and even cutting-edge applications like AR/VR seamlessly.

#### Mobility Management:
Think of it as ensuring smooth transitions between stations. NGAP facilitates seamless handover between different RATs (radio access technologies) and gNBs (base stations), guaranteeing uninterrupted connectivity for users on the move, ensuring no dropped calls or service disruptions.



## 5G NG Aplication Protocol (NGAP) Setup Procedure

 - reference: 38.413 v16.7.0: Section 8.7.1: https://www.etsi.org/deliver/etsi_ts/138400_138499/138413/16.07.00_60/ts_138413v160700p.pdf

NG Setup Procedure is the first NGAP procedure triggered to exchange application-level data for the NG-RAN node and AMF to interoperate on the NG-C interface.

The NG Setup procedure, is a low level procedure bewteen the AMF and gNodeB. 

It has two messenges: 
 - NG setup request
 - NG setup response

The procedure is used to exchange aplication level data which is needed for the gNodeB and AMF to interoperate. 

This process uses non-UE associeted signaling. 

 ![ 5G NG Aplication Protocol (NGAP) Setup Procedure](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/5G-NG-setup_process_TS_138_413_v16.7.0_NG_Aplication_Protocol.PNG)

## Initial registration procedure

 - reference: 23.502 v16.7.1 Section 4.2.2.2: https://www.etsi.org/deliver/etsi_ts/123500_123599/123502/16.07.00_60/ts_123502v160700p.pdf

![Initial registration procedure](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/5g_registration_procedures_TS_123_502_V16.7.1-registration-procedures.PNG)

There are 4 types of registration:
 - Initial registration: Initiatied by the UE, 5GS Registration Type = 1.
 - Movility registration Update: when the UE moves to a new registration area, 5GS Registration Type = 2.
 - Periodic registration update: when the UE wants to inform the network that it is still there. 5GS Registration type = 3.
 - Emergency registration: when the UE is in a limited service state. 5GS Registration type = 4.

### high level sequence fro Initial registration

 - The UE initiates a random access procedure to initate communication with the gNodeB.
 - The UE creates the RRC connection with the gNodeB and sends registration request with the 5GC.
 - 5GC selects the appropiate authentification procedure based on subscriber and starts the authentification procedure.
 - NAS level authentification and initiate ciphering for the NAS message with the 5G core.
 - The 5GC retrieves the subscription data and performs the policy association procedure.
 - The 5GC updates the SM context and informs UE to start up the PDU sessions establishment procedure via the Inital Context Setup Request.

![initial registration request](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/5g_initial_registration_request.PNG)

![Notes_on_protocols/Images_mobile_communication/Initial_registration_without_AMF_handover.PNG](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/Initial_registration_without_AMF_handover.PNG)

![Notes_on_protocols/Images_mobile_communication/Initial_registration_without_AMF_handover_2.PNG](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/Initial_registration_without_AMF_handover_2.PNG)

![general registration request](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/5G-general_registrartion-request.PNG)


## Initial UE message and registration request message

  - reference: NG Aplication Protocol (NGAP) 38.413. V16.7.0. Section 8.6.1: https://www.etsi.org/deliver/etsi_ts/138400_138499/138413/16.07.00_60/ts_138413v160700p.pdf

![initial UE messsage](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/5g-initial-UE-message.PNG)

The Non Access Stratum (NAS) is a functional layer running between the User Equipment (UE) and the Core Network (CN). The layer supports traffic and signalling messages between the CN and UE. 
(reference: https://www.dialogic.com/glossary/nas#:~:text=The%20Non%20Access%20Stratum%20(NAS,between%20the%20CN%20and%20UE.)

NAS and MM are two protocols that operate at the upper layer of the 5G system architecture, above the access stratum (AS) that deals with the radio interface. NAS is responsible for establishing, maintaining, and releasing sessions between the user equipment (UE) and the core network (CN) (reference: https://www.linkedin.com/advice/1/how-do-you-design-test-nas-mm-protocols-5g-networks-skills-3gpp)


Initial UE Message and Registration Request Message are the first two messages exchanged between UE and AMF to establish a new connection.

The Initial UE Message is the first communication from user equipment (UE) to the network, while the Registration Request Message is a specific UE message used to request registration with the network.

Before we proceed to proceed to the contents of the initial message, we must know that the initial message is basically a transport layer type message.

There are three types of mass transport layer messages:
 - First is the uplink transport.
 - second is the initial message
 - third is the downlink mass transport.

The purpose of the transport layer messages are that they are used to carry the NAS messages along with

them over the protocol direction of the initial messages.

Uplink meaning starting from the Ram node or the G node B towards the AMF.

![NAS transport messages](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/5g-NAS-transport-messages.PNG)











