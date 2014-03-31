#include <unistd.h>
#include <sys/param.h>
#include <sybfront.h>
#include <sybdb.h>
#include <syberror.h>
#include <stdio.h>
#include <ncurses.h>

#include "mssql.h"


LOGINREC *login;
DBPROCESS *dbproc;
DBPROCESS *dbconn;

void set_login();
void set_dbprocess();
void set_database();
int execute_query();


int execute_query(){

  set_login();
  set_dbprocess();
  set_database();

  dbcmd(dbconn, sql);

  if (dbsqlexec(dbconn) == FAIL) {
    fprintf(stderr, "\nCould not execute the sql statement\n");
    return 5;
  }
  dbresults(dbconn); 

  /* bind selected value  */
  int colnum = dbnumcols(dbconn);
  char val[colnum][255];
  for(int i =0; i<colnum;i++){
    dbbind(dbconn, i+1, NTBSTRINGBIND, 0, (BYTE *)val[i]);
  }
  for(int i=0; i<colnum ;i++){
    addstr(dbcolname(dbconn,i+1));
    addstr("\t");
  }
  addstr("\n");

  while (dbnextrow(dbconn) != NO_MORE_ROWS) {
    for(int i=0; i<colnum ;i++){
      addstr(val[i]);
      addstr("\t");
    }
    addstr("\n");
  }

  dbfreebuf(dbconn);
  dbclose(dbconn);
  dbexit();
  
  return 0;
}




void set_login(){
    dbinit();
    login = dblogin();
	DBSETLCHARSET(login, CHARSET);
    DBSETLUSER(login, UID);
    DBSETLPWD(login, PWD);
    DBSETLAPP(login, PROGNAME);
    char hostname[MAXHOSTNAMELEN];
    if (gethostname(hostname, MAXHOSTNAMELEN) == 0)
    DBSETLHOST(login, hostname);
}

void set_dbprocess(){
    if ((dbconn = dbopen(login, host)) == NULL) { }
}

void set_database(){
    if ((dbuse(dbconn, DBNAME)) == FAIL) { }
    dbloginfree(login);
}
