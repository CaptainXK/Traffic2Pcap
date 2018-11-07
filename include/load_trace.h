#ifndef TLOAD_H
#define TLOAD_H

#include <stdio.h>
#include <pkt_hdr.h>

#define INVALID_LINE -1
#define END_LINE 0
#define VALID_LINE 1

#define NB_FIELD 7

#ifdef __cplusplus
extern "C"{
#endif

/*
* load trace to pkts array
*/
int load_pp_trace(const char * trace_file, struct pp_hdr * pkts, const int max_nb);

/*
* load one and parse on line in trace file before store
*/
int load_one_pp_trace(FILE *fp, struct pp_hdr * pkts);

/*
* load default trace
*/
int load_default_trace(struct pp_hdr * pkts, const int trace_nb);
#ifdef __cplusplus
}
#endif

#endif
