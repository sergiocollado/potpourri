 # Notes on Linux networking



## Network concepts


### Machine interface

#### MAC address
 unique figerprint of the network interface
 
#### IP address
 Unique address on the network
 
#### Subnet
 Separates the IP into network and host address, and defines the size of the network
 
#### Gateway
  The connection leading outside of the local network
  
#### DNS host
 Translates hostname into IP addresses

#### DNS Domain 
 The lookup domain for the host

#### Commands
  The commands to identify the previous data are: ifconfig, ip, nmcli, routel. 

#### ifconfig

check `man ifconfig`. Take into account `ifconfig` is deprecated. 

`lo` the loopback interface, this is a virtual interface that the system uses to communicate with itself. 

#### ip

`ip address show` use this better than `ipconfig`

```bash
Show / manipulate routing, devices, policy routing and tunnels.
Some subcommands such as ip address have their own usage documentation.
More information: https://www.man7.org/linux/man-pages/man8/ip.8.html.

 - List interfaces with detailed info:
   ip address

 - List interfaces with brief network layer info:
   ip -brief address

 - List interfaces with brief link layer info:
   ip -brief link

 - Display the routing table:
   ip route

 - Show neighbors (ARP table):
   ip neighbour

 - Make an interface up/down:
   ip link set interface up/down

 - Add/Delete an IP address to an interface:
   ip addr add/del ip/mask dev interface

 - Add a default route:
   ip route add default via ip dev interface
```

#### nmcli - network manager cli

```bash
A command-line tool for controlling NetworkManager.
Some subcommands such as nmcli monitor have their own usage documentation.
More information: https://networkmanager.dev/docs/api/latest/nmcli.html.

 - Run an nmcli subcommand:
   nmcli agent|connection|device|general|help|monitor|networking|radio command_options

 - Display the current version of NetworkManager:
   nmcli --version

 - Display help:
   nmcli --help

 - Display help for a subcommand:
   nmcli subcommand --help
```
#### routel

The routel script will list routes in a format that some might consider easier to interpret then the ip route list equivalent.

#### Example

Check the system is running the network:

```bash
[cloud_user@ip-10-0-1-172 ~]$ systemctl status NetworkManager
● NetworkManager.service - Network Manager
   Loaded: loaded (/usr/lib/systemd/system/NetworkManager.service; disabled; vendor preset: enabled)
   Active: active (running) since Mon 2024-07-22 14:03:00 EDT; 1h 18min ago
     Docs: man:NetworkManager(8)
  Process: 1227 ExecReload=/usr/bin/dbus-send --print-reply --system --type=method_call --dest=org.freedesktop.NetworkManager /org/freedesktop/NetworkManager org.freedesktop.NetworkManager.Reload uint32:0 (code=exited, status=0/SUCCESS)
 Main PID: 1207 (NetworkManager)
   CGroup: /system.slice/NetworkManager.service
           ├─1207 /usr/sbin/NetworkManager --no-daemon
           └─1231 /sbin/dhclient -d -q -sf /usr/libexec/nm-dhcp-helper -pf /var/run/dhclient-ens5.pid -lf /var/lib/NetworkManager/dhclient-8126c120-a964-e959-ff98-ac4973344505-ens5.lease ...

Jul 22 14:56:28 ip-10-0-1-172.ec2.internal dhclient[1231]: DHCPACK from 10.0.1.1 (xid=0x45cf9bf2)
Jul 22 14:56:28 ip-10-0-1-172.ec2.internal NetworkManager[1207]: <info>  [1721674588.0944] dhcp4 (ens5):   address 10.0.1.172
Jul 22 14:56:28 ip-10-0-1-172.ec2.internal NetworkManager[1207]: <info>  [1721674588.0944] dhcp4 (ens5):   plen 24 (255.255.255.0)
Jul 22 14:56:28 ip-10-0-1-172.ec2.internal NetworkManager[1207]: <info>  [1721674588.0945] dhcp4 (ens5):   gateway 10.0.1.1
Jul 22 14:56:28 ip-10-0-1-172.ec2.internal NetworkManager[1207]: <info>  [1721674588.0945] dhcp4 (ens5):   lease time 3600
Jul 22 14:56:28 ip-10-0-1-172.ec2.internal NetworkManager[1207]: <info>  [1721674588.0945] dhcp4 (ens5):   hostname 'ip-10-0-1-172'
Jul 22 14:56:28 ip-10-0-1-172.ec2.internal NetworkManager[1207]: <info>  [1721674588.0945] dhcp4 (ens5):   nameserver '10.0.0.2'
Jul 22 14:56:28 ip-10-0-1-172.ec2.internal NetworkManager[1207]: <info>  [1721674588.0945] dhcp4 (ens5):   domain name 'ec2.internal'
Jul 22 14:56:28 ip-10-0-1-172.ec2.internal NetworkManager[1207]: <info>  [1721674588.0945] dhcp4 (ens5): state changed bound -> bound
Jul 22 14:56:28 ip-10-0-1-172.ec2.internal dhclient[1231]: bound to 10.0.1.172 -- renewal in 1497 seconds.
```

