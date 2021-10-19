#define LINE_BUFSIZE 1024

typedef struct {
    char *cwd, *user;
} ENV;

typedef char * token;

typedef struct block {
    token tok;
    struct block *next_block;
} block;

typedef struct line {
    block blk;
    struct line *next_line;
} line;



extern char *builtin_str[];
extern int (*builtin_func[])(ENV *, char **);

char *sijimi_read_line(void);
line *sijimi_split_line(char *);
void print_line(line *);
int num_of_block(line *);
char **block_to_array(block *);


int sijimi_execute(ENV *, line *);
int sijimi_launch(ENV *,  line *, int);

int sijimi_cd (ENV *, char **);
int sijimi_help(ENV *, char **);
int sijimi_exit(ENV *,char **);
int sijimi_num_builtins();
