#ifndef PARSE_CMD_H
#define PARSE_CMD_H

#include <unistd.h>
#include <config.h>
#include <pkt_hdr.h>

void parse_pp_cmd(int argc , char ** argv, struct pp_config * pp_conf); 

#endif

