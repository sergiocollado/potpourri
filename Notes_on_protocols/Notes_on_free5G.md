
# Notes onf free5G

References:
 - https://training.linuxfoundation.org/training/introduction-to-free5gc-lfs114/
 - https://free5gc.org/
 - https://github.com/free5gc/free5gc
 - https://github.com/aligungr/UERANSIM

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


