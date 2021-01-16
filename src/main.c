#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "args.h"

#define NUM_SUPPORTED_CMDS 3

#define ASSERT_NOT_REACHED() assert(0 && "This should never be reached")

/**
 * mkenv is a script for managing .env files
 * Supported commands:
 * `mkenv show` - show what environment is currently active
 * `mkenv set <env>` - set the `.env` file from the contents of `.env.<env>`
 * `mkenv --help` - show the usage of mkenv
 */

void print_usage()
{
	printf(
		"Usage:\n\t%s\n\n\t%s\n\t%s\n\t%s\n", 
		"mkenv [cmd] [args...]", 
		"show\t\tdisplay currently active environment", 
		"set [env]\tset .env file to [env]", 
		"--help\t\tdisplay usage information"
	);
}

// @NiceToHave: variable argument list for the first printf
void print_error(const char *error)
{
	printf("ERROR: %s\n", error);
	print_usage();
}

void do_set(char* env)
{
	assert(env && "do_set requires one non NULL environment argument");	
	printf("doing set for env: %s\n", env);
}

void do_help()
{
	print_usage();
}

void do_show()
{
	printf("calling do_show\n");
}

void call_command(cmd_type type, char **argv)
{
	switch (type) {
		case CMD_HELP:
			do_help();
			break;
		case CMD_SHOW:
			do_show();
			break;
		case CMD_SET:
			do_set(argv[0]);
			break;
		case CMD_INVALID:
			ASSERT_NOT_REACHED();
	}
}

cmd_def_t cmd_for_type(cmd_type type, int num_commands, cmd_def_t *commands)
{
	for (int i = 0; i < num_commands; i++) {
		if (commands[i].type == type) {
			return commands[i];
		}
	}
	ASSERT_NOT_REACHED();
}

int main(int argc, char **argv)
{
	int exit_code = 0;

	// 1. define what commands we support
	cmd_def_t show_command = {CMD_SHOW, 0};
	cmd_def_t help_command = {CMD_HELP, 0};
	cmd_def_t set_command = {CMD_SET, 1};

	cmd_def_t commands[NUM_SUPPORTED_CMDS] = {show_command, set_command, help_command};

	// 2. figure out what command the user wants to run
	cmd_type ct = parse_cmd_type(*(++argv));
	// 3. create an application configuration with the information we have
	application_config_t *config = init_config();
	config->supported_cmd_num = NUM_SUPPORTED_CMDS;
	config->commands = commands;
	config->args_given = argc - 2;
	/* all args after argv[1] */
	config->argv = ++argv;

	// 4. validate that the application configuration matches the information
	// given us.
	if (ct == CMD_INVALID) {
		print_error("Invalid command");
		free_config(config);
		exit(1);
	}

	cmd_def_t given_cmd = cmd_for_type(ct, NUM_SUPPORTED_CMDS, commands);
	cmd_parse_err err = parse_args(config, given_cmd);

	if (err == PARSE_ERR_NONE) {
		// Run the command
		call_command(ct, argv);
	} else if (err == PARSE_ERR_INVALID_ARG_NUM) {
		print_error("Invalid number of arguments for commands");
		exit_code = 1;
	} else {
		print_error("Unhandled parse error");
		exit_code = 1;
	}

	free_config(config);
	exit(exit_code);
}
