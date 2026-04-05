
# Notes onf free5G

Notes from: https://training.linuxfoundation.org/training/introduction-to-free5gc-lfs114/

References:
 - https://training.linuxfoundation.org/training/introduction-to-free5gc-lfs114/
 - https://free5gc.org/
 - https://github.com/free5gc/free5gc
 - https://github.com/aligungr/UERANSIM
 - https://github.com/free5gc/free5GLabs
 - https://github.com/free5gc/free5gc/wiki
 - https://github.com/free5gc/gtp5g

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

## Service-Based architecture SBA

The Service-Based Architecture (SBA) framework allows all NFs, except for the UPF, to communicate with each other through the Service-Based Interface (SBI). These interactions typically use HTTP/2-based APIs and JSON data formats, enabling flexible and scalable communication between functions.

According to the 3GPP specifications, the NF that offers a service is referred to as the Service Producer, while the NF that uses the service is called the Service Consumer. Communication between producers and consumers typically takes one of three forms: query, subscription, and notification.

![SBA](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_protocols/Images_mobile_communication/free5g_SBA.png)

The Network Repository Function (NRF) plays a crucial role in enabling NF registration and discovery. It allows NFs to register their availability and capabilities with the network, while also supporting the discovery of other NFs to enable efficient communication.

Communication interfaces are what bind the 5G Core. Reference point interfaces carry signaling and user traffic, while the SBA ensures modular Control Plane functions can interact smoothly. Together, they make the 5G Core operate as a coordinated and scalable system.


## Building and running free5G

To build and run free5GC safely and consistently, it’s best to use a virtual machine (VM). A VM provides an isolated environment that prevents conflicts with your host system and ensures consistent behavior across setups.

In this course, we’ll use VirtualBox to host an Ubuntu 20.04 LTS server. This environment forms the foundation for installing, configuring, and testing free5GC.

Let’s go through the steps to install Ubuntu and create your VM.

### 1 - Install VirtualBox and Ubuntu ISO

Install VirtualBox(opens in a new tab) on your machine. 

Download the Ubuntu Server 20.04 LTS(opens in a new tab) ISO file. You can choose either the live-server or the desktop version.

💡 Tip: The server version uses fewer resources and is ideal for lab environments.

### 2 Create a New Virtual Machine

Open VirtualBox and create your first VM using the downloaded ISO image file. 

Allocate at least 1-2 CPUs and a minimum of 2048MB of memory.

Add a “Host-only” network interface to allow communication between your host and VM.

### 3 Complete the Ubuntu Installation

Boot the VM with the ISO image and finish the Ubuntu installation

### 4 Update and Upgrade the VM

Run the following commands in the terminal to update and upgrade the Ubuntu VM, ensuring it has the latest security updates:

```
sudo apt update
sudo apt upgrade
sudo apt install net-tools vim -y
```

After running these commands, your Ubuntu VM will be fully updated and equipped with basic tools for networking and text editing.

💡 Tip: Once your base Ubuntu VM is ready, you can clone it to create additional testing environments without repeating the installation process. This is especially helpful when experimenting with multiple configurations of free5GC.

Now that your Ubuntu VM is ready, the next step is to clone and configure it for free5GC.

This ensures each instance has the proper hostname, IP address, and network configuration before installing the core network.

## Cloning and configuring free5G

To avoid repeating the setup steps for future VMs, it’s helpful to clone your base Ubuntu VM. This cloned VM will serve as the environment where free5GC will be installed and run.

This approach saves time and ensures every instance starts from a clean, consistent configuration.

### Step 1: Clone the VM

Open VirtualBox, right-click the VM you just created, and select the clone option to clone a new VM. You can refer to the following image for guidance.
Screenshot of the VirtualBox “Clone Virtual Machine” window showing a new VM named free5GC. The linked clone option and MAC address policy to generate new addresses for all network adapters are selected.

Cloning the base Ubuntu VM as free5GC in VirtualBox.

### Step 2: Change the Hostname

Open the cloned VM. The hostname will be the same as the original VM, so use the following command to update it to free5GC.

```
sudo vim /etc/hostname
```

### Step 3: Update the Hosts File

Edit the `/etc/hosts` file:
```
sudo vim /etc/hosts
```

Update the entries so they look like this:

```
127.0.0.1 localhost
127.0.1.1 free5GC
...
```

After making these changes, reboot the VM to apply them.

### Step 4: Configure the Network Interface

By default, the Host-only network interface obtains its IP address through DHCP. However, the cloned free5GC VM will not automatically receive a new IP address, so you need to configure it manually. Use the following commands:
```
sudo vim /etc/netplan/00-installer-config.yaml
```
Modify the `/etc/netplan/00-installer-config.yaml` file with the following content:

```
# This is the network config written by 'subiquity'
network:
  ethernets:
    enp0s3:
      dhcp4: true
    enp0s8:
      dhcp4: no
      addresses: [192.168.56.101/24]
  version: 2
```
After modifying the file, apply the settings with these commands:

