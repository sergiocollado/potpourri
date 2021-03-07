# Notes on linux inner workings

## Linux networking basics

### Switches
 to connect two computers a switch is needed. (A switch can only serve communication within a network)
 
 To see the interfaces, 
 
```
ip link
```

**ip link** is to display and modify interfaces n a linux host.

if the switch has for example the ip: 192.168.1.0. and the computers (A and B)to communicate have the ips. 192.168.1.10 (A)  and 192.168.1.11 (B) 

we add both ip computers with:

**ip addr** is to display the ips of the interfaces, adn **ip addr add** to add ip addresses to the network interfaces.

```
ip addr add 192.168.1.10/24 dev eth0
```

```
ip addr add 192.168.1.11/24 dev eth0
```

### Routing

For connceting different networks a router in needed. Like the router connects with two networks it has two ip addresses assinged, one in each network.

Imaging another network wit a switch (192.168.2.0) and two computers C (192.168.2.10) and D(192.168.2.11). How can system A communicate with C?

In the first network the router has the ip: 192.168.1.1 and in the second network it is identified with the ip: 192.168.2.1

So to communicate between the networks the **gateway** must be defined:

To display the existing routing configuration in a system, use the **route** command

```
route
```

This will display the kernel's routing table.

The **route** or **ip route** command display the routing table

To configure a gateway, so a computer can reach another computer in another network, use the command: **ip route add**

```
ip route add 192.168.2.0/24 via 192.168.1.1
```
- 192.168.1.1 would be the address of the router
- 192.168.2.0/24 would be the range of addresses requested to be accessed through the router

Other example, one of the computers, need to reach an address in the internet (172.217.194.0), you ask to route to that address through the router

```
ip route add 172.217.194.0/24 via 192.168.1.1
```

For not having to define all the ips, outside the own networ, a default policy can be defined:

```
ip route add default via 192.168.2.1
```

or intead of default, it can be defined also as 0.0.0.0, this means any destination


### How to set a linux host a router (fordwarding packets in a linux host)

By default in linux, packets are not forwarded from one interface to the next. 

Wether a host can fordward packets between interfaces is defined in a setting in the system, at the file:

```
/proc/sys/net/ipv4/ip_fordward
```

by default, the value in this file, is set to 0, that states for **not fordward**. 

if you set this value to one, the system will allow fordwarding packets from one interface to other.

```
echo 1 > /proc/sys/net/ipv4/ip_fordward
```

Only setting this value, will not persist in case the system is rebooted, or turned off. For that you must modify this value in:

```
in the file: /etc/sysctl.conf
net.ipv4.ip_fordward = 1
```









