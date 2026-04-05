
# Notes onf free5G

References:
 - https://training.linuxfoundation.org/training/introduction-to-free5gc-lfs114/
 - https://free5gc.org/
 - https://github.com/free5gc/free5gc

## Overview

free5GC is an open source implementation of the 5G Core, aligned with 3GPP Release 15 and designed as a learning and research platform for modern 5G networks. It provides a clear, modular view of how core network functions work together and how service-based architecture is applied in practice.

This will introduce the foundations of free5GC: its overall architecture, the roles of key network functions such as AMF, SMF, and UPF, and the development patterns used throughout the project. You’ll learn how the system is structured, how components interact, and how to navigate the codebase with confidence.

We’ll walk through core concepts, examine how free5GC implements 5G control and user plane behavior, and explore the tools and patterns developers use to run, debug, and extend the system. You’ll develop both conceptual understanding and practical insight, preparing you to build deeper 5G Core skills and begin contributing when you’re ready.

## Foundations of free5G

### What is free5G?

free5GC is an open source project that develops and maintains an implementation of the 5G Core Network (5GC). The project was developed by a team led by Professor Jyh-Cheng Chen at Taiwan's National Chiao Tung University (now National Yang Ming Chiao Tung University).
Image of free5GC logo

Its primary goal is to provide a functional and standards-compliant 5GC that can be used by researchers, students, and developers for academic research, prototyping, and testing of 5G technologies and applications.

To understand what free5GC actually does, it helps to know what the 5G Core is responsible for. At the highest level, the core has two big jobs:
 1- Control Plane → makes the decisions and sets the rules.
 2 - Data Plane → carries the user’s traffic through the network.

free5GC implements both planes according to 3GPP standards, providing a reliable foundation for experimentation and innovation.

Beyond these core functions, several characteristics make free5GC especially valuable to the research and development community.

#### Written in Go

free5GC is developed in the Go programming language. Go was chosen because it handles concurrency and networking efficiently, which are critical for simulating how different parts of the 5G Core interact.


#### Reference implementation

The project closely follows 3GPP standards, serving as a reference implementation. This means its functions align with real-world 5G Core deployments, allowing researchers and developers to test ideas with confidence.

#### Project goal

free5GC was created to make a working, standards-compliant 5G Core available to the community. It lowers barriers for researchers, educators, and innovators to learn, experiment, and build prototypes without relying on proprietary systems.

## free5G architecture: control and data plane

## Introduction to control and data plane

In any mobile network, the workload is divided into two key domains: the Control Plane and the Data Plane.

To understand the difference, picture a railway system.

The Control Plane is like the railway's signaling and management system. It includes the dispatchers, the track switches, the schedule, and the ticketing system. It decides which train goes on which track, verifies passengers, and ensures the whole system runs smoothly and safely.

The Data Plane is the train itself. Its sole job is to transport passengers (your data) from one station to another as quickly and efficiently as possible, following the route determined by the Control Plane.
Split image comparing the Control Plane and Data Plane: the left side shows a train control cockpit labeled ‘Control Plane,’ and the right side shows a train on railway tracks labeled ‘Data Plane.’

This division of responsibilities is known as Control and User Plane Separation (CUPS). It’s a core principle of 5G architecture that allows for greater flexibility and efficiency.

💡 CUPS in Action: Separating control and data allows operators to scale each plane independently, optimize performance, and evolve parts of the network without disrupting service.


## The control plane

The Control Plane is the brain of the network. While it doesn't handle any of your actual internet traffic (like video streams or web pages), it’s responsible for all the decisions required for that traffic to flow correctly.

The Control Plane coordinates all the signaling processes that enable connectivity. It ensures user devices are authenticated, registered, and continuously managed as they move across the network.

To perform these functions, the Control Plane handles several critical responsibilities within the 5G Core.

#### Connection and mobility management 

When you turn on your phone, the Control Plane handles your device's request to join the network (Registration). It verifies your identity using your SIM information (Authentication) and tracks your location as you move between different cell towers, ensuring your connection is seamlessly handed over without dropping (Mobility Management).

#### Session management

When you open an app that needs internet access, the Control Plane establishes a data pathway for you. This is called a **PDU (Protocol Data Unit)** Session. This process involves assigning an IP address to your device and setting up the virtual "tunnels" through which your data will travel across the Data Plane. It's also responsible for tearing down these sessions when they're no longer needed.

