#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sijimi.h"


int main(int argc, char **argv[])
{
    sijimi_loop();
}


void sijimi_loop(void)
{
    char *line;
    char **args;
    int status;

    do {
        printf(">");
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

        status = sijimi_execute(args);

        free(line);
        free(args);
    } while (status);
}
