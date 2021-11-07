#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "sijimi.h"

int launch(ENV *env, line *command_line, int i);
int exec_builtin_cmd(ENV *env, char **block_array);
int redirect(ENV *env, line *command_line, int th_of_command, char **block_array);
int pipe_command(ENV *env, line *command_line, int th_of_command, char **block_array);
int is_text(char *filename);

int execute(ENV *env, line *command_line)
{
    int i, status, ret;
    pid_t pid, wpid;


    if (command_line == NULL) {
        fprintf(stderr, "Input Value Error\n");
        return 1;
    }

    pid = fork();

    if (pid == 0) {
        // child process
        ret = launch(env, command_line, 0);
    } else if (pid > 0) {
        // parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return ret;
}

// 再起的にパイプを処理する
int launch(ENV *env, line *command_line, int th_of_command)
{
    char **block_array = block_to_array(&command_line->blk);

    // リダイレクト
    if (command_line->redirect_flg == 1) {
        if (redirect(env, command_line,th_of_command, block_array) < 0) {
            fprintf(stderr, "redirect error\n");
        }
    }

    if (th_of_command == num_of_block(command_line) - 1) {
        if (exec_builtin_cmd(env, block_array) >= 0) {
            return 1;
        }

        if (execvp(block_array[0], block_array) < 0) {
            fprintf(stderr, "execute command error\n");
            return -1;
        }

        return 1;
    }

    if (pipe_command(env, command_line, th_of_command, block_array) < 0) {
        fprintf(stderr, "pipe error");
        return -1;
    }

    return 1;
}


int exec_builtin_cmd(ENV *env, char **block_array)
{
    for (int i = 0; i < sijimi_num_builtins(); i++) {
        if (strcmp(block_array[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(env, block_array);
        }
    }
    return -1;
}

int pipe_command(ENV *env, line *command_line, int th_of_command, char **block_array)
{
    pid_t pid;
    int status, pp[2] = {};

    pipe(pp);
    pid = fork();
    if (pid == 0) {
        // child process

        close(pp[0]);
    
        // 標準出力をパイプの書き込み口につなぐ
        dup2(pp[1], 1);
        close(pp[1]);

        launch(env, command_line->next_line, th_of_command+1);
    }
    if (pid < 0) {
        // fork error
        fprintf(stderr, "fork error\n");
    }
    if (pid > 0) {
        // parent process

        close(pp[1]);
        
        // 標準入力をパイプの読み出し口につなぐ        
        dup2(pp[0], 0);
        close(pp[0]);

        if (exec_builtin_cmd(env, block_array) >= 0) {
            fprintf(stderr, "execution error\n");
            return -1;
        }
        
        if (execvp(block_array[0], block_array) < 0) {
            fprintf(stderr, "execution error\n");
            return -1;
        }
    }
    return 1;
}

int redirect(ENV *env, line *command_line, int th_of_command, char **block_array)
{
    int token_num, fd;
    char *filename;
    FILE *file;

    token_num = num_of_token(&command_line->blk);

    if (is_text(block_array[token_num-1]) == 0) {
        return -1;
    }

    filename = block_array[token_num-1];
    block_array[token_num-1] = NULL;

    if ((file = fopen(filename, "r"))) {
        if (remove(filename) != 0) {
            return -1;
        }
    }

    fd = open(filename, O_CREAT | O_RDWR, 0666);

    // オープンしたファイルのディスクリプたを標準出力に複製する
    dup2(fd, 1);
    close(fd);

    return 1;
}

int is_text(char *filename)
{
    if (strncmp(filename+(strlen(filename) - 4), ".txt", 4) == 0) {
        return 1;
    }
    return 0;
}