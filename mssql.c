#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>                  /*  for sleep()  */
#include <curses.h>
#include <locale.h>

#include "mssql.h"

int main(int argc, char **argv ) {

	struct dbconfig dbconf = {"", "","",""};

    if(!set_cmd_option (argc, argv, &dbconf)){
        printf("please set host name\n\r");
        return 0;
    }
    puts(dbconf.username);
    puts(dbconf.password);


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
