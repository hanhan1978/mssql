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
int exit_flag = 0;

int main(int argc, char *argv[]) {

    if(argc <= 1){
        show_usage();
        return 0;
    }

    //surpress stderr, because dblib.c display ugly error message
    freopen("/dev/null", "w", stderr);
 
    dbinfo = (struct dbconfig *)malloc(sizeof(struct dbconfig));
    if (!set_cmd_option( argc, argv, dbinfo)){
        return 0;
    }
    if (!connect_db(dbinfo)){
        return 0;
    }

    //set hisotry file path
    history_file = (char *)malloc(256);
    strcpy(history_file, getenv("HOME"));
    strcat(history_file, MSSQL_HISTORY_FILE_NAME);
    read_history(history_file); //read history for incremental search (ctrl + r)

    rl_startup_hook = my_startup; //set up readline with original method binding
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
    if (my_eoq == 1 || slre_match("(\\\\G|;)\\s*$", rl_line_buffer, strlen(rl_line_buffer), caps, 4, SLRE_IGNORE_CASE) > 0){
        rl_done = 1;
        return 1;
    } else if( slre_match("^(\\\\q|exit)$", rl_line_buffer, strlen(rl_line_buffer), caps, 4, 0) > 0) {
        rl_done = 1;exit_flag=1;
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

/* set eoq flag when semi colon is typed */
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
        if(exit_flag){
            printf("\nBye\n");
            exit(0);
        }
        add_history(line);
        sql = trans_dialect(line); //convert the input sql if it matches mysql query dialect
        eprintf("\nSQL EXECUTE : %s\n", sql);
        printf("\n");
        if (execute_query(sql) > 0){
            write_history(history_file);
        }
        free(sql);
    }
}





