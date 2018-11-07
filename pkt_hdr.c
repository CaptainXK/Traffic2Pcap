#include <pkt_hdr.h>

void fill_pp_hdr(struct pp_hdr * _pp_hdr, uint32_t _action, uint32_t _id)
{
	for(uint32_t i=0; i < 32; i++){
		_pp_hdr->payload[i] = i;
	}

	_pp_hdr->action = _action;
	_pp_hdr->id = _id;
}
