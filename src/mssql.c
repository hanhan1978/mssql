#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "mssql.h"
#include "slre.h"

int my_startup(void);
int my_bind_cr(int, int);
int my_bind_eoq(int, int);
char *my_readline(void);

int my_eoq; 

int main(int argc, char *argv[]) {

    if(argc <= 1){
        show_usage();
        return 0;
    }
 
    dbinfo = (struct dbconfig *)malloc( sizeof(struct dbconfig) );
    if (!set_cmd_option( argc, argv, dbinfo)){
        return 0;
    }
    //eprintf("%s %s %s %s\n", dbconf.hostname, dbconf.password, dbconf.username, dbconf.database);
    if (!connect_db(dbinfo)){
        return 0;
    }

    //set hisotry file path
    history_file = (char *)malloc(256);
    strcpy(history_file, getenv("HOME"));
    strcat(history_file, HISTORY_FILE_NAME);

    read_history(history_file);

    rl_startup_hook = my_startup;
    my_readline();
}

int my_startup(void) {
    my_eoq = 0;
    rl_bind_key('\n', my_bind_cr);
    rl_bind_key('\r', my_bind_cr);
    rl_bind_key(';', my_bind_eoq);
    return 1;
}

int my_bind_cr(int count, int key) {
    struct slre_cap caps[4];
    if (my_eoq == 1 || slre_match(";\\s*$", rl_line_buffer, strlen(rl_line_buffer), caps, 4, 0) > 0) {
        rl_done = 1;
        return 1;
    }
    if (strcmp( rl_line_buffer , "") == 0 || slre_match("^\\s+$", rl_line_buffer, strlen(rl_line_buffer), caps, 4, 0) > 0) {
        printf("\n");
        rl_on_new_line();
    }else{
        rl_insert_text(" \n");
    }
    return 1;
}

int my_bind_eoq(int count, int key) {
    my_eoq = 1;
    rl_insert_text(";");
    return 1;
}

char * my_readline(void) {
    char *line;
    char *sql;
    while(1){
        if ((line = readline("mssql> ")) == NULL) {
            return NULL;
        }
        sql = trans_dialect(line);
        eprintf("\nSQL EXECUTE : %s\n", sql);
        printf("\n");
        if (execute_query(sql) > 0){
            add_history(line);
            write_history(history_file);
        }
        free(sql);
    }
}


char * trans_dialect(char * line){
    char * sql = (char *)malloc(1024);
    struct slre_cap caps[4];
    if (slre_match("^show databases\\s*;\\s*$", line, strlen(line), caps, 4, 0) > 0) {
        strcpy(sql,"SELECT name FROM master.dbo.sysdatabases WHERE dbid > 4 ");
    }else if (slre_match("^show tables\\s*;\\s*$", line, strlen(line), caps, 4, 0) > 0) {
        strcpy(sql,"SELECT name FROM sysobjects WHERE xtype = 'U'");
    }else{
        strcpy(sql, line);
    }
    return sql;
}