#### Policy and QoS (Quality of Service) configuration 

The Control Plane is the rule-maker. Based on your subscription plan, current network conditions, and the type of application you're using, it defines the rules for your data session.

This includes:
 - Setting your maximum download and upload speeds
 - Prioritizing latency-sensitive traffic (for example, voice calls over file downloads)
 - Communicating Quality of Service (QoS) rules to the Data Plane for enforcement

Together, these responsibilities make the Control Plane the central coordinator of the 5G Core, ensuring that all other network functions operate in sync.    

While the Control Plane decides how data should flow, the Data Plane executes those decisions by forwarding packets efficiently and enforcing the policies defined by the Control Plane.

## The data plane

The Data Plane's job is straightforward but essential: it forwards your data packets between your device and the internet as fast as possible, strictly following the rules defined by the Control Plane.

It doesn’t decide how traffic should move; instead, it focuses on executing the Control Plane’s instructions with speed, precision, and reliability.

To achieve this, the Data Plane applies the policies and forwarding paths defined by the Control Plane, ensuring each data session runs smoothly and efficiently.

#### Packet routing and fowarding

The Data Plane takes data packets from your device, encapsulates them, and forwards them through the core network towards their final destination on the internet.

#### QoS and Policy enforcement

While the Control Plane decides the rules, the Data Plane enforces them. It inspects data packets and applies the assigned QoS policies for:
 - Traffic shaping: buffering packets to control the data rate
 - Prioritization: letting real-time video packets go ahead of email
 - Blocking: filtering traffic that violates policy.

#### Usage reporting

The Data Plane tracks the volume of data that passes through it. It then reports this information back to the Control Plane, which uses it for billing and charging purposes.

Together, these responsibilities make the Data Plane the execution layer of the 5G Core, turning the Control Plane’s instructions into real network action.


## Control Plane network functions 

The Control Plane and Data Plane are brought to life by specific Network Functions (NFs). Think of them as the specialized building blocks of the 5G Core. Each NF has a focused role, from authenticating users to enforcing policies to forwarding traffic.

In 5G’s Service-Based Architecture (SBA), these functions are modular, discoverable, and communicate with each other through APIs. This design makes the 5G Core flexible, scalable, and easier to evolve as standards and technologies change.

These NFs manage network access, security, mobility, policies, and charging. They don’t carry traffic directly, but they make sure everything flows properly.

Together, the Control Plane NFs form the decision-making system of the 5G Core. They authenticate users, manage sessions, enforce policies, and coordinate resources. Without them, the Data Plane would have no instructions to follow.

### Access and Mobility Management Function (AMF)

Main role: Manages UE registration, mobility, and access-related tasks.

Key Responsibilities:
 - Registers the UE to the network and manages its mobility status.
 - Performs NAS message encryption and integrity protection.
 - Acts as a proxy to forward session-related messages from the UE to the SMF.
 - Handles authentication and authorization in coordination with AUSF.
 - Interacts with NSSF to select appropriate slices for UE.

### Authentication Server Function (AUSF)

Main role: Acts as the network's security guard, responsible for verifying the identity of users before they are allowed to connect.

Key Responsibilities
 - Handles the primary authentication process for any device connecting to the 5G core.
 - Supports multiple authentication methods, making it compatible with both standard cellular (3GPP) and other network types like Wi-Fi (non-3GPP).
 - Generates the necessary security keys during 5G-AKA and EAP-AKA' procedures to ensure the connection is secure.

### Network Repository Function (NRF)

Main role: Serves as the central directory or "phone book" for all other Network Functions.

Key Responsibilities:
 - Maintains a dynamic, up-to-date list of all available NF instances and the services they offer.
 - Enables service discovery, allowing NFs to find and communicate with each other.
 - Monitors the health status and availability of registered NFs.

### Network Slice Selection Function (NSSF)

Main role: Functions as a traffic director for network slicing, ensuring the user is connected to the correct virtual network slice for their needs.

Key Responsibilities:
 - Selects the appropriate Network Slice Instance to serve a user based on their subscription and requested service.
 - Validates the user's requested slice information (NSSAI - Network Slice Selection Assistance Information) against their subscription profile.
 - Determines which AMF set is best suited to manage the user's session within the selected slice.

