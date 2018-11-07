#include <config.h>

void init_config(struct pp_config * conf)
{
	conf->is_default = 1;
	conf->max_nb = 65535;
	conf->file_path = NULL;
}
