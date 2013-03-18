#include <unistd.h>
#include <sys/param.h>
#include <sybfront.h>
#include <sybdb.h>
#include <syberror.h>
#include <stdio.h>
#include <stdlib.h>

#define  UID       "sa"
#define  PWD       "hanhan"
#define  PROGNAME  "DemoProg"
#define  DBSERVER  "192.168.10.92"
#define  DBNAME    "hogehoge"

LOGINREC * get_login(char *uid, char *pwd);

int main(){
    char *sql;
    LOGINREC *login;

	login = get_login(UID, PWD);
}

LOGINREC * get_login(char *uid, char *pwd) {

    LOGINREC *login = (LOGINREC * )malloc(2048);

    char hostname[MAXHOSTNAMELEN];
    if (dbinit() == FAIL) {
      fprintf(stderr, "Could not init db.\n");
    }
    if ((login = dblogin()) == FAIL) {
      fprintf(stderr, "Could not initialize dblogin() structure.\n");
    }
    DBSETLUSER(login, uid);
    DBSETLPWD(login, pwd);
    DBSETLAPP(login, PROGNAME);
    if (gethostname(hostname, MAXHOSTNAMELEN) == 0)
      DBSETLHOST(login, hostname);

    printf("%s %s \n", uid, pwd);

	return login;
}

