

#define  CHARSET   "utf8"
#define  PROGNAME  "mssql"
#define  HISTORY_FILE_NAME  "/.mssql_history"

//#define eprintf(...) fprintf(stderr, __VA_ARGS__) 
#define eprintf(...) do {} while(0) 

typedef struct dbconfig{
    char *username;
    char *password;
    char *hostname;
    char *database;
} dbconf;

struct dbconfig * dbinfo;

int pretty_print;

int my_startup(void);
int my_bind_cr(int, int);
int my_bind_eoq(int, int);
char *my_readline(void);
char * trans_dialect(char * line);
char * history_file;

int my_eoq; 
int set_cmd_option(int argc, char **argv, struct dbconfig *dbconf);

int connect_db();
int execute_query(char * sql);

void show_usage();
void show_version();

int is_pretty(char *line);
char * format_string(char * sql);
char * trim_by_pointer(char * str, const char * point);
char * remove_consective_blank(char * str);

typedef struct result_node{
    char *value;
    struct result_node * next;
} node;

void print_normal(struct result_node * hnode, struct result_node * node, int * max_col_size, int col_size);
