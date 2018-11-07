#ifndef NDN_H
#define NDN_H

#include <unistd.h>
#include <inttypes.h>

#define ETHER_ADDR_LEN 6

struct ether_addr {
  uint8_t addr_bytes[ETHER_ADDR_LEN]; 
} __attribute__((__packed__));

struct ether_hdr {
	struct ether_addr d_addr; 
  struct ether_addr s_addr; 
  uint16_t ether_type;      
} __attribute__((__packed__));

struct pp_hdr{
	struct ether_hdr eth;//14
  uint8_t payload[32];//32
	uint32_t action;//4
	uint32_t id;//4
}__attribute__((__packed__));// size = 14 + 32 + 4 + 4 = 54

#endif
