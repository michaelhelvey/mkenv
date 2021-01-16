#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

void copy_file(char *src, char *dest)
{

	FILE *src_file;
	FILE *dest_file;

	if ((src_file = fopen(src, "r")) == NULL) {
		fprintf(stderr, "Could not open %s\n", src);
		exit(1);
	}
	if ((dest_file = fopen(dest, "w+")) == NULL) {
		perror("Could not open dest");
		exit(1);
	}

	int c;
	while((c = fgetc(src_file)) != EOF) {
		fputc(c, dest_file);
	}

	fclose(src_file);
	fclose(dest_file);
}

void get_current_env(char *env)
{
	// we assume that the user of the program will create a mkenv file
	FILE *state_file;
	if ((state_file = fopen(".mkenv", "r")) == NULL) {
		perror("Could not open .mkenv file");
		exit(1);
	}
	fgets(env, MKENV_ENV_MAX_LEN, state_file);
	if (strlen(env) == 0) {
		printf("Invalid .mkenv file: empty contents.\n");
		exit(1);
	}
	fclose(state_file);
}

void set_current_env_state(char *env)
{
	FILE *state_file;
	if ((state_file = fopen(".mkenv", "w+")) == NULL) {
		perror("Could not open .mkenv file");
		exit(1);
	}
	fputs(env, state_file);
	fputs("\n", state_file);
	fclose(state_file);
}