```
sudo netplan try
sudo netplan apply
```
At this point, your free5GC VM should be ready with the correct hostname and a static IP address. You’re now ready to begin installing and configuring free5GC.

Static IPs ensure your virtual network remains stable even if your host restarts or other VMs are added. This prevents connectivity issues later when testing with UERANSIM.

💡 Tip: Static IPs ensure your virtual network remains stable even if your host restarts or other VMs are added. This prevents connectivity issues later when testing with UERANSIM.

Your cloned VM is now configured with a unique hostname and a stable network identity. Next, you’ll install the required packages and dependencies that make free5GC operational.

## Installing the required packages

Before you can build and run free5GC, you need to install several system packages and dependencies. This ensures your system has the proper tools, Go runtime, database support, and development libraries.

We’ll walk through these steps one by one.

### Step 1: Verify Kernel Version

free5GC requires Linux kernel version  5.0.0-23-generic or 5.4.x. You can check your kernel version with the following command:
```
uname -r
```
If your version matches, you’re good to go. Otherwise, you may need to install a compatible version.

### Step 2: Install Prerequisite Tools

We need to install wget and git. These tools are essential for downloading source code and files from the internet and GitHub repositories.
```
sudo apt -y install wget git
```
### Step 3: Install the Go Programming Language

free5GC is written in Go. You need to install the specific version it was built and tested with, which is Go 1.21.8. 

The following commands will download the Go archive, extract it to the correct location, and set up the necessary environment variables in your .bashrc file so your system can find and use Go.
```
wget https://dl.google.com/go/go1.21.8.linux-amd64.tar.gz
sudo tar -C /usr/local -zxvf go1.21.8.linux-amd64.tar.gz
mkdir -p ~/go/{bin,pkg,src}
echo 'export GOPATH=$HOME/go' >> ~/.bashrc
echo 'export GOROOT=/usr/local/go' >> ~/.bashrc
echo 'export PATH=$PATH:$GOPATH/bin:$GOROOT/bin' >> ~/.bashrc
echo 'export GO111MODULE=auto' >> ~/.bashrc
source ~/.bashrc
```

### Step 4: Install MongoDB Database

free5GC uses MongoDB to store subscriber information.

Note that modern versions of MongoDB require a CPU feature called AVX.

⚠️ Warning: Note that modern versions of MongoDB require a CPU feature called AVX.

First, run this command to check if your CPU supports AVX.
```
lscpu | grep avx
```
If the command shows any output, you can proceed.

These commands will add the official MongoDB software repository to your system, update your package list, and install the database.

```
sudo apt install -y gnupg curl
curl -fsSL https://www.mongodb.org/static/pgp/server-7.0.asc | \
sudo gpg -o /usr/share/keyrings/mongodb-server-7.0.gpg --dearmor

echo "deb [ arch=amd64,arm64 signed-by=/usr/share/keyrings/mongodb-server-7.0.gpg ] https://repo.mongodb.org/apt/ubuntu focal/mongodb-org/7.0 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-7.0.list

sudo apt update
sudo apt install -y mongodb-org
```

After installation, use the final command to start the database service and verify it's running correctly.

```
sudo systemctl start mongod
sudo systemctl status mongod
```
You should see active (running) in the status output, which confirms a successful installation.

### Step 5: Install Build Dependencies

Finally, before you can compile free5GC itself, you need to install several C/C++ libraries and development tools. These packages are required for building the low-level user-plane components that handle network traffic.

```
sudo apt -y update
sudo apt -y install git gcc g++ cmake autoconf libtool pkg-config libmnl-dev libyaml-dev
```

After completing these installations, your VM now has the tools and dependencies needed to build and run free5GC.

If you plan to experiment with newer MongoDB versions or Go releases later, document your environment versions first. This makes it easier to troubleshoot or replicate your setup later.

💡Tip: If you plan to experiment with newer MongoDB versions or Go releases later, document your environment versions first. This makes it easier to troubleshoot or replicate your setup later.

With all required packages installed, your system is ready to download, build, and launch the free5GC core components.

### Build and launch the core components

Before you can run free5GC, you need to download the source code and compile the necessary binaries.

We’ll walk through the full build process, covering how to clone the repository, compiling both control and data plane components, and also setting up the web-based console to manage user data.

These steps assume you’ve already completed the system and package setup on your VM.

### Step 1: Clone the free5GC Repository

Clone the latest version of the free5GC repository from GitHub using the following commands:
```
cd ~
git clone --recursive -b v4.1.0 -j `nproc` https://github.com/free5gc/free5gc.git
cd free5gc
```
### Step 2: Build Control Plane Network Functions (NFs)

After cloning the repository, compile the NF services in free5GC. There are two ways to build the executable files.

To build each NF individually (e.g., AMF), use:
```
make amf
```
Or simply build all NFs at once using:
```
make
```
### Step 3: Build the User Plane Function (UPF)

The previous commands built all control plane NFs, but you also need to build the data plane NFs.

