#include <stdio.h>
#include <unistd.h>
#include "sijimi.h"

char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[])(char **) = {
    &sijimi_cd,
    &sijimi_help,
    &sijimi_exit
};

int sijimi_cd(char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "cd: path is required");
        return 1;
    }
    if (chdir(args[1]) != 0) {
        perror("sijimi");
    }
    return 1;
}

int sijimi_help(char **args)
{
    printf("Use the man command for information on other programs.\n");
    return 1;
}

int sijimi_exit(char **args)
{
    return 0;
}

int sijimi_num_builtins()
{
    return sizeof(builtin_str) / sizeof(char *);
}