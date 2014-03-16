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
int execute_query();


int execute_query(){
//  DBINT id;
  DBCHAR id[255];
  DBCHAR city[255];
  DBCHAR prefecture[255];
  char   resultstr[100];

  set_login();
  set_dbprocess();

  /* Now prepare a SQL statement */
  dbcmd(dbconn, sql);

  /* Now execute the SQL statement */
  if (dbsqlexec(dbconn) == FAIL) {
    fprintf(stderr, "Could not execute the sql statement\n");
    return 5;
  }
  dbresults(dbconn); /* Very important to call this! :) */

  /* Now bind the returned columns to the variables */
  dbbind(dbconn, 1, NTBSTRINGBIND, 0, (BYTE *)&id);
  dbbind(dbconn, 2, NTBSTRINGBIND, 0, (BYTE *)&prefecture);
  dbbind(dbconn, 3, NTBSTRINGBIND, 0, (BYTE*)&city);

  /* Loop thru the result set */
  while (dbnextrow(dbconn) != NO_MORE_ROWS) {
    /* print out the data */
    sprintf(resultstr, "%s %s %s\n", id, prefecture, city);
    addstr(resultstr);
  }

  /* Clean up*/
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
    if ((dbconn = dbopen(login, DBSERVER)) == NULL) { }
    if ((dbuse(dbconn, DBNAME)) == FAIL) { }
    dbloginfree(login);
}
