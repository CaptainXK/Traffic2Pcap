#include <stdio.h>
#include <stdlib.h>
#include <pkt_hdr.h>
#include <load_trace.h>
#include <limits.h>//USHRT_MAX
#include <string.h>//bzero
#include <parse_pp_cmd.h>
#include <config.h>
#include <pkts_to_pcap.h>

#define NB_PKT 65535
#define PKT_SIZE 64

struct pp_hdr pkts[NB_PKT];
struct pp_config cur_conf;

int main(int argc, char ** argv)
{

	int ret;

	//init conif	
	init_config(&cur_conf);

	//parse args
	parse_pp_cmd(argc, argv, &cur_conf);

	//do load default trace
	if(cur_conf.is_default == 1){
		ret = load_default_trace(pkts, NB_PKT);
		printf("Default trace : load %d lines\n", ret);
	}
	//load trace from file
	else{
		ret = load_pp_trace(cur_conf.file_path, pkts, NB_PKT);
		printf("PP trace : load %d lines\n", ret);
	}	

	//convert to pcap
	do_convert(pkts, ret);

	return 0;
}
