       #define _GNU_SOURCE     /* To get defns of NI_MAXSERV and NI_MAXHOST */
       #include <arpa/inet.h>
       #include <sys/socket.h>
       #include <netdb.h>
       #include <ifaddrs.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <unistd.h>
       #include <linux/if_link.h>

       int main(int argc, char *argv[])
       {
           struct ifaddrs *ifaddr;
           int family, s;
           char host[NI_MAXHOST];

           if (getifaddrs(&ifaddr) == -1) {
               perror("getifaddrs");
               exit(EXIT_FAILURE);
           }

           /* Walk through linked list, maintaining head pointer so we
              can free list later. */

           for (struct ifaddrs *ifa = ifaddr; ifa != NULL;
                    ifa = ifa->ifa_next) {
               if (ifa->ifa_addr == NULL)
                   continue;

               family = ifa->ifa_addr->sa_family;

               /* Display interface name and family (including symbolic
                  form of the latter for the common families). */

               printf("%-8s %s (%d)\n",
                      ifa->ifa_name,
                      (family == AF_PACKET) ? "AF_PACKET" :
                      (family == AF_INET) ? "AF_INET" :
                      (family == AF_INET6) ? "AF_INET6" : "???",
                      family);

               /* For an AF_INET* interface address, display the address. */

               if (family == AF_INET || family == AF_INET6) {
                   s = getnameinfo(ifa->ifa_addr,
                           (family == AF_INET) ? sizeof(struct sockaddr_in) :
                                                 sizeof(struct sockaddr_in6),
                           host, NI_MAXHOST,
                           NULL, 0, NI_NUMERICHOST);
                   if (s != 0) {
                       printf("getnameinfo() failed: %s\n", gai_strerror(s));
                       exit(EXIT_FAILURE);
                   }

                   printf("\t\taddress: <%s>\n", host);

               } else if (family == AF_PACKET && ifa->ifa_data != NULL) {
                   struct rtnl_link_stats *stats = (rtnl_link_stats*)ifa->ifa_data;

                   printf("\t\ttx_packets = %10u; rx_packets = %10u\n"
                          "\t\ttx_bytes   = %10u; rx_bytes   = %10u\n",
                          stats->tx_packets, stats->rx_packets,
                          stats->tx_bytes, stats->rx_bytes);
               }
           }

           freeifaddrs(ifaddr);
           exit(EXIT_SUCCESS);
       }

/** Sample output
lo       AF_PACKET (17)
		tx_packets =        123; rx_packets =        123
		tx_bytes   =       7185; rx_bytes   =       7185
eth0     AF_PACKET (17)
		tx_packets =    1110120; rx_packets =    1263345
		tx_bytes   =  933902637; rx_bytes   =  187065645
eth1     AF_PACKET (17)
		tx_packets =        608; rx_packets =        600
		tx_bytes   =      25932; rx_bytes   =      27698
lo       AF_INET (2)
		address: <127.0.0.1>
eth0     AF_INET (2)
		address: <173.203.57.63>
eth1     AF_INET (2)
		address: <10.179.70.43>
lo       AF_INET6 (10)
		address: <::1>
eth0     AF_INET6 (10)
		address: <2001:4801:7800:29:4240:e7ff:feb0:e62f>
eth0     AF_INET6 (10)
		address: <fe80::4240:e7ff:feb0:e62f%eth0>
eth1     AF_INET6 (10)
		address: <fe80::4240:39ff:feff:276e%eth1>
**/ 
