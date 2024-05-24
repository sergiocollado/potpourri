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
 | : -- : |  : -- : |  : -- : |  : -- : |  : -- : |  : -- : | 
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


AMF is responsible for movility management. 

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

- reference: https://www.tech-invite.com/3m23/toc/tinv-3gpp-23-501_t.html
- reference: https://portal.3gpp.org/desktopmodules/Specifications/SpecificationDetails.aspx?specificationId=3144

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

 - reference: Non-Public Networks (NPN): https://www.3gpp.org/technologies/npn
 - reference: https://www.techtarget.com/searchnetworking/tip/Private-5G-in-a-box-simplifies-deployment-mobility
 - reference: What is Private 5G? Private 5G vs. Wi-Fi: https://youtu.be/UCLtahIJfYY
 - reference: Private 5G Networks - Mpirical: https://youtu.be/gdi4eJfTP2w
 - reference: Advanced: Private Networks & 5G Non-Public Networks: https://youtu.be/rF3yyjfx1YA

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

![general registration request](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/5G-general_registrartion-request.PNG)


## Initial UE message and registration request message

  - reference: NG Aplication Protocol (NGAP) 38.413. V16.7.0. Section 8.6.1: https://www.etsi.org/deliver/etsi_ts/138400_138499/138413/16.07.00_60/ts_138413v160700p.pdf

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

![initial UE messsage](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/5g-initial-UE-message.PNG)










