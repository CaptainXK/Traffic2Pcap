#include <pkts_to_pcap.h>
#include <pcap.h>

void do_convert(const struct pp_hdr * pkts, const int pkts_nb)
{
  pcap_t *pd;
  pcap_dumper_t *pdumper;

  pd = pcap_open_dead(DLT_EN10MB, 65535);
  pdumper = pcap_dump_open(pd, "pp.pcap");

  struct pcap_pkthdr packet_header;
  struct timeval ts;

  packet_header.ts = ts;
  packet_header.caplen = 64;
  packet_header.len = 64;

	int i;

	for(i = pkts_nb - 1 ; i>=0; --i){
			pcap_dump((u_char*)pdumper, &packet_header, (const u_char*)&pkts[i]);
	}

  pcap_close(pd);
  pcap_dump_close(pdumper);


}
