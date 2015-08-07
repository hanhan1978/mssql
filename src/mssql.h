
#ifndef MSSQL_INCLUDE_H
#define MSSQL_INCLUDE_H

#define  MSSQL_CHARSET   "utf8"
#define  MSSQL_PROGNAME  "mssql"
#define  MSSQL_HISTORY_FILE_NAME  "/.mssql_history"

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


//-----utils.c
int is_pretty(const char * input);
char * normalize(const char * input);
int need_execution(const char * input);
int is_termination(const char * input);


//-----output.c
typedef struct result_node{
    char *value;
    struct result_node * next;
} node;

typedef struct result_set {
  int rows;
  int colnum;
  int * each_collen;
  struct result_node * hnode;
  struct result_node * node;
} result_set;
node * add_node(char * value, struct result_node * tail, int len);

void print_result(struct result_set * res);

#endif
