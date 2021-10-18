#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include "sijimi.h"

ENV *initialize_sijimi(ENV *env);
void sijimi_loop(void);

int main(int argc, char **argv[])
{
    sijimi_loop();
    return 0;
}

void sijimi_loop(void)
{
    char *line;
    char **args;
    int status;
    ENV *env = malloc(sizeof(ENV));

    initialize_sijimi(env);

    do {
        printf("%s@%s$ ", env->user, env->cwd);

        line = sijimi_read_line();
        if (line == NULL) {
            fprintf(stderr, "sijimi_read_line: return NULL");
            break;
        }

        args = sijimi_split_line(line);
        if (args == NULL) {
            fprintf(stderr, "sijimi_split_line: return NULL");
            break;
        }

        status = sijimi_execute(env, args);

        free(line);
        free(args);
    } while (status);
}

ENV *initialize_sijimi(ENV *env)
{
    int pwd_buf_size, user_buf_size;
    char *pwd_buf, *user_buf, *pwd, *user;
    uid_t uid = getuid();
    struct passwd *user_data = getpwuid(uid);

    if ((pwd = getenv("PWD")) != NULL) {
        pwd_buf_size = strlen(pwd);
        pwd_buf = malloc(sizeof(char) * pwd_buf_size);
        strcpy(pwd_buf, pwd);
    }
    user_buf = malloc(sizeof(char) * strlen(user_data->pw_name));

    strcpy(user_buf, user_data->pw_name);

    env->cwd = pwd_buf;
    env->user = user_buf;

    return env;
}