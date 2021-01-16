#ifndef MKENV_FILE_H
#define MKENV_FILE_H

#define MKENV_ENV_MAX_LEN 100

void get_current_env(char *env);

void set_current_env_state(char *env);

void copy_file(char *src, char *dest);

#endif
