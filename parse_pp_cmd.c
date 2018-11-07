#include <parse_pp_cmd.h>
#include <stdio.h>
#include <stdlib.h>

void usage()
{
	printf("Usage:\n");
	printf("\t-f: pp trace file\n");

	exit(0);
}

void parse_pp_cmd(int argc , char ** argv, struct pp_config * pp_conf)
{
	int opt;

	//no cmd means default mode
	if(argc == 1){
		printf("[Default mode]\n");
		pp_conf->is_default = 1;
		return;
	}

	while(( opt = getopt(argc, argv, "f:h")) != -1){
		switch(opt){
			case 'f':
				pp_conf->file_path = strdup(optarg);
				pp_conf->is_default = 0;
				break;
			case 'h':
			default:
				usage();
				break;
		}
	}

	return;		
}