check for active connections: 

```bash
[cloud_user@ip-10-0-1-172 ~]$ nmcli c show
NAME         UUID                                  TYPE      DEVICE
System ens5  8126c120-a964-e959-ff98-ac4973344505  ethernet  ens5
System eth0  5fb06bd0-0bb0-7ffb-45f1-d6edd65f3e03  ethernet  --
```

check the connection on that device:

```bash
[cloud_user@ip-10-0-1-172 ~]$ nmcli d show ens5
GENERAL.DEVICE:                         ens5
GENERAL.TYPE:                           ethernet
GENERAL.HWADDR:                         0E:C8:C6:B7:DE:09
GENERAL.MTU:                            9001
GENERAL.STATE:                          100 (connected)
GENERAL.CONNECTION:                     System ens5
GENERAL.CON-PATH:                       /org/freedesktop/NetworkManager/ActiveConnection/1
WIRED-PROPERTIES.CARRIER:               on
IP4.ADDRESS[1]:                         10.0.1.172/24
IP4.GATEWAY:                            10.0.1.1
IP4.ROUTE[1]:                           dst = 0.0.0.0/0, nh = 10.0.1.1, mt = 100
IP4.ROUTE[2]:                           dst = 0.0.0.0/0, nh = 10.0.1.1, mt = 0
IP4.ROUTE[3]:                           dst = 10.0.1.0/24, nh = 0.0.0.0, mt = 0
IP4.ROUTE[4]:                           dst = 169.254.0.0/16, nh = 0.0.0.0, mt = 1002
IP4.ROUTE[5]:                           dst = 10.0.1.0/24, nh = 0.0.0.0, mt = 100
IP4.DNS[1]:                             10.0.0.2
IP4.DOMAIN[1]:                          ec2.internal
IP6.ADDRESS[1]:                         fe80::cc8:c6ff:feb7:de09/64
IP6.GATEWAY:                            --
IP6.ROUTE[1]:                           dst = fe80::/64, nh = ::, mt = 256
IP6.ROUTE[2]:                           dst = ff00::/8, nh = ::, mt = 256, table=255
```
So all the data needed is:

```bash
IP Address: 10.0.1.172
Netmask: 24
Gateway: 10.0.1.1
DNS Server:  10.0.0.2
DNS Domain: ec2.internal
```


### Network topology

#### Basic network topology 

A **switch** is a device desined for local area networking, the switch is connected to a **router (gateway)**  and the router is connected to the internet (external network). Routers have a routing table, so they are able to communicate with other routers. Routers forward packages between networks. 

#### OSI layers

