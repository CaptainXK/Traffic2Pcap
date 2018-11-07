#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <pkt_hdr.h>
#include <limits.h>//USHRT_MAX
#include <string.h>//bzero

#define NB_PKT 1024
#define LINKTYPE_ETHERNET 1
#define TCPDUMP_MAGIC	0xa1b2c3d4
#define PKT_SIZE 64

void fill_pp_hdr(struct pp_hdr * _pp_hdr, uint32_t _action, uint32_t _id)
{
	for(uint32_t i=0; i < 32; i++){
		_pp_hdr->payload[i] = i;
	}

	_pp_hdr->action = _action;
	_pp_hdr->id = _id;
}

int main() {
  pcap_t *pd;
  pcap_dumper_t *pdumper;

  pd = pcap_open_dead(DLT_EN10MB, 65535);
  pdumper = pcap_dump_open(pd, "pp.pcap");

  struct pcap_pkthdr packet_header;
  struct timeval ts;

  packet_header.ts = ts;
  packet_header.caplen = 64;
  packet_header.len = 64;

  struct pp_hdr cur_pp_hdr[NB_PKT];
	int i;

	for(i = NB_PKT - 1 ; i>=0; --i){
		//zero dst and src mac
		bzero(&cur_pp_hdr[i].eth.d_addr, sizeof(cur_pp_hdr[i].eth.d_addr));			
		bzero(&cur_pp_hdr[i].eth.s_addr, sizeof(cur_pp_hdr[i].eth.s_addr));			
		
		cur_pp_hdr[i].eth.ether_type = PKT_SIZE - sizeof(struct ether_hdr);
		fill_pp_hdr(&cur_pp_hdr[i], (uint32_t)i, (uint32_t)i);
	}
	
	for(i = NB_PKT - 1 ; i>=0; --i){
			pcap_dump((u_char*)pdumper, &packet_header, (const u_char*)&cur_pp_hdr[i]);
	}

  pcap_close(pd);
  pcap_dump_close(pdumper);

	return 0;
}