First, install gtp5g, a 5G GTP-U kernel module maintained by the free5GC team:
```
git clone -b v0.9.14 https://github.com/free5gc/gtp5g.git
cd gtp5g
make
sudo make install
```
Then, build the UPF using the following command (you may skip this step if you built all NFs earlier):
```
cd ~/free5gc
make upf
```
Now, you can use the following command to run free5GC :
```
./run.sh
```
### Step 4: Build and Launch the Webconsole

To manage subscriber data, such as adding or modifying users, you will need to build and run the free5GC Webconsole, which provides a graphical user interface for these tasks.

First, install Node.js using the following commands:
```
curl -fsSL https://deb.nodesource.com/setup_20.x | sudo -E bash - 
sudo apt update
sudo apt install -y nodejs
corepack enable
```
Then, build the Webconsole using:
```
cd ~/free5gc
make webconsole
```
Start the Webconsole with the following command:
```
cd ~/free5gc/webconsole
./bin/webconsole
```
Open your web browser from your host machine, and connect to Webconsole at http://192.168.56.101:5000(opens in a new tab). 

(Default username: admin, password: free5gc)

💡Tip: The Webconsole provides an easy way to view and manage subscriber (UE) information without manually editing configuration files.

With all components successfully built, your free5GC setup is now ready for use.

Next, you’ll configure IP forwarding and NAT so packets can move between your simulated network and external systems.

## System configuration

Although free5GC is now installed, additional settings are required to ensure packets can reach the data network through the core network.

By default, the Linux system disables IP forwarding, meaning it does not forward packets between different subnets. However, in free5GC, packet forwarding is necessary.

For example, the UE communicates with free5GC through a host-only network interface, but packets need to reach the data network via a NAT network interface.

### Enable IP Forwarding

Enabling IP forwarding is essential to allow packets to move between different network interfaces.

You can enable it with the following command:
```
sudo sysctl -w net.ipv4.ip_forward=1
```
### Add a NAT Rule

Another important step is setting up a Network Address Translation (NAT) rule. By default, Linux does not perform NAT, meaning external networks won't recognize the source IP of the packets, preventing them from reaching their destination or receiving responses. To resolve this, you need to add a NAT rule to iptables using the following command:
```
sudo iptables -t nat -A POSTROUTING -o <dn_interface> -j MASQUERADE
```
Replace <dn_interface> with the name of your NAT network interface( e.g. enp0s3)

Example:
```
sudo iptables -t nat -A POSTROUTING -o enp0s3 -j MASQUERADE
```
### Disable the Firewall (Optional)

To avoid potential connectivity issues, you may also want to disable the firewall. You can do this using the following commands:
```
sudo systemctl stop ufw
sudo systemctl disable ufw
```
Only disable the firewall in secure, non-production environments. For production or shared systems, configure proper firewall rules instead.

⚠️ Warning: Only disable the firewall in secure, non-production environments. For production or shared systems, configure proper firewall rules instead.

With IP forwarding enabled, NAT configured, and the firewall disabled, your free5GC environment is now prepared for proper packet forwarding and communication with external networks.

Next, you’ll test the setup using UERANSIM, which simulates a 5G device to confirm successful communication with the free5GC core.


## Test connectivity

After completing the system configuration, you should be able to create a UE and connect to the data network using free5GC.

