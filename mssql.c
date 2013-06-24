#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>                  /*  for sleep()  */
#include <curses.h>

#define  UID       "hanhan"
#define  PWD       "hanhan"
#define  PROGNAME  "DemoProg"
#define  DBSERVER  "192.168.10.92"
#define  DBNAME    "hogehoge"

int main(void) {
    WINDOW * mainwin;
    mainwin = initscr();
    noecho();

	while(1){
	    show_prompt();
        char *ss = get_input();
	    //addstr(ss);
         
		addch('\n');
	}

	getch();

 //   delwin(mainwin);
    endwin();
  //  refresh();

    return EXIT_SUCCESS;
}
