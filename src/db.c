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


void set_login(struct dbconfig *dbconf);
int set_dbprocess(struct dbconfig *dbconf);
void free_result(struct result_node *node);
node * add_node(char * value, struct result_node * tail, int len);
int err_handler(DBPROCESS *dbproc, int severity, int dberr, int oserr, char *dberrstr, char *oserrstr); 
int msg_handler(DBPROCESS *dbproc, DBINT msgno, int msgstate, int severity, char *msgtext, char *srvname, char *procname, int line);

int connect_db(){
  dbmsghandle(msg_handler);
  dberrhandle(err_handler);
  set_login(dbinfo);
  return set_dbprocess(dbinfo);
}


int execute_query(char * sql){

  dbsetopt(dbconn, DBTEXTSIZE, "2147483647", -1);
  dbsetopt(dbconn, DBQUOTEDIDENT, "1", -1);
  dbcmd(dbconn, sql);
  dberrhandle(err_handler);
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


  int maxlength[colnum];
  int i;

  struct result_node * head = NULL;
  struct result_node * temp = NULL;

  int max_collength = 0;
  for(i=0; i<colnum ;i++){
    temp = add_node(dbcolname(dbconn,i+1), temp, 1024);
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

  int len;
  unsigned int tmp_len;
  int rows = 0;
  while (dbnextrow(dbconn) != NO_MORE_ROWS) {
    for(i=0; i<colnum ;i++){
        char * ptr = NULL;
        len = dbdatlen(dbconn, i+1);
        tmp_len = 32 + (2 * (len)); 
        ptr = malloc(tmp_len);
        dbconvert(dbconn, (dbcoltype(dbconn, i+1)) , (dbdata(dbconn, i+1)) , len, SYBCHAR, (BYTE *)ptr, -1);
        temp2 = add_node(ptr, temp2, tmp_len);
        if(head2 == NULL){
            head2 = temp2;
        }
        if(maxlength[i] < (int)strlen(ptr)){
            maxlength[i] = (int)strlen(ptr);
        }
    }
    rows++;
  }

  if(pretty_print){
      print_pretty(head, head2, max_collength, colnum);
  }else{
      print_normal(head, head2, maxlength, colnum);
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
    DBSETLCHARSET(login, MSSQL_CHARSET);
    DBSETLUSER(login, dbconf->username);
    DBSETLPWD(login, dbconf->password);
    DBSETLAPP(login, MSSQL_PROGNAME);
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

node * add_node(char * value, struct result_node * tail, int len){
    struct result_node * node = (struct result_node *)malloc( sizeof(struct result_node) );
    node->value = (char *)malloc(len);
    strcpy(node->value, value);
    node->next = NULL;
    if(tail != NULL){
        tail->next = node;
    }
    return node;
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
           //printf("DB-Library error:\n\t%s\n", dberrstr); 
           //if (oserr != DBNOERR) printf("Operating-system error:\n\t%s\n", oserrstr); 
           // display nothing, because msg_handler shows better description
           return(INT_CANCEL); 
      } 
 } 


int msg_handler(DBPROCESS *dbproc, DBINT msgno, int msgstate, int severity, char *msgtext, char *srvname, char *procname, int line)
 { 
       if(msgno == 5701){
           printf ("\nDatabase changed\n");
           return 0;
       }else if(msgno == 5703){
           return 0; //5703 is information lang setting message
       }
       printf("ERROR %d : %s", msgno, msgtext); 
       if (line > 0) 
           printf (" at line %d", line); 
       printf("\n\n");
 
       return(0); 
 } 
