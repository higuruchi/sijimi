#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <signal.h>
#include <sysexits.h>
#include "sijimi.h"

ENV *initialize_sijimi(ENV *env);
void abrt_handler(int);
void sijimi_loop(void);

int main(int argc, char **argv)
{
    sijimi_loop();
    return 0;
}


void sijimi_loop(void)
{
    char *input_line;
    line *command_line;
    int status;
    ENV *env = malloc(sizeof(ENV));

    initialize_sijimi(env);

    puts("hello! this is sijimi");
    puts("please input command!");

    do {
        printf("%s@%s$ ", env->user, env->cwd);

        input_line = read_line();

        if (signal(SIGINT, abrt_handler) == SIG_ERR) {
            exit(1);
        }

        if (input_line == NULL) {
            fprintf(stderr, "read_line: return NULL\n");
            break;
        }

        command_line = split_line(input_line);
        if (command_line == NULL) {
            fprintf(stderr, "split_line: return NULL\n");
            continue;
        }

        status = execute(env, command_line);
        if (status < 0) {
            fprintf(stderr, "execution error\n");
            free(command_line);
            free(input_line);
            continue;
        }

        free(command_line);
        free(input_line);
    } while (1);
}

ENV *initialize_sijimi(ENV *env)
{
    char *pwd_buf, *user_buf, *home_buf, *pwd, *user;
    uid_t uid = getuid();
    struct passwd *user_data = getpwuid(uid);

    pwd = getcwd(NULL, 0);

    user_buf = malloc(sizeof(char) * strlen(user_data->pw_name) + 1);
    pwd_buf = malloc(sizeof(char) * strlen(pwd) + 1);
    home_buf = malloc(sizeof(char) * strlen(user_data->pw_dir) + 1);

    strcpy(user_buf, user_data->pw_name);
    strcpy(pwd_buf, pwd);
    strcpy(home_buf, user_data->pw_dir);

    env->cwd = pwd_buf;
    env->user = user_buf;
    env->home = home_buf;

    free(pwd);
    // free(user_data);

    return env;
}

void abrt_handler(int sig) {
    puts("Bye");
    exit(1);
}


// int initialize_env() {

// }