#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "sijimi.h"

int sijimi_execute(ENV *env, char **args)
{
    int i;

    if (*args == NULL) {
        return 1;
    }

    for (i = 0; i < sijimi_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(env, args);
        }
    }

    return sijimi_launch(env, args);
}

int sijimi_launch(ENV *env, char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // child process
        if (execvp(args[0], args) == -1) {
            perror("sijimi");
        }
    }
    if (pid < 0) {
        // fork error
        perror("sijimi");
    }
    if (pid > 0) {
        // parent process

        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}
