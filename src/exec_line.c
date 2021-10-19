#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "sijimi.h"

int sijimi_launch(ENV *env, line *command_line, int i);

int sijimi_execute(ENV *env, line *command_line)
{
    int i, status;
    pid_t pid, wpid;


    if (command_line == NULL) {
        fprintf(stderr, "Input Value Error\n");
        return 1;
    }

    // for (i = 0; i < sijimi_num_builtins(); i++) {
    //     if (strcmp(args[0], builtin_str[i]) == 0) {
    //         return (*builtin_func[i])(env, args);
    //     }
    // }

    pid = fork();

    if (pid == 0) {
        // child process
        sijimi_launch(env, command_line, 0);
    } else if (pid > 0) {
        // parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }

}

// 再起的にパイプを処理する
int sijimi_launch(ENV *env, line *command_line, int i)
{
    pid_t pid;
    int status, pp[2] = {};
    char **block_array = block_to_array(&command_line->blk);

    printf("num of block: %d\n", num_of_block(command_line));

    if (i == num_of_block(command_line) - 1) {
        execvp(block_array[0], block_array);
        return;
    }

    pipe(pp);
    pid = fork();
    if (pid == 0) {
        // child process
        close(pp[0]);
        dup2(pp[1], 1);
        close(pp[1]);

        sijimi_launch(env, command_line->next_line, i+1);
    }
    if (pid < 0) {
        // fork error
        perror("sijimi");
    }
    if (pid > 0) {
        // parent process
        close(pp[1]);
        dup2(pp[0], 0);
        close(pp[0]);
        
        execvp(block_array[0], block_array);
    }
    return 1;
}
