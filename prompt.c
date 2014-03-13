#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncurses.h>


#include "mssql.h"

void show_prompt(){
	addstr("mssql> ");
}

void show_continue(){
	addstr("    -> ");
}

void clear_propmpt(){

}

int del_backward(WINDOW *win, int i){
    int x,y;
	getyx(win, y, x);
    if(x > PROMPT_LENGTH){
        mvdelch(y,x-1);
        i = i-1;
    }
    return i;
}

void set_input(WINDOW *win){
    sql = (char *)malloc(2048);
	int sm_flag = 0;
    int i=0; 
    while(1){
	    sql[i] = getch(); 

        //enter key without input
        if(i==0 && sql[i] == '\n'){
            addstr("\n");
            show_prompt();
            continue;
        }

//        printf("%0d", sql[i]);
        //delete key
        if(sql[i] == 127 || sql[i] == 8){
            i = del_backward(win, i);
            continue;
        }


        //ctrl+p
        if(sql[i] == 16){
            addstr("unko");
            continue;
        }

		addch(sql[i]);

		if(sql[i] == ';'){
		    sm_flag=1;
		}
		if(sql[i] == '\n'){
            if(sm_flag == 1){
		        return;
            }else{
                show_continue();
            }
		}
		i++;
	}
}


