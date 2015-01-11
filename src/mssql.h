


#define  VERSION   "0.0.2"
#define  CHARSET   "utf8"
#define  PROGNAME  "DemoProg"
#define  HISTORY_FILE_NAME  "/.mssql_history"

#define eprintf(...) fprintf(stderr, __VA_ARGS__) 
/*#define eprintf(...) do {} while(0) */

typedef struct dbconfig{
    char *username;
    char *password;
    char *hostname;
    char *database;
} dbconf;

struct dbconfig * dbinfo;

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
