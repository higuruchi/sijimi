#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sijimi.h"

#define TOKEN_DELIM " \t\r\n\a"

block *append_token(block *blk_header, token token_data);
int num_of_token(block *blk);
line *append_block(line *line_header, block block_data);
int num_of_block(line *line);
void print_block(block *block_header);
void print_token(token tok);

line *sijimi_split_line(char *input_line)
{
    line  *command_line = NULL;
    block *command_block = NULL;
    token command_token;

    command_token = strtok(input_line, TOKEN_DELIM);
    while (command_token != NULL) {
        if (strcmp(command_token, "|") == 0) {
            if (command_block == NULL) {
                fprintf(stderr, "syntax error\n");
                return NULL;
            }
            command_line = append_block(command_line, *command_block);
            command_block = NULL;
        } else {
            command_block = append_token(command_block, command_token);
        }
        command_token = strtok(NULL, TOKEN_DELIM);
    }

    if (command_block != NULL) {
        // 以下でセグフォが発生している
        command_line = append_block(command_line, *command_block);
    }

    return command_line;
}

block *append_token(block *blk_header, token token_data)
{
    block *top_blk = blk_header;
    block *next_block = malloc(sizeof(block));

    next_block->tok = token_data;
    next_block->next_block = NULL;

    if (blk_header == NULL) {
        return next_block;        
    }

    while(blk_header->next_block != NULL) {
        blk_header = blk_header->next_block;
    }
    blk_header->next_block = next_block;

    return top_blk;
}

int num_of_token(block *blk)
{
    int num = 0;
    
    if (blk == NULL) {
        return 0;
    }

    while(blk->next_block != NULL) {
        num++;
        blk = blk->next_block;
    }
    return num + 1;
}

line *append_block(line *line_header, block block_data)
{
    line *top_line = line_header;
    line *next_line = malloc(sizeof(line));
    if (next_line == NULL) {
        fprintf(stderr, "malloc: memory allocation error\n");
    }

    next_line->blk = block_data;
    next_line->next_line = NULL;

    if (line_header == NULL) {
        return next_line;
    }

    while(line_header->next_line != NULL) {
        line_header = line_header->next_line;
    }

    line_header->next_line = next_line;

    return top_line;
}

int num_of_block(line *line)
{
    int num = 0;
    
    if (line == NULL) {
        return 0;
    }

    while(line->next_line != NULL) {
        num++;
        line = line->next_line;
    }
    return num;
}

char **block_to_array(block *blk)
{
    int token_num = num_of_token(blk), i = 0;
    char **blk_array = malloc(sizeof(char *) * token_num+1);
    block *blk_head = blk;

    while(blk != NULL) {
        blk_array[i++] = blk->tok;
        // printf("hoge: %s\n", (*blk_array));
        blk = blk->next_block;
    }
    *(blk_array+token_num) = NULL;
    return blk_array;
}

void print_line(line *line_header)
{
    while(line_header != NULL) {
        print_block(&line_header->blk);
        line_header = line_header->next_line;
    }
    puts("¥¥¥¥¥¥¥¥¥¥¥¥¥¥¥¥¥¥");
}

void print_block(block *block_header)
{
    while(block_header != NULL) {
        print_token(block_header->tok);
        block_header = block_header->next_block;
    }
    puts("-------------------");
}

void print_token(token tok)
{
    printf("%s\n", tok);
}