#include <unistd.h>
#include <sys/param.h>
#include <sybfront.h>
#include <sybdb.h>
#include <syberror.h>
#include <stdio.h>

#include "mssql.h"


LOGINREC *login;
DBPROCESS *dbproc;
DBPROCESS *dbconn;

void set_login(struct dbconfig *dbconf);
int set_dbprocess(struct dbconfig *dbconf);

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
  char val[colnum][255];
  int i;
  for(i =0; i<colnum;i++){
    dbbind(dbconn, i+1, NTBSTRINGBIND, 0, (BYTE *)val[i]);
  }
  for(i=0; i<colnum ;i++){
    printf("%s\t", dbcolname(dbconn,i+1));
  }
  printf("\n");

  while (dbnextrow(dbconn) != NO_MORE_ROWS) {
    for(i=0; i<colnum ;i++){
        printf("%s\t", val[i]);
    }
    printf("\n");
  }
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
        printf("Type 'help;' or '\\h' for help. Type '\\c' to clear the current input statement.\n");
        return 1;
    }
    printf("Access denied for user '%s' (using password: YES)\n", dbconf->username);
    return 0;
}

