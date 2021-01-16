#include <stdlib.h>
#include <string.h>

#include "args.h"


cmd_type parse_cmd_type(char *arg)
{
	if (strcmp(arg, "show") == 0) {
		return CMD_SHOW;
	} else if (strcmp(arg, "set") == 0) {
		return CMD_SET;
	} else if (strcmp(arg, "--help") == 0) {
		return CMD_HELP;
	} else {
		return CMD_INVALID;
	}
}

const char *cmd_type_to_str(cmd_type type)
{
	switch(type) {
		case CMD_SHOW:
			return "CMD_SHOW";
		case CMD_SET:
			return "CMD_SET";
		case CMD_HELP:
			return "CMD_HELP";
		case CMD_INVALID:
			return "CMD_INVALID"; 
	}
	return "Unknown type";
}

application_config_t *init_config()
{
	return (application_config_t *)malloc(sizeof(application_config_t));
}

void free_config(application_config_t *config)
{
	free(config);
}

cmd_parse_err parse_args(application_config_t *config, cmd_def_t given_cmd)
{
	if (config->args_given != given_cmd.arg_num) {
		return PARSE_ERR_INVALID_ARG_NUM;
	}
	return PARSE_ERR_NONE;
}
