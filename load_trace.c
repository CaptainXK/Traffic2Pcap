#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>
#include <load_trace.h>

#define DEBUG_PKT 0

int load_one_trace(FILE *fp, struct pp_hdr * pkt);

uint32_t pkt_length = 64;

int load_pp_trace(const char *  trace_file, struct pp_hdr * pkts, const int max_nb)
{
	assert(pkts != NULL);
	
	FILE * file;
	int trace_cnt = 0;
	int pos = 0;
	int ret = 0;
	
	file = fopen(trace_file, "r");
	assert( file != NULL);

	while(trace_cnt < max_nb){
		ret = load_one_trace(file, (pkts + (pos++)) );

		if(ret == VALID_LINE){
			trace_cnt++;
		}
		else{
			break;
		}
	}

	return trace_cnt;	

}

int load_one_trace(FILE *fp, struct pp_hdr * pkt)
{
	//read one packet
  int j, k;

	//pp bench sender
	//read fields_nb and packets_nb
	static int nFields = 0;
	static int nPackets = 0;
	static uint32_t pkt_id = 1;
	
	if(nFields == 0 && nPackets ==0){
		assert(fscanf(fp, "%d %d", &nFields, &nPackets));
	}
	
	//check eof
	if(feof(fp))
		return END_LINE;

	int payload_pos = 0;
	uint8_t* cur_byte;
	uint32_t cur_field;

#if DEBUG_PKT
	printf("Current line:");
#endif

	for(j = 0, payload_pos = 0; j < nFields; ++j, payload_pos += 4){
		//read one 4Bytes data
		if(fscanf(fp, "%x", &cur_field) == EOF)
			return END_LINE;
		
		//put into payload one by one
		//little end order, so start from last byte in uint32_t data
		cur_byte = (uint8_t*)(&cur_field);
		for(k = 3; k>=0; --k){
			pkt->payload[payload_pos + k] = *(cur_byte+k);
#if DEBUG_PKT
			printf("%x", pkt->payload[payload_pos + k]);
#endif
		}	
	}
	
#if DEBUG_PKT
	printf("\n");		
#endif
	//set packet id
	pkt->id = pkt_id++;
	
	pkt->action = 0;

	//set ether type to pass NIC hardware check, otherwise can not receive packets as expected	
	pkt->eth.ether_type = (uint16_t)(pkt_length - sizeof(struct ether_hdr));
	
	return VALID_LINE;
}

#define DEF_PKT_SIZE 64

int load_default_trace(struct pp_hdr * pkts, const int trace_nb)
{
	int i;

	for(i = 0 ; i < trace_nb; ++i){
		//zero dst and src mac
		bzero(&pkts[i].eth.d_addr, sizeof(pkts[i].eth.d_addr));			
		bzero(&pkts[i].eth.s_addr, sizeof(pkts[i].eth.s_addr));			
		
		pkts[i].eth.ether_type = DEF_PKT_SIZE - sizeof(struct ether_hdr);
		fill_pp_hdr(&pkts[i], (uint32_t)i, (uint32_t)i);
	}

	return i;
}
