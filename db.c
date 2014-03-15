#include <unistd.h>
#include <sys/param.h>
#include <sybfront.h>
#include <sybdb.h>
#include <syberror.h>
#include <stdio.h>
#include <stdlib.h>

#define  UID       "dev"
#define  PWD       "devdev"
#define  PROGNAME  "DemoProg"
#define  DBSERVER  "192.168.10.6"
//#define  DBSERVER  "192.168.1.102"
#define  DBNAME    "hogehoge"
#define  CHARSET   "utf8"

//int connect_db(DBPROCESS *dbconn, char *uid, char *pwd);
DBPROCESS * connect_db(char *uid, char *pwd, char *dbname, char *sql); 

int * calc_colsize(int * max_col, char * sql);
//void set_dbprocess(DBPROCESS *dbproc, LOGINREC *login);
//void set_login(LOGINREC *login);

DBPROCESS *dbproc;
LOGINREC *login;

int main(){
    char *sql;

    sql = "select * from test";
    set_login();
    set_dbprocess();

    int * max_col;
	calc_colsize(& max_col, sql);
//    printf("%d \n", (int)sizeof(max_col));

    int i =0;
	for(i =0 ; i< 3 ;i++){
        printf("key[%d] => %d \n", i,max_col[i]);
	}
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
    if ((dbproc = dbopen(login, DBSERVER)) == NULL) { }
    if ((dbuse(dbproc, DBNAME)) == FAIL) { }
    dbloginfree(login);
}

void exec_query(char *sql){
    dbcmd(dbproc, sql);
    if (dbsqlexec(dbproc) == FAIL) { }
    dbresults(dbproc); 
	dbprrow(dbproc);
}


int * calc_colsize(int * max_col, char * sql){

    dbcmd(dbproc, sql);
    if (dbsqlexec(dbproc) == FAIL) {}
    dbresults(dbproc); 
	int cols = dbnumcols(dbproc);

    * max_col = (int *) malloc(sizeof(int) * cols);
    int i= 0;
	for( i =0; i < cols ; i++){
	    max_col[i] = i+3;
		//printf("%d \n", i+3);
	}
	for( i =0; i < cols ; i++){
		printf("key %d => %d \n", i, max_col[i]);
	}
	return max_col;
}



void print_result(DBPROCESS *dbproc, char *sql){

    dbcmd(dbproc, sql);
    if (dbsqlexec(dbproc) == FAIL) {
      fprintf(stderr, "Could not execute the sql statement\n");
    }
    dbresults(dbproc); /* Very important to call this! :) */

	int cols; int rows = 0;
	cols = dbnumcols(dbproc);
	printf("cols = %d \n", cols);

    char *colname; int i=1; int type; int len;
    for(i; i <= cols; i++){
	   colname = dbcolname(dbproc, i); 
	   type = dbcoltype(dbproc, i);

       printf("%s(type %d)\t", colname, type );
	}

    /* Loop thru the result set */
    DBINT id;
    DBCHAR str[255];
    while (dbnextrow(dbproc) != NO_MORE_ROWS) {
      /* print out the data */
      //printf("%s \t %s \t %s\n", (BYTE *)bd, prefecture, city);
	  rows++;
    }
	printf("rows = %d \n", rows);


    /* Clean up*/
    dbfreebuf(dbproc);

}





//DBINT id;
//DBCHAR prefecture[255];




//dbbind(dbproc, 1, INTBIND, 0, (BYTE *)&id);
//dbbind(dbproc, 2, NTBSTRINGBIND, 0, (BYTE *)&prefecture);
//dbbind(dbproc, 3, NTBSTRINGBIND, 0, (BYTE*)&city);







//	printf("NTBSTRINGBIND %d \n", NTBSTRINGBIND);
//	printf("INTBIND %d \n", INTBIND);
//	printf("SYBCHAR %d \n", SYBCHAR);
//	printf("SYBBINARY %d \n", SYBBINARY);
//	printf("SYBCHAR       %d \n",  SYBCHAR);
//	printf("SYBTEXT       %d \n",  SYBTEXT);
//	printf("SYBBINARY     %d \n",  SYBBINARY);
//	printf("SYBIMAGE      %d \n",  SYBIMAGE);
//	printf("SYBINT1       %d \n",  SYBINT1);
//	printf("SYBINT2       %d \n",  SYBINT2);
//	printf("SYBINT4       %d \n",  SYBINT4);
//	printf("SYBFLT8       %d \n",  SYBFLT8);
//	printf("SYBREAL       %d \n",  SYBREAL);
//	printf("SYBNUMERIC    %d \n",  SYBNUMERIC);
//	printf("SYBDECIMAL    %d \n",  SYBDECIMAL);
//	printf("SYBBIT        %d \n",  SYBBIT);
//	printf("SYBMONEY      %d \n",  SYBMONEY);
//	printf("SYBMONEY4     %d \n",  SYBMONEY4);
//	printf("SYBDATETIME   %d \n",  SYBDATETIME);
//	printf("SYBDATETIME4  %d \n",  SYBDATETIME4);
//	printf("SYBAOPSUM     %d \n",  SYBAOPSUM);
//	printf("SYBAOPAVG     %d \n",  SYBAOPAVG);
//	printf("SYBAOPCNT     %d \n",  SYBAOPCNT);
//	printf("SYBAOPMIN     %d \n",  SYBAOPMIN);
//	printf("SYBAOPMAX     %d \n",  SYBAOPMAX);     
////	printf("SYBBOUNDARY   %d \n",  SYBBOUNDARY);
////	printf("SYBSENSITIVITY %d \n",  SYBSENSITIVITY);
