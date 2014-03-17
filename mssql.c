#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>                  /*  for sleep()  */
#include <curses.h>
#include <locale.h>

#include "mssql.h"

#define HISTORY_FILE "~/.mssql_history" 
char hisfilepath[256];

void  sethisfilepath(){
    strcpy(hisfilepath, getenv("HOME"));
    char *filename = "/.mssql_history";
    strcat(hisfilepath, filename);
}

void writehis(char * sql){
    FILE *fp;
    fp = fopen(hisfilepath, "a");
    fputs(sql, fp);
    fclose(fp);
}

void readhis(){
    FILE *fp;
    fp = fopen(hisfilepath, "r");
    sql = (char *)malloc(2048);
    if( fp == NULL ) {
         printf( "file open error\n" );
    }

    fseek(fp, 5, SEEK_CUR);
    int i;
    while( fgets( sql , 1024 , fp ) != NULL ) {
          break;
//        printf( "row=%s" , sql );/* row */
    }
//    fgets(row, 1024, fp);
    fclose(fp);
}

int main(void) {
    sethisfilepath(); //set history filepath to global var hisfilepath

//    readhis();
//    printf("%s", sql);

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
