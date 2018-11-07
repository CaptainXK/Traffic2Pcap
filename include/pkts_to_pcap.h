#ifndef PKTS_TO_PCAP
#define PKTS_TO_PCAP

#include <pkt_hdr.h>

void do_convert(const struct pp_hdr * pkts, const int pkts_nb);

#endif
