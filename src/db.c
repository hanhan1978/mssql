#include <unistd.h>
#include <sys/param.h>
#include <sybfront.h>
#include <sybdb.h>
#include <syberror.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mssql.h"


LOGINREC *login;
DBPROCESS *dbproc;
DBPROCESS *dbconn;

typedef struct result_node{
    char *value;
    struct result_node * next;
} node;

void set_login(struct dbconfig *dbconf);
int set_dbprocess(struct dbconfig *dbconf);
void print_result(struct result_node * node, int * length, int col_size);
void print_boundary(int * col_length, int col_size);
void free_result(struct result_node *node);
node * add_node(char * value, struct result_node * tail);
void print_pretty(struct result_node * hnode, struct result_node * node, int max_col_size, int col_size);
int err_handler(DBPROCESS *dbproc, int severity, int dberr, int oserr, char *dberrstr, char *oserrstr); 
int msg_handler(DBPROCESS *dbproc, DBINT msgno, int msgstate, int severity, char *msgtext, char *srvname, char *procname, int line);

int connect_db(){
  dbmsghandle(msg_handler);
  set_login(dbinfo);
  return set_dbprocess(dbinfo);
}


int execute_query(char * sql){

  dbcmd(dbconn, sql);
  //dberrhandle(err_handler);
  dbmsghandle(msg_handler);

  if (dbsqlexec(dbconn) == FAIL) {
    return 0;
  }
  dbresults(dbconn); 

  /* bind selected value  */
  int colnum = dbnumcols(dbconn);
  if(colnum <= 0){
      return 1;
  }


  char val[colnum][255];
  int maxlength[colnum];
  int i;
  for(i =0; i<colnum;i++){
    dbbind(dbconn, i+1, NTBSTRINGBIND, 0, (BYTE *)val[i]);
  }

  struct result_node * head = NULL;
  struct result_node * temp = NULL;

  int max_collength = 0;
  for(i=0; i<colnum ;i++){
    temp = add_node(dbcolname(dbconn,i+1), temp);
    if(head == NULL){
        head = temp;
    }
    maxlength[i] = (int)strlen(dbcolname(dbconn,i+1));
    if(max_collength < (int)strlen(dbcolname(dbconn,i+1))){
        max_collength = (int)strlen(dbcolname(dbconn,i+1));
    }
  }

  struct result_node * head2 = NULL;
  struct result_node * temp2 = NULL;

  int rows = 0;
  while (dbnextrow(dbconn) != NO_MORE_ROWS) {
    for(i=0; i<colnum ;i++){
        temp2 = add_node(val[i], temp2);
        if(head2 == NULL){
            head2 = temp2;
        }
        if(maxlength[i] < (int)strlen(val[i])){
            maxlength[i] = (int)strlen(val[i]);
        }
    }
    rows++;
  }
  if(pretty_print){
      print_pretty(head, head2, max_collength, colnum);
  }else{
      //print result
      print_boundary(maxlength, colnum);
      print_result(head, maxlength, colnum);
      print_boundary(maxlength, colnum);
      print_result(head2, maxlength, colnum);
      print_boundary(maxlength, colnum);
  }
  if(rows > 0){
      printf("%d rows in set\n\n", rows);
  }else{
      printf("Empty set\n\n");
  }

  free_result(head);
  free_result(head2);
  return 1;
}




void set_login(struct dbconfig *dbconf){
    dbinit();
    login = dblogin();
    DBSETLCHARSET(login, CHARSET);
    DBSETLUSER(login, dbconf->username);
    DBSETLPWD(login, dbconf->password);
    DBSETLAPP(login, PROGNAME);
    char hostname[MAXHOSTNAMELEN];
    if (gethostname(hostname, MAXHOSTNAMELEN) == 0)
    DBSETLHOST(login, hostname);
}

int set_dbprocess(struct dbconfig *dbconf){
    if ((dbconn = dbopen(login, dbconf->hostname)) != NULL){
        printf("Welcome to the SqlServer monitor.  Commands end with ; or \\g.\n");
        printf("Type 'help;' or '\\h' for help. Type '\\c' to clear the current input statement.\n\n");
        printf("Connected to default database => [%s] \n", dbname(dbconn));
        return 1;
    }
    printf("Access denied for user '%s' (using password: YES)\n", dbconf->username);
    return 0;
}

node * add_node(char * value, struct result_node * tail){
    struct result_node * node = (struct result_node *)malloc( sizeof(struct result_node) );
    node->value = (char *)malloc(1024);
    strcpy(node->value, value);
    node->next = NULL;
    if(tail != NULL){
        tail->next = node;
    }
    return node;
}

void print_boundary(int * col_length, int col_size){
    int col = 0;
    int i = 0;
    for( col=0; col < col_size; col++){
        printf("+");
        for(i=0; i<col_length[col] +2; i++){
          printf("-");
        }
    }
    printf("+\n");
}

void print_pretty(struct result_node * hnode, struct result_node * node, int max_col_size, int col_size){
    int col = 0;
    int i=0;
    struct result_node * it = node;
    struct result_node * ht; 

    while(it != NULL ){
        if(col % col_size == 0){
            ht = hnode; 
            printf("*************************** %d. row ***************************\n", (col/col_size)+1);
        }
        for(i =0; i<(max_col_size - strlen(ht->value)) ; i++){
            printf(" ");
        }
        printf("%s : %s\n", ht->value, it->value);
        it = it->next;
        ht = ht->next;
        col++;
    }
}

void print_result(struct result_node * node, int * col_length, int col_size){
    int col = 0;
    int i = 0;
    struct result_node * it = node;
    while(it != NULL ){
        printf("| %s", it->value);
        for(i =0; i<(col_length[col] - strlen(it->value)) ; i++){
            printf(" ");
        }
        printf(" ");
        it = it->next;
        if(col >= col_size -1){
          col=0;
          printf("|\n");
        }else{
          col++;
        }
    }
}


void free_result(struct result_node *node){
    struct result_node * it = node;
    struct result_node * nxt;
    while(it != NULL ){
        free(it->value);
        nxt = it->next;
        free(it);
        it = nxt;
    }
}


int err_handler( DBPROCESS    *dbproc, int severity, int dberr, int oserr, char *dberrstr, char *oserrstr )
{ 
      if ((dbproc == NULL) || (DBDEAD(dbproc))) 
           return(INT_EXIT); 
      else  
      { 
           printf("DB-Library error:\n\t%s\n",
                dberrstr); 
           if (oserr != DBNOERR) 
                printf("Operating-system \
                     error:\n\t%s\n", oserrstr); 
           return(INT_CANCEL); 
      } 
 } 


int msg_handler(DBPROCESS *dbproc, DBINT msgno, int msgstate, int severity, char *msgtext, char *srvname, char *procname, int line)
 { 
       if(msgno == 5701){
           printf ("\nDatabase changed\n");
           return 0;
       }
       printf("ERROR %d : %s", msgno, msgtext); 
       if (line > 0) 
           printf (" at line %d", line); 
       printf("\n\n");
 
       return(0); 
 } 
