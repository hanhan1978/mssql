/**
 * @file
 * main file for mssql 
 *
 * main func do only following 
 *  1. => set command line args to struct
 *  2. => check if database connection succeed
 *  3. => call service invoker 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mssql.h"

int main(int argc, char *argv[]) {

  if(argc <= 1){
    show_usage();
    return 0;
  }
  //surpress stderr, because dblib.c display ugly error message
  freopen("/dev/null", "w", stderr);

  dbinfo = (struct dbconfig *)malloc(sizeof(struct dbconfig));
  if (!set_cmd_option( argc, argv, dbinfo)){
    return 0;
  }
  if (!connect_db(dbinfo)){
    return 0;
  }
  return cliservice();
}
