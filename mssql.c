#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>                  /*  for sleep()  */
#include <curses.h>
#include <locale.h>

#include "mssql.h"


int main(int argc, char **argv ) {

    if(!set_cmd_option (argc, argv)){
        printf("please set host name\n\r");
        return 0;
    }
//    printf("%s what's up2 \n", host);
//    return 0;
    sethisfilepath();

    setlocale(LC_ALL,"");
    WINDOW * mainwin;
    mainwin = initscr();
    noecho();

	while(1){
	    show_prompt();
        set_input();
        execute_query();
        writehis(sql);
	}

	getch();
 //   delwin(mainwin);
    endwin();
  //  refresh();

    return EXIT_SUCCESS;
}
