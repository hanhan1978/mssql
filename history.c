#include <stdlib.h>
#include <stdio.h>

#include "mssql.h"

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
    }
    fclose(fp);
}
