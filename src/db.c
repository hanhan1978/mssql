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

int connect_db(struct dbconfig dbconf){
  set_login(dbconf);
  return set_dbprocess(dbconf);
}


int execute_query(struct dbconfig dbconf){

  set_login(dbconf);
  set_dbprocess(dbconf);
  set_database(dbconf);

  dbcmd(dbconn, sql);

  if (dbsqlexec(dbconn) == FAIL) {
    addstr("\nCould not execute the sql statement\n");
    return 5;
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
    addstr(dbcolname(dbconn,i+1));
    addstr("\t");
  }
  addstr("\n");

  while (dbnextrow(dbconn) != NO_MORE_ROWS) {
    for(i=0; i<colnum ;i++){
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




void set_login(struct dbconfig dbconf){
    dbinit();
    login = dblogin();
	DBSETLCHARSET(login, CHARSET);
    DBSETLUSER(login, dbconf.username);
    DBSETLPWD(login, dbconf.password);
    DBSETLAPP(login, PROGNAME);
    char hostname[MAXHOSTNAMELEN];
    if (gethostname(hostname, MAXHOSTNAMELEN) == 0)
    DBSETLHOST(login, hostname);
}

int set_dbprocess(struct dbconfig dbconf){
    if ((dbconn = dbopen(login, dbconf.hostname)) != NULL){
        printf("Welcome to the SqlServer monitor.  Commands end with ; or \\g.\n");
        printf("Type 'help;' or '\\h' for help. Type '\\c' to clear the current input statement.\n");
        return 1;
    }
    printf("Access denied for user '%s' (using password: YES)\n", dbconf.username);
    return 0;
}

void set_database(struct dbconfig dbconf){
    if ((dbuse(dbconn, dbconf.database)) == FAIL){
        eprintf("database selection failed !! \n");
    }else{
        eprintf("database selection succeeded !! \n");
    }
    dbloginfree(login);
}
