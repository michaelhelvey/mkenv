#ifndef MKENV_ARGS_H
#define MKENV_ARGS_H

typedef enum {
	CMD_SHOW,
	CMD_SET,
	CMD_HELP,
	CMD_INVALID,	
} cmd_type;

typedef enum {
	PARSE_ERR_NONE,
	PARSE_ERR_INVALID_ARG_NUM,
} cmd_parse_err;

/* command definition */
typedef struct {
	cmd_type type;
	int arg_num;
} cmd_def_t;

/* application configuration */
typedef struct {
	int supported_cmd_num;
	cmd_def_t *commands;
	int args_given;
	char **argv;
} application_config_t;

application_config_t *init_config();

void free_config(application_config_t *config);

/* parses a string into a cmd_type */
cmd_type parse_cmd_type(char *arg);

/* parses a cmd_type into a descriptive string */
const char *cmd_type_to_str(cmd_type type);

cmd_parse_err parse_args(application_config_t *config, cmd_def_t given_cmd);

#endif 
