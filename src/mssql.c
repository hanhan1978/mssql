#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "mssql.h"

int my_startup(void);
int my_bind_cr(int, int);
int my_bind_eoq(int, int);
char *my_readline(void);

int my_eoq; 

int main(int argc, char *argv[]) {
    struct dbconfig dbconf = {"","","",""};

    if (!set_cmd_option( argc, argv, &dbconf)){
        return 1;
    }
    eprintf("%s %s %s %s\n", dbconf.hostname, dbconf.password, dbconf.username, dbconf.database);

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
    if (my_eoq == 1) {
        rl_done = 1;
    }
    if (strcmp( rl_line_buffer , "") == 0){
        printf("\n");
        rl_on_new_line();
    }else{
        rl_insert_text(" \n");
    }
    return 1;
}

int my_bind_eoq(int count, int key) {
    my_eoq = 1;
    printf(";");
    return 1;
}

char * my_readline(void) {
    char *line;
    while(1){
        if ((line = readline("mssql> ")) == NULL) {
            return NULL;
        }
        printf("\n\nSQL EXECUTE : %s\n", line);
    }
}
