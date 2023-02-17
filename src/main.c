#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>

#define MKENV_VERSION "1.1.0"
#define MAX_ENV_FILE_LEN 100

void usage(FILE *stream)
{
    fprintf(stream, "mkenv %s\n", MKENV_VERSION);
    fprintf(stream, "A utility for setting .env files based on environment\n\n");
    fprintf(stream, "USAGE:\n");
    fprintf(stream, "\tmkenv [cmd] [environment]\n\n");
    fprintf(stream, "ARGS:\n");
    fprintf(stream, "\t<environment>\tthe .env.[environment] specified for the command\n\n");
    fprintf(stream, "COMMANDS:\n");
    fprintf(stream, "\tset\tset the current `.env` file to the contents of `.env.environment`\n");
    fprintf(stream, "\tshow\tshow the currently active environment.  Equivalent to `cat .env`");
}

void set(const char *env)
{
    // Dear reddit C programmers, yes this is deeply naive, and libc is
    // evil, and I'm doing this in userspace, but you know what, fuck off I'm
    // trying to get something done.

    size_t env_len = strlen(".env.") + 1;
    size_t env_name_len_max = MAX_ENV_FILE_LEN - env_len;
    size_t env_name_len = strlen(env) + 1;

    if (env_name_len > env_name_len_max) {
        fprintf(stderr, "Environment file names larger than %d are not supported\n", MAX_ENV_FILE_LEN);
        exit(1);
    }

    static char env_buffer[MAX_ENV_FILE_LEN];
    strlcpy(env_buffer, ".env.", MAX_ENV_FILE_LEN);
    strlcat(env_buffer, env, MAX_ENV_FILE_LEN); // env_buffer will be null-terminated after strlpy

    FILE *src;
    if ((src = fopen(env_buffer, "r")) == NULL) {
        fprintf(stderr, "ERROR: %s '%s'\n", strerror(errno), env_buffer);
        exit(1);
    }

    FILE *dest;
    if ((dest = fopen(".env", "w")) == NULL) {
        fprintf(stderr, "ERROR: %s\n", strerror(errno));
        exit(1);
    }

    int c, i;
    c = i = 0;
    while ((c = fgetc(src)) != EOF) {
        if (fputc(c, dest) == EOF) {
            fprintf(stderr, "ERROR: could not write to %s\n", env_buffer);
            exit(1);
        }
        i++;
    }

    printf("Wrote %d bytes. Set current environment to %s\n", i, env_buffer);
}

void show_env()
{
    FILE *f;
    if ((f = fopen(".env", "r")) == NULL) {
        fprintf(stderr, "ERROR: %s\n", strerror(errno));
        exit(1);
    }

    int c;
    while ((c = fgetc(f)) != EOF) {
        putc(c, stdout);
    }
}

int main(int argc, const char **argv)
{
    if (argc < 2) {
        usage(stderr);
        exit(1);
    }

    const char *cmd = argv[1];
    if (strcmp(cmd, "set") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Required positional argument [environment] not set.\n");
            exit(1);
        }

        const char *env = argv[2];
        set(env);
    } else if (strcmp(cmd, "show") == 0) {
        show_env();
    } else {
        fprintf(stderr, "Invalid command %s.  Valid commands: set, show.\n", cmd);
        exit(1);
    }

    return 0;
}
