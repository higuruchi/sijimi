#include <stdio.h>

char *sijimi_read_line(void)
{
    char *line = NULL;
    ssize_t bufsize = 0;

    if (getline(&line, &bufsize, stdin) == -1) {
        if (feof(stdin)) {
            return NULL;
        }
        fprintf(stderr, "getline: error");
        return NULL;
    }
    return line;
}