#ifndef CONFIG_H
#define CONFIG_H

#include <string.h>

#define MAX_TRACE_NB 65535

struct pp_config{
	int is_default;
	int max_nb;
	char * file_path;	
};

void init_config(struct pp_config * conf);

#endif
