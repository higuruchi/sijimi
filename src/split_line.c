#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TOKEN_BUFSIZE 64
#define TOKEN_DELIM " \t\r\n\a"

char **sijimi_split_line(char *line)
{
    int bufsize = TOKEN_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (tokens == NULL) {
        fprintf(stderr, "malloc: allocation error\n");
        return NULL;
    }
    token = strtok(line, TOKEN_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += TOKEN_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (tokens == NULL) {
                fprintf(stderr, "realloc: allocation error\n");
                return NULL;
            }
        }
        token = strtok(NULL, TOKEN_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}