### Policy Control Functio (PCF)    

Main role: Acts as the rule-maker for the network, defining and providing policies that govern how data sessions are handled.

Key Responsibilities:
 - Retrieves subscriber policy information from the UDR to understand a user's service level and restrictions.
 - Provides the SMF with Session Management (SM) policies that dictate rules for data sessions, like QoS.
 - Provides the AMF with Access and Mobility (AM) policies that influence how a user connects to and moves within the network.
 - Creates UE Route Selection Policy (URSP) rules to guide a device's traffic across different network slices or connections.

### Charging Function (CHF)

Main role: Manages all aspects of data charging and billing.

Key Responsibilities:
 - Supports both online and offline charging models.
 - Calculates data usage and applies the correct charging mechanisms based on the user's plan and network policies.
 - Generates Charging Data Record (CDR) files.

### Session Management Function (SMF)

Main role: Manages the entire lifecycle of a user's data connection, from initiation to termination.

Key Responsibilities:
 - Handles session lifecycle operations such as establishment, modification, and release.
 - Manages UE IP address allocation, which may come from a UPF or an external data network.
 - Instructs UPF and NG-RAN to perform redundant transmission over N3/N9 interfaces.
 - Determines the PDU session data path based on the SM Policy provided by PCF.

### Unified Data Management (UDM)

Main role: Acts as a centralized manager for user identity, subscription, and authentication data.

Key Responsibilities:
 - Manages SUPI(Subscription Permanent Identifier) and GPSI(Generic Public Subscription Identifier).
 - Manages authentication credentials for 3GPP AKA.
 - Manages user subscription information.

### Unified Data Respository (UDR)

Main role: Functions as the network's centralized database, securely storing information used by other NFs.

Key Responsibilities:
 - Stores and retrieves subscriber data for UDM.
 - Stores and retrieves policy data for PCF.
 - Stores structured data for exposure, application data, and AF request information for NEF.

### Network Exposure Function (NEF)

Main role: Provides a secure and controlled gateway for external applications to access the capabilities of the 5G network.


## Data plane network functions


While the Control Plane defines how traffic should flow, the Data Plane executes those instructions through its own set of specialized Network Functions (NFs). These NFs carry and process user data, enforce the rules defined by the Control Plane, and ensure packets reach their destinations efficiently.

Some of these NFs allow users to connect to the 5G core through Non-3GPP access networks. These are networks not defined by the 3GPP standards, with the most common example being Wi-Fi. These functions act as secure gateways, handling the translation and security needed to seamlessly integrate these external access methods into the 5G ecosystem.

The Data Plane NFs act as the execution layer of the 5G Core. They handle the actual movement of data packets, apply QoS policies, and generate usage reports. Their efficiency directly impacts the speed and reliability of the end-user experience.


### User Plane Function (UPF)

Main role: Acts as the network's data highway, responsible for forwarding all user traffic to and from the internet.

Key Responsibilities:
 - Serves as the external PDU session connection point to data networks.
 - Handles packet routing and forwarding.
 - Enforces user-plane policy rules such as traffic steering.
 - Generates traffic usage reports.

### Non-3GPP InterNetworking Function (N3IWF)

Main role: Enables devices to connect securely to the 5G core over untrusted non-3GPP networks, like public Wi-Fi.

Key Responsibilities:
 - Establishes a secure IPsec tunnel with the device to protect all communication over the untrusted network.
 - Processes NAS and NGAP messages
 - Encapsulates and decapsulates packets for IPsec and N3 tunneling

### Trusted Non-3GPP Gateway Function (TNGF)

Main role: Enables devices to connect to the 5G core over trusted non-3GPP networks, such as a secure corporate Wi-Fi network.

Key Responsibilities:
 - Handles NGAP messages for supporting PDU sessions and QoS
 - Relays NAS messages transparently between UE and AMF
 - Relays PDU data units transparently between the UE and UPF(s)

## Communication Interfaces overview

Modern 5G networks consist of modular Network Functions (NFs), and these need to communicate efficiently. This is achieved through two primary models:
 - Service-Based Architecture (SBA): Used for Control Plane NFs, where functions interact through APIs.
 - Reference Point Interfaces: Used where strict protocol stacks are required, especially in the Data Plane and at the network edge

Together, these models ensure signaling, control, and data forwarding happen reliably across the 5G Core.

5G System Architecture

Every NF requires an interface to communicate with others. The following diagram shows the architecture of the 5G system. Most NFs use the Service-Based Interface (SBI), while a small set of reference point interfaces (N1, N2, N3, N4, N6, and N9) handle specific signaling and data traffic.

The 5G Core’s architecture is designed around flexibility and modularity. Each Network Function communicates through well-defined interfaces that ensure signaling, control, and user data flow seamlessly between the Control and Data Planes. This structure allows the network to evolve as new services and technologies are introduced.

![communication interfaces](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/free5g_arch_communication_interfaces.jpg)

## Key reference point interfaces

Let’s look more closely at how these interfaces support communication between the Control Plane, Data Plane, and external networks.

Each interface plays a specific role in managing signaling, user traffic, or control information. Together, they make it possible for data to move reliably between user devices, network functions, and the internet.

Together, these interfaces ensure that both signaling and user traffic move reliably across the 5G Core, forming the backbone of communication between the Control Plane, Data Plane, and external networks.


### N2 

The N2 interface is the signaling bridge that connects the Radio Access Network (RAN) to the core network's AMF. Its exclusive purpose is to carry command-and-control messages that manage a user's entire connection lifecycle.

As the diagram shows, this communication is structured by the N2 protocol stack. The application layer uses NGAP (Next Generation Application Protocol). NGAP runs on top of SCTP (Stream Control Transmission Protocol), a transport protocol chosen for its high reliability in handling telecom signaling. This layered approach ensures that the radio layer and the core network are always in sync, making the N2 the fundamental control channel for user access and mobility operations.

![n2 interface](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/free5g_n2_interface.png)

### N1

The N1 interface is the logical channel between the User Equipment (UE) and the AMF. Think of it as the UE's private, secure line for sending signaling messages to the 5G core network.

As the diagram illustrates, N1 is not a direct physical connection. Instead, messages are "tunneled" through the RAN. The UE sends its control messages, encapsulated within the NAS (Non-Access Stratum) protocol, to the RAN. The RAN then forwards these messages transparently over N2 to the AMF.

![n1 interface](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/free5g_n1_interface.jpg)

### N4 

The N4 interface links the SMF and the UPF. This interface is central to CUPS, allowing the SMF to make decisions, while the UPF focuses on executing those decisions.

As the diagram shows, all communication over the N4 interface is managed by the PFCP (Packet Forwarding Control Protocol). The SMF uses PFCP to install, modify, and remove rules on the UPF for each data session.

![n4 interface](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/free5g_n4_interface.png)

### N3

The N3 interface is the primary data tunnel for all user traffic, carrying it from the RAN to the UPF. Unlike the N2 interface, which handles signaling, the N3 is purely a Data Plane Interface. Its sole responsibility is to transport the actual data packets, such as video streams, web pages, and application data, from the cell tower into the 5G Core.

As the diagram illustrates, this is achieved by creating a secure tunnel using the GTP-U (GPRS Tunneling Protocol for the User Plane). The GTP-U protocol encapsulates the user's original data packets and adds a special header. This header contains a Tunnel Endpoint Identifier (TEID), which acts like a unique label for each data session. The TEID allows the UPF to instantly recognize which user's traffic it is handling, so it can apply the correct forwarding rules and policies for thousands of different sessions at once.

![n3 interface](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/free5g_n3_interface.jpg)

### N6 

The N6 interface is the Data Plane gateway between the 5G Core and an external Data Network (DN), such as the public internet. It is the final exit point for all user traffic.

N6 connects to a specific type of UPF known as the PDU Session Anchor (PSA). The GTP-U tunnel that carries user data across the 5G Core (over the N3 and N9 interfaces) terminates at this anchor UPF. The UPF then decapsulates the traffic and sends the user's raw IP packets out over the N6 interface. Often, a NAT (Network Address Translation) gateway is used here to translate the private IP addresses into public ones.

### N9

The N9 interface is a data plane link that connects two User Plane Functions (UPFs) within the 5G core.

A common use case is connecting an Intermediate UPF (I-UPF), located closer to the user for low-latency access, to a centralized PSA-UPF. Just like the N3 interface, N9 uses the GTP-U protocol to tunnel user data between the two UPFs.



