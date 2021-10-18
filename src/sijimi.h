#define LINE_BUFSIZE 1024

typedef struct {
    char *cwd, *user;
} ENV;

extern char *builtin_str[];
extern int (*builtin_func[])(ENV *, char **);

char *sijimi_read_line(void);
char **sijimi_split_line(char *);
int sijimi_execute(ENV *, char **args);
int sijimi_launch(ENV *, char **);
int sijimi_cd (ENV *, char **args);
int sijimi_help(ENV *, char **args);
int sijimi_exit(ENV *,char **args);
int sijimi_num_builtins();
