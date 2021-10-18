#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sijimi.h"

char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[])(ENV *, char **) = {
    &sijimi_cd,
    &sijimi_help,
    &sijimi_exit
};

int sijimi_cd(ENV *env, char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "cd: path is required");
        return 1;
    }
    if (chdir(args[1]) != 0) {
        perror("sijimi");
    }
    free(env->cwd);
    env->cwd = getcwd(NULL, 0);
    return 1;
}

int sijimi_help(ENV *env, char **args)
{
    printf("Use the man command for information on other programs.\n");
    return 1;
}

int sijimi_exit(ENV *env, char **args)
{
    return 0;
}

int sijimi_num_builtins()
{
    return sizeof(builtin_str) / sizeof(char *);
}