To validate this, you can use UERANSIM (https://github.com/aligungr/UERANSIM) (opens in a new tab), an open source 5G UE and RAN simulator. It allows you to test connectivity without physical hardware by emulating how a UE communicates with the core.

This provides a quick way to confirm that your free5GC setup is functioning as expected.

Steps to Test Connectivity

To perform the test:

   ### 1

    Install UERANSIM
    Follow the installation steps provided in the UERANSIM Wiki(opens in a new tab).
    
  ###   2

    Update free5GC Configuration
    Adjust the necessary parameters in the free5GC configuration files.
    (Refer to Sections 5 and 6 of the official tutorial(opens in a new tab) for detailed guidance.)
    
  ###   3

    Run the Simulation
    Start UERANSIM to simulate a UE connection and verify that registration is successful.

💡Tip: UERANSIM doesn’t require real 5G hardware; it emulates both the UE and gNB. This makes it ideal for testing and learning how the core network behaves before deploying on real equipment.

With a successful simulation, your 5G core setup is fully verified. You’ve now completed the process of building, configuring, and testing a working free5GC environment.

## Exploring the souce code

This chapter takes you on a guided tour of the free5GC source code, showing how a modern 5G Core network is constructed from the ground up. We begin by exploring the anatomy of a core Network Function (NF), using the Network Repository Function (NRF) as our example. You will learn to navigate an NF’s internal file structure and understand the purpose of each component.

The chapter then brings the code to life by tracing the execution path of an API request, from its entry point to the business logic processor. This will equip you with the skills to follow the operational flow of any network function and see how different modules are interconnected.

Finally, you will explore the powerful role of OpenAPI, learning how free5GC automatically generates 3GPP-compliant code from official specifications to ensure standardization and accelerate development.

### Anatomy of a network function (NF)

To work effectively with free5GC, developers need to understand how a Network Function (NF) is organized internally.

In this example, we’ll look at the Network Repository Function (NRF) and examine how its code directories map to specific responsibilities.

The directory structure of a Network Function is logically organized to separate different responsibilities. Understanding this layout is the first step to navigating the code effectively.

#### cmd

The application’s main entry point. When you compile and run the NRF, the main() function inside this directory is the first piece of code that executes. A developer should look here to understand the initial startup sequence, such as how the configuration from the factory is loaded and how the logger is initialized.

https://github.com/free5gc/nrf/blob/0067e052aced23822cc4d32d65d61d0521ab141b/cmd/main.go

#### internal

Contains code accessible only to the NRF itself and cannot be imported by other network functions. This is crucial for preventing other parts of the system from depending on implementation details that might change.

    context – This is the state management center of the NF. It holds all the runtime data and state, such as the profiles of other NFs that have successfully registered.

    logger – This package contains the logging setup specific to the NRF. It ensures that log messages are formatted and output consistently.

    SBI – This stands for Service-Based Interface, the heart of the NF's external communication capabilities. This is where the 3GPP-specified RESTful APIs are implemented. Developers will spend most of their time here when tracing API requests or modifying endpoint behavior.

    util – A collection of utility or helper functions used throughout the NRF's internal packages. This avoids code duplication for common tasks.

#### pkg

In contrast to internal, pkg contains public code that is designed to be shared and imported by other components or NFs.

    app - Contains the main application logic that orchestrates the different components of the NRF. It's responsible for tying together the server, services, and context.

    factory - This directory uses the 'factory' design pattern to create and initialize objects based on configuration. Its main role is to read the NRF's configuration file (e.g., nrfcfg.yaml) and construct the initial state and settings for the NF.

    service - Contains the high-level service implementation and business logic for the NRF. It defines the core functionalities, such as handling service registration and discovery requests.

#### go module files

These files are standard for managing dependencies in a Go project.

    go.mod - This file explicitly defines the NRF's module path and lists all its dependencies, such as the external libraries it needs to function, like the Gin web framework.

    go.sum - This is a lock file that contains the cryptographic checksums of each direct and indirect dependency. It ensures build integrity by guaranteeing that you are always using the exact same version of the libraries.


Together, these directories and files form the foundation of an NF, providing a clear separation of responsibilities while supporting standardized communication in the 5G Core.

#### How a Network Function Starts

Understanding the directory structure provides a static map of the source code. Now, let's bring that map to life by tracing the dynamic operational flow of a Network Function from the moment it starts.

By following the startup sequence of the NRF, we can see exactly how the different packages we just reviewed (cmd, factory, logger, context, and service) collaborate to initialize and launch the service.


#### Initialization

    The application starts from the cmd directory's main function

    It loads the configuration using the factory package

    Sets up logging through the logger package

#### Context Setup

    The context package initializes and maintains the NRF's state

    It manages information about registered network functions

#### Service Registration

    The service package implements the RESTful APIs needed for NRF

    It uses the SBI (Service-Based Interface) implementation from the internal/sbi directory    

#### Core Functionality

    NRF provides service discovery for other network functions

    It maintains a registry of available network functions

    Handles service registration, deregistration, and discovery

    Supports OAuth2-based authorization for other network functions    

Together, these steps demonstrate how free5GC cleanly separates concerns while ensuring each NF remains interoperable across its modular architecture.


### Inside the SBI directory

Now that we understand the static file structure and startup sequence, the next step is to trace the dynamic flow of a live request. This is the most effective way to see how a Network Function performs its core operations. In free5GC, all API-related logic is centralized within the internal/sbi directory, which contains the implementation of the Service-Based Interface.

Before we trace a specific request, let's first break down the key components within this critical directory. For our example, we’ll look at api_accesstoken.go, but the same structure applies broadly across the SBI package.

#### Consumer

Contains client-side logic for consuming other Network Functions’ services. It allows the NRF to send outbound requests to register, discover, or query peer NFs.

#### processor

Implements the core business logic executed when the NRF receives an API request. It interprets the data passed from handlers, applies the 3GPP rules, and produces structured response

#### API implementation files (api_*.go)

These Go files define individual HTTP request handlers. Each handler manages HTTP-specific tasks such as parsing input, validating data, and forwarding requests to the processor.

#### router.go

Responsible for registering and managing API routes. It maps URL paths and HTTP methods (e.g., POST /oauth2/token) to their corresponding handler functions.

#### server.go 

Defines the HTTP server configuration. It establishes connections, sets up middleware, and ensures that incoming HTTP/2 traffic is properly dispatched to the router.

Together, these components provide the foundation for how free5GC handles API communication. Understanding their roles is an important step before tracing how a live request moves through the system.


### Tracing API implementation: step-by-step method

With an understanding of the main components inside the SBI directory, we can now trace a real API request from start to finish. This exercise shows how an incoming request moves through different layers of code, from route registration to handler to processor, revealing the clear separation of concerns in free5GC. This skill is essential for debugging and development, helping developers pinpoint issues and understand how different modules interact in real time.

To make this a practical exercise, we will trace a real API call: the OAuth2 Access Token request, whose handler is defined in api_accesstoken.go.

#### Step 1: Identify the API Route Registration

Any API request begins with routing. The first step is to find where the API's URL path is mapped to a specific handler function in the code. This mapping is called route registration.

In internal/sbi/api_accesstoken.go, we find the following code:

```
func (s *Server) getAccesstokenRoutes() []Route {
    return []Route{
        …
        {
            "AccessTokenRequest",
            http.MethodPost,
            "/oauth2/token",
            s.HTTPAccessTokenRequest,
        },
…
}
```
This code defines a route that maps an incoming HTTP POST request on the /oauth2/token path to the s.HTTPAccessTokenRequest handler. This is the precise entry point for this API call within the Go code.

#### Step 2: Explore the Request Handler

Now that the router has directed the request to HTTPAccessTokenRequest, let's examine what this handler function does. The primary role of a handler in free5GC is to manage the HTTP-level concerns of the request, parsing, validation, and preparation, not to perform the core business logic itself. This is a clean separation of concerns.
```
func (s *Server) HTTPAccessTokenRequest(c *gin.Context) {
    // Check if OAuth is enabled
    if !factory.NrfConfig.GetOAuth() {
        // Return error if disabled
        // ...
     }
    var accessTokenReq models.NrfAccessTokenAccessTokenReq
    // Parse form data from request
    // ...
    // Process request fields using reflection
    // ...
    // Forward to processor for business logic
    s.Processor().HandleAccessTokenRequest(c, accessTokenReq)
}
```
As shown in the code, the handler performs several preparatory steps:
 - 1 Verifies that the OAuth2 feature is enabled in the configuration.
 - 2 Parses the incoming HTTP form data into a structured Go object (accessTokenReq).
 - 3 Uses reflection to map form fields to a structured model.
 - 4 Forwards the request to the processor.

#### Step 3: Follow the Flow to the Processor

The final step in our trace is to follow the request to its ultimate destination: the processor. This is where the core business logic is executed. The handler delegates the request with this single line of code:
```
s.Processor().HandleAccessTokenRequest(c, accessTokenReq)
```
This call forwards the request context and the parsed accessTokenReq model to the HandleAccessTokenRequest method inside the processor. To see how the NRF actually validates credentials and generates a token, a developer would need to examine this method in processor/access_token.go.

The processor layer relies on functions and models generated from OpenAPI specifications, ensuring adherence to 3GPP standards. We will revisit this in future topics.

⚠️ Warning:When troubleshooting, trace the request path in the following order: router, handler, and then processor. This helps pinpoint exactly where behavior diverges from expectations.

This step-by-step trace illustrates how free5GC routes and processes requests in a consistent and modular way, preparing you to understand the full API execution flow in the next section.

### free5GC API Execution Flow

Now that you've explored how the OAuth2 /oauth2/token endpoint is implemented in free5GC, let’s step back and look at the broader execution pattern shared by most APIs in the system.

This high-level flow helps reinforce the overall structure of how Network Functions (NFs) receive, route, and process requests within free5GC.

#### 1 HTTP Request Arrives at the Server

An external client (like another NF) sends an HTTP/2 request, which is the initial point of contact with the NF. The `server.go` component is responsible for handling the low-level network connection and accepting this incoming request.

#### 2 The Router Dispatches the Request

The `router.go` component acts like a traffic controller. It inspects the request's URL path and HTTP method (e.g., POST /oauth2/token) and consults its list of registered routes to determine which specific handler function should process it.

#### 3 The Handler Parses and Validates

The designated API handler (e.g., HTTPAccessTokenRequest in `api_accesstoken.go`) takes over. Its job is to handle HTTP-specific tasks, such as parsing the raw request data into a structured Go object and performing initial validation checks.

#### 4 The Handler Delegates to the Processor

Once the request is prepared and validated, the handler's responsibility ends. It delegates the structured data to the processor layer, which is responsible for the actual business logic. This handoff is a key example of the separation of concerns.

#### 5 The Processor Executes the Business Logic

The processor is the brain of the operation. It performs the core task, for example, generating an access token, querying the NF's state from the context, or registering a new NF profile. After executing its logic, it prepares a structured response object.

#### 6 The Response is Returned to the Client

The flow reverses. The processor returns the response object to the handler. The handler then serializes this object into a standard format (like JSON) and sends it back over the HTTP connection to the original client, completing the request cycle.

💡 The free5GC architecture ensures every API follows a predictable flow. Once you learn to trace one request, you can confidently navigate others using the same logic.

This consistent execution pattern applies across all APIs in free5GC, making it easier for developers to trace requests, understand dependencies, and debug issues.

### Tracing code dependencies

We’ve explored the static file structure of a Network Function and traced its dynamic API flow. Now, let’s connect these ideas by examining the dependencies that link everything together. Understanding how to trace and manage the relationships between modules in the free5GC codebase is a critical skill for effective development and debugging.

Every Go source file begins by importing the packages it depends on. By examining these import statements, we can identify and categorize the file's dependencies and see how it interacts with other parts of the system.

Let’s look at an example from the NRF, `api_accesstoken.go`, to see what these dependencies reveal.

```go
import (
    "github.com/gin-gonic/gin"
    "github.com/free5gc/nrf/internal/logger"
    "github.com/free5gc/nrf/internal/util"
    "github.com/free5gc/nrf/pkg/factory"
    "github.com/free5gc/openapi/models"
)
```
    
This import block defines every external and internal package the file uses. By studying it, we can categorize these dependencies and see how each one supports the NRF’s functionality.

#### External dependency

Third-party libraries that are not part of the free5GC project itself. They provide general functionality, such as web frameworks or database drivers.

 - `github.com/gin-gonic/gin`: A high-performance HTTP web framework for Go. free5GC uses Gin to handle low-level details of routing and managing API requests. The handler function in this file receives its request context directly from the Gin engine.

#### Internal dependecies

Packages within the same Network Function (in this case, the NRF). They are typically located in the internal or pkg directories and. are specific to NRF's operation.

 - `github.com/free5gc/nrf/internal/logger`: The NRF’s private logging package used to write log messages.
 - `github.com/free5gc/nrf/internal/util`: A package containing internal helper functions used only within the NRF.
 - `github.com/free5gc/nrf/pkg/factory`: The package that holds the NRF's configuration data, which is loaded from the YAML file at startup.

#### Shared project dependencies

Packages that are part of the free5GC project but are designed to be shared and used by multiple Network Functions to ensure consistency.

 - `github.com/free5gc/openapi/models`: This is a critical shared package containing the Go data structures generated from 3GPP OpenAPI specifications. Using these common models allows different NFs (like the AMF and NRF) to communicate using a standardized, compliant language.


Tracing imports helps developers understand how modules are connected and where functionality originates, providing a clearer view of how the system works as a whole.


### AMF specific dependencies

While many NFs share common dependencies for tasks like logging or configuration, a control-plane function like the AMF (Access and Mobility Management Function) has a specialized role that requires a unique set of libraries. These dependencies are dictated by the critical interfaces the AMF must manage: the N1 interface to the User Equipment (UE) and the N2 interface to the Radio Access Network (RAN).

#### N1 interface: communicating with the UE

The N1 interface is the AMF's direct communication link to the user's device for all control plane signaling, such as registration and authentication.

To manage this crucial connection, the AMF code depends heavily on:

 - NAS (Non-Access Stratum) Libraries: NAS is the protocol "spoken" between the UE and the AMF. The AMF requires libraries to encode and decode NAS messages for procedures like registration, authentication, and service requests.
 - Security Protocol Libraries: As the UE's first point of contact in the core network, the AMF is responsible for securing the connection. This requires dependencies on libraries that implement the necessary security and encryption protocols for UE communication.
 - Session Management Libraries: The AMF coordinates with the SMF (Session Management Function) to establish data sessions for the UE. This requires libraries to manage the PDU session state and communication.

#### N2 interface: communicating with the RAN   

The N2 interface connects the AMF to the gNodeB (the 5G cell tower). This link is essential for managing the UE's connection to the network and its mobility (e.g., moving between cell towers). Key dependencies for the N2 interface include:

 - NGAP (Next Generation Application Protocol) Libraries: This is the primary signaling protocol used over the N2 interface. The AMF relies on NGAP handling libraries to manage the UE context within the RAN, establish radio bearers, and coordinate handovers.
 - SCTP Transport Libraries: NGAP messages are typically transported over SCTP, a reliable transport protocol suited for signaling. The AMF code, therefore, requires a dependency on an SCTP library to establish and maintain this vital communication link to the RAN.
 - Handover Procedure Implementations: Managing UE mobility is a core AMF task. This requires complex logic for handover procedures, which are orchestrated using the NGAP protocol.

💡 Each Network Function’s dependencies reflect its role in the 5G Core. By identifying which packages and libraries a function relies on, developers can better understand how data and control flow through the network.

Understanding the AMF’s specialized dependencies highlights how free5GC tailors each Network Function to its unique responsibilities.

### Communication between network functions

Identifying dependencies gives us a map of the potential communication paths between Network Functions. Now, let's trace a message along one of those paths to see how this interaction works in practice.
Diagram showing a client Network Function (Client NF) on the left sending a “Discovery Request” to the NRF on the right, and the NRF returning a “Response.” The Client NF is labeled as the consumer sending a request, and the NRF is labeled as the server receiving and processing the request.

In a service-based architecture, NFs constantly communicate with each other, with one NF acting as a consumer (client) and another as a server. For example, let's examine the code for when a client NF sends a discovery request to the NRF.

Client NF (other NF):

```go
// Consumer sending a discovery request to NRF
discoveryRes, err := consumer.SendSearchNFInstances(param)
```

Server NF (NRF):

```go
// Handler receiving the discovery request
func (s *Server) HTTPNFDiscoveryRequest(c *gin.Context) {
    // Process and forward to processor
    s.Processor().HandleNFDiscoveryRequest(c, searchFilter)
}
```

This approach allows you to explore how a message (like a discovery request) flows from one NF to another, through the consumer, API handler, and processor layers.

Tracing dependencies shows not only what each file imports, but how modules interact to support the larger system. This perspective helps developers navigate the codebase with greater confidence and clarity.

🔑 Understanding how Network Functions communicate helps bridge the gap between individual source files and the overall behavior of the 5G Core. These communication paths become even clearer when viewed through free5GC’s OpenAPI-generated interfaces, which standardize interactions across all Network Functions.

### Leveraging OpenAPI specifications in free5GC

The 3GPP organization publishes official OpenAPI specification files that define the service-based interfaces (SBIs) for 5G core network functions. Think of these files, written in standard YAML or JSON format, as a strict API contract or a detailed blueprint for communication. They serve as the authoritative definition of how network functions must interact, ensuring that a compliant NF from one vendor can seamlessly communicate with one from another.

This blueprint is a machine-readable file that precisely defines every aspect of an NF's interface, leaving no room for ambiguity.

reference: 
 - https://www.3gpp.org/technologies/openapis-for-the-service-based-architecture
 - https://forge.3gpp.org/rep/all/5G_APIs


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

A complete list of possible success and error status codes, so a client application knows how to handle any outcome.
The exact structure of request and response messages, ensuring all NFs "speak" the same language.


The free5GC developers can access these specifications from:
 - 3gpp web site: https://www.3gpp.org/ftp/Specs/archive/29_series/
 - The free5GC repository's OpenAPI directory: https://github.com/free5gc/openapi

OpenAPI specifications create a shared language between all 5G Core Network Functions. By defining every endpoint, method, and message structure, they make true interoperability and vendor neutrality possible.

#### Code generation tools

As established in the previous section, the real power of having a standardized, machine-readable API contract is the ability to automate development. The OpenAPI Generator is the tool that makes this automation possible.

In free5GC development, OpenAPI is primarily used for:

 - Converting 3GPP OpenAPI specifications into Go code.
 - Generating consistent data models and API interfaces.
 - Implementing standardized HTTP/REST network function interfaces.

#### Installation and Setup in free5GC

First, you need to install the OpenAPI Generator. Two approaches are available:

Docker (recommended to avoid Java dependency issues)

```
# Pull the OpenAPI Generator Docker image
docker pull openapitools/openapi-generator-cli:v7.12.0
```

JAR File

```
# Download the JAR file 
wget https://repo1.maven.org/maven2/org/openapitools/openapi-generator-cli/7.12.0/openapi-generator-cli-7.12.0.jar -O openapi-generator-cli.jar 
# Create a convenient execution alias 
alias openapi-generator="java -jar $(pwd)/openapi-generator-cli.jar"
```

Code Generation Examples from 3GPP Specifications

Here’s a complete example of using the OpenAPI Generator to generate Go code from the 3GPP NRF API specifications.

The commands below show both the Docker and JAR file methods for generating the same output.

Using Docker

```
docker run --rm -v "${PWD}:/local" openapitools/openapi-generator-cli generate \
 -i /local/spec/TS29510_Nnrf_NFManagement.yaml \
 -g go \
 -o /local/internal/nrf/api \
--additional-properties=packageName=api,withGoCodegenComment=true,enumClassPrefix=true
```

Using JAR File

```
java -jar openapi-generator-cli.jar generate \
 -i spec/TS29510_Nnrf_NFManagement.yaml \
 -g go \
 -o internal/nrf/api \
--additional-properties=packageName=api,withGoCodegenComment=true,enumClassPrefix=true
```

Common Options Explained

The OpenAPI Generator supports several options that control how code is produced. The most common ones used in free5GC development are explained below:
 - `-i`: Specifies the input OpenAPI specification file.
 - `-g go`: Uses the Go language generator.
 - `-o`: Specifies the output directory for the generated code
 - `--additional propierties`: Sets specific generator options such as:
    - `packageName`: Defines the generated Go package name.
    - `withGoCodegenComment`: Adds generation comments to files.
    - `enumClassPrefix`: Adds a prefix to enum types.
    - `isGoSubmodule`: Specifies whether to generate code for a submodule.
  
With these tools in place, developers can quickly transform 3GPP specifications into working Go code, ensuring consistency with standards while freeing them to focus on building functionality rather than boilerplate.

### OpenAPI code analysis

After running the OpenAPI Generator, you’ll have a new set of Go files in your project. While it might be tempting to treat this generated code as a “black box,” it's essential for a developer to understand its structure and purpose.

Analyzing this code is crucial because it provides the fundamental toolkit for implementing your Network Function’s business logic. These files contain the standardized building blocks, the data structures, and API contracts that your custom code will use to communicate and operate in a 3GPP-compliant way.
Illustration showing how generated Go files in free5GC contain Data Models and API Interfaces that feed into the free5GC logic layer.

Let's explore the two primary components you'll find in the generated code: Data Models and Server/Client Interfaces.

Data Models

Data Models

Structured Go types that represent the messages exchanged between network functions. These include:
 - Request structures
 - Response structures
 - Common data types used across different APIs

The following example shows one of these generated models as it appears in the NRF specification.

```go
// Generated model example from NRF specification
type NrfAccessTokenAccessTokenReq struct {
    GrantType      string             `json:"grant_type" yaml:"grant_type"`
    NfInstanceId   string             `json:"nfInstanceId" yaml:"nfInstanceId"`
    RequesterPlmn  *models.PlmnId     `json:"requesterPlmn,omitempty" yaml:"requesterPlmn"`
    TargetNfType   models.NfType      `json:"targetNfType" yaml:"targetNfType"`
    Scope          string             `json:"scope" yaml:"scope"`
    TargetNfPlmn   *models.PlmnId     `json:"targetNfPlmn,omitempty" yaml:"targetNfPlmn"`
}
```

The NrfAccessTokenAccessTokenReq structure is an example of an OpenAPI-generated data model that represents an access token request in the NRF. Each field corresponds to a parameter defined in the 3GPP specification, and the JSON and YAML tags ensure proper serialization and deserialization.

#### Server/Client Interfaces

The OpenAPI Generator reads the 3GPP-defined OpenAPI specifications and generates Go interfaces that define standard communication contracts between network functions. The interfaces directly map REST endpoints to programming methods, ensuring compliant communication throughout the system.

The following example shows one of the generated interfaces created from the 3GPP specifications.

```go
// Example of generated API interface
type NFManagementApi interface {
    RegisterNFInstance(nfInstanceID string, nfRegistration models.NfRegistration) (models.NfRegistration, error)
    GetNFInstance(nfInstanceID string) (models.NfProfile, error)
    UpdateNFInstance(nfInstanceID string, patchItem []models.PatchItem) (models.NfProfile, error)
    DeregisterNFInstance(nfInstanceID string) error
}
```

In this example, the NFManagementApi interface defines a set of standardized operations for managing Network Functions. Each function maps to a specific REST endpoint, providing a consistent contract between servers and clients. Developers later implement the logic for these functions in the processor layer, using the OpenAPI-generated models to handle the data structures.

🔑 The OpenAPI-generated models and interfaces do more than define structure. They guide how the processor works. By passing standardized models, such as NfProfile, into functions like HandleNFRegisterRequest, free5GC ensures consistent communication and compliance with 3GPP specifications.

These interfaces serve both server implementations (which must fulfill these contracts) and client code (which calls these methods), ensuring consistent communication throughout the system.

Together, the generated data models and interfaces form the backbone of free5GC’s compliance with 3GPP standards, giving developers reliable building blocks for extending and customizing core functionality.

### Integration with free5GC architecture

Now that we’ve explored what’s inside the generated Go files, let’s see how these components integrate into the free5GC architecture. The OpenAPI-generated code provides standardized data models and API interfaces, while the processor brings them to life by implementing the business logic that drives each network function.

The architecture of free5GC is designed around a clear separation of concerns between automatically generated code and manually written business logic. The processor component is where this integration happens. Think of the relationship as symbiotic:
 - The OpenAPI-generated code provides the standardized data structures (the models).
 - The processor provides the custom business logic that operates on that data.

 A Practical Example: NF Registration

This relationship is perfectly illustrated when handling a network function registration request. The processor receives the request data packaged neatly into a standardized model:

```go
func (p *Processor) HandleNFRegisterRequest(c *gin.Context, nfProfile models.NfProfile) {
    // Process the registration using the standardized model
    nfInstanceID := p.NfInstanceIDFromNfProfile(nfProfile)
    p.SetNfProfiles(nfInstanceID, nfProfile)
    // Additional business logic...
}
```

Let’s break down what’s happening here:

####  The Standardized Input
    Notice the function signature: nfProfile models.NfProfile. The processor doesn't deal with raw JSON or HTTP data. Instead, it receives a clean, validated NfProfile object, which is a struct generated directly from the 3GPP specification. The API handler has already parsed and validated the request into this model.
    
####  The Custom Logic
    Inside the function, the processor executes the actual business logic. It uses the data within the nfProfile object to perform its tasks, such as extracting the instance ID and storing the profile in the NRF's context. This part of the code is handwritten by developers and defines the unique behavior of the NRF.

This clean separation allows developers to focus on the core functionality within the processor, confident that the data they are working with is always structured and compliant, thanks to the OpenAPI-generated models. The processor provides the intelligence, while the generated code provides the standardized skeleton.

#### Benefits of the Use of the OpenAPI

By starting with standard 3GPP specifications and generating code automatically, free5GC ensures strong adherence to these specifications while greatly reducing implementation time.

By understanding how free5GC leverages OpenAPI specifications, developers can more effectively contribute to the project, extend its functionality, and maintain compliance with evolving 5G standards.

