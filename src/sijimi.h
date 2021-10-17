#define LINE_BUFSIZE 1024

extern char *builtin_str[];
extern int (*builtin_func[])(char **);

void sijimi_loop(void);
char *sijimi_read_line(void);
char **sijimi_split_line(char *);
int sijimi_execute(char **args);
int sijimi_launch(char **);
int sijimi_cd (char **args);
int sijimi_help(char **args);
int sijimi_exit(char **args);
int sijimi_num_builtins();
