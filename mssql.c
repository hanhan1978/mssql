#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>                  /*  for sleep()  */
#include <curses.h>


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
