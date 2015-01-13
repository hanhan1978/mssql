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

int connect_db(){
  set_login(dbinfo);
  return set_dbprocess(dbinfo);
}


int execute_query(char * sql){

  dbcmd(dbconn, sql);

  if (dbsqlexec(dbconn) == FAIL) {
    printf("\nCould not execute the sql statement\n");
    return 0;
  }
  dbresults(dbconn); 


  /* bind selected value  */
  int colnum = dbnumcols(dbconn);
  if(colnum <= 0){
      printf("Empty set\n\n");
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

  for(i=0; i<colnum ;i++){
    temp = add_node(dbcolname(dbconn,i+1), temp);
    if(head == NULL){
        head = temp;
    }
    maxlength[i] = (int)strlen(dbcolname(dbconn,i+1));
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

  //print result
  print_boundary(maxlength, colnum);
  print_result(head, maxlength, colnum);
  print_boundary(maxlength, colnum);
  print_result(head2, maxlength, colnum);
  print_boundary(maxlength, colnum);
  printf("%d rows in set\n\n", rows);

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
        printf("Welcome to the SqlServer monitor.  Commands end with ;");
        printf("Type 'help;' or '\\h' for help. Type '\\c' to clear the current input statement.\n\n");
        printf("Connected to default database => [%s] \n", dbname(dbconn));
        return 1;
    }
    printf("Access denied for user '%s' (using password: YES)\n", dbconf->username);
    return 0;
}

node * add_node(char * value, struct result_node * tail){
    struct result_node * node = (struct result_node *)malloc( sizeof(struct result_node) );
    node->value = (char *)malloc(256);
    strcpy(node->value, value);
    node->next = NULL;
    if(tail != NULL){
        tail->next = node;
    }
    return node;
}

void print_boundary(int * col_length, int col_size){
    int col =0;
    for( col=0; col < col_size; col++){
        printf("+");
        for(int i=0; i<col_length[col] +2; i++){
          printf("-");
        }
    }
    printf("+\n");
}

void print_result(struct result_node * node, int * col_length, int col_size){
    int col = 0;
    struct result_node * it = node;
    while(it != NULL ){
        printf("| %s", it->value);
        for(int i =0; i<(col_length[col] - strlen(it->value)) ; i++){
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
