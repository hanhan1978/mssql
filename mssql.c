#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>                  /*  for sleep()  */
#include <curses.h>
#include <locale.h>

#include "mssql.h"

#define HISTORY_FILE "~/.mssql_history" 

int main(void) {


    setlocale(LC_ALL,"");
    WINDOW * mainwin;
    mainwin = initscr();
    noecho();

	while(1){
	    show_prompt();
        set_input();
        execute_query();
        free(sql);
	}

	getch();
 //   delwin(mainwin);
    endwin();
  //  refresh();

    return EXIT_SUCCESS;
}
