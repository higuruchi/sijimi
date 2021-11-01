#define LINE_BUFSIZE 1024

typedef struct {
    char *cwd, *user, *home;
} ENV;

typedef char * token;

typedef struct block {
    token tok;
    struct block *next_block;
} block;

typedef struct line {
    int redirect_flg;
    block blk;
    struct line *next_line;
} line;



extern char *builtin_str[];
extern int (*builtin_func[])(ENV *, char **);

char *read_line(void);
line *split_line(char *);
void print_line(line *);
int num_of_block(line *);
int num_of_token(block *blk);
char **block_to_array(block *);


int execute(ENV *, line *);

int sijimi_cd (ENV *, char **);
int sijimi_help(ENV *, char **);
int sijimi_exit(ENV *,char **);
int sijimi_num_builtins();
