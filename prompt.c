#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

void show_prompt(){
	addstr("mssql> ");
}


char * get_input(WINDOW *win){
    char *s;
    s = (char *)malloc(2048);
	int sm_flag = 0;
    int i=0; 
    while(1){
	    s[i] = getch(); 
		addch(s[i]);
		if(s[i] == ';'){
		    sm_flag=1;
		}
		if(s[i] == '\n' && sm_flag == 1){
		    return s;
		}
		i++;
	}
}


//
//		getyx(win, y, x);
//		    printw("x = %d, y = %d", x, y);