We’ll describe OSI layers “top down” from the application layer that directly serves the end user, down to the physical layer.

##### 7. Application Layer

The application layer is used by end-user software such as web browsers and email clients. It provides protocols that allow software to send and receive information and present meaningful data to users. A few examples of application layer protocols are the Hypertext Transfer Protocol (HTTP), File Transfer Protocol (FTP), Post Office Protocol (POP), Simple Mail Transfer Protocol (SMTP), and Domain Name System (DNS).

##### 6. Presentation Layer

The presentation layer prepares data for the application layer. It defines how two devices should encode, encrypt, and compress data so it is received correctly on the other end. The presentation layer takes any data transmitted by the application layer and prepares it for transmission over the session layer. Examples: TLS, SSL, MIME, JPEG, GIF.  

##### 5. Session Layer

The session layer creates communication channels, called sessions, between devices. It is responsible for opening sessions, ensuring they remain open and functional while data is being transferred, and closing them when communication ends. The session layer can also set checkpoints during a data transfer—if the session is interrupted, devices can resume data transfer from the last checkpoint. Examples: 
LDAP, NetBios, PPTP, RPC, SMB, SSL. 

##### 4. Transport Layer

The transport layer takes data transferred in the session layer and breaks it into “segments” on the transmitting end. It is responsible for reassembling the segments on the receiving end, turning it back into data that can be used by the session layer. The transport layer carries out flow control, sending data at a rate that matches the connection speed of the receiving device, and error control, checking if data was received incorrectly and if not, requesting it again. Examples: TCP, UDP, SPX, iSCSI

##### 3. Network Layer

The network layer has two main functions. One is breaking up segments into network packets, and reassembling the packets on the receiving end. The other is routing packets by discovering the best path across a physical network. The network layer uses network addresses (typically Internet Protocol addresses) to route packets to a destination node. Examples: IP, IPSec, ICMP, RIP. 

##### 2. Data Link Layer

The data link layer establishes and terminates a connection between two physically-connected nodes on a network. It breaks up packets into frames and sends them from source to destination. This layer is composed of two parts—Logical Link Control (LLC), which identifies network protocols, performs error checking and synchronizes frames, and Media Access Control (MAC) which uses MAC addresses to connect devices and define permissions to transmit and receive data. Examples: Ethernet, FrameRelay, WiFi, PPP, VLAN, MAC. 

##### 1. Physical Layer

The physical layer is responsible for the physical cable or wireless connection between network nodes. It defines the connector, the electrical cable or wireless technology connecting the devices, and is responsible for transmission of the raw data, which is simply a series of 0s and 1s, while taking care of bit rate control.

### What are alternatives to the OSI model?

Today, the main alternative to the Open Systems Interconnection (OSI) model is the TCP/IP model.

The TCP/IP model is comprised of five different layers:
 - The physical layer
 - The data link layer
 - The network layer
 - The transport layer
 - They application layer
   
While layers like the physical layer, network layer, and application layer appear to map directly to the OSI model, this isn’t quite the case. Instead, the TCP/IP model most accurately maps to the structure and protocols of the internet.

The OSI model remains a popular networking model to describe how networking operates from a holistic perspective for educational purposes. However, the TCP/IP model is now more commonly used in practice.

#### Anatomy of an IP address

References:
 - https://en.wikipedia.org/wiki/IP_address
 - https://en.wikipedia.org/wiki/Classless_Inter-Domain_Routing
 - https://en.wikibooks.org/wiki/A-level_Computing/AQA/Computer_Components,_The_Stored_Program_Concept_and_the_Internet/Structure_of_the_Internet/IP_addresses





### Network flow




## Machine level configuration

### Network interface

### Routing

### DNS




## Admin services and tools

### Firewalls

### Connection and troubleshooting




## Advanced user cases


### Port forwarding & redirection

### ssh tunneling 

### Proxy servers

### Load balancers

### VPN

### IDS



