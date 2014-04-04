
char *sql;

#define  VERSION   "0.01"
#define  CHARSET   "utf8"
#define  PROGNAME  "DemoProg"

#define  PROMPT_LENGTH 7
#define  HISTORY_FILE "~/.mssql_history" 

typedef struct dbconfig{
    char *username;
    char *password;
    char *hostname;
    char *database;
} dbconf;

int set_cmd_option(int argc, char **argv, struct dbconfig *dbconf);

void set_login(struct dbconfig dbconf);
void set_dbprocess(struct dbconfig dbconf);
void set_database(struct dbconfig dbconf);
int execute_query(struct dbconfig dbconf);

void show_usage();
