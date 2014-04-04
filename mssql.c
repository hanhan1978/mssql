#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>                  /*  for sleep()  */
#include <curses.h>
#include <locale.h>

#include "mssql.h"


int main(int argc, char **argv ) {

	struct dbconfig dbconf = {"", "","",""};

    if(!set_cmd_option (argc, argv, &dbconf)){
    	show_usage();
        return 0;
    }


    sethisfilepath();

    setlocale(LC_ALL,"");
    WINDOW * mainwin;
    mainwin = initscr();
    noecho();

	while(1){
	    show_prompt();
        set_input();
        execute_query(dbconf);
        writehis(sql);
	}

	getch();
 //   delwin(mainwin);
    endwin();
  //  refresh();

    return EXIT_SUCCESS;
}
