#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

#include "mssql.h"
     


int set_cmd_option(int argc, char **argv, struct dbconfig *dbconf) {
    int c;
    int argument_fullfilled = 0;
    int need_password=0;

    while (1){
    struct option long_options[] =
        {
           {"host",     required_argument, 0, 'h'},
           {"help",     no_argument,       0, 'z'},
           {"version",  no_argument,       0, 'v'},
           {"user",     required_argument, 0, 'u'},
           {"password", no_argument,       0, 'p'},
           {0, 0, 0, 0}
        };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "h:u:z:v:p", long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c){
            case 'u':
              dbconf->username = optarg;
              break;
            case 'p':
              need_password = 1;
              break;
            case 'h':
              dbconf->hostname = optarg;
              break;
            case 'z':
              show_usage();
              exit(1);
              break;
            case 'v':
              show_version();
              exit(1);
              break;
            default:
              show_usage();
              exit(1);
              break;
        }
    }

  if(!need_password || !strcmp(dbconf->hostname, "") || !strcmp(dbconf->username , "")){
      printf("Missing one or more required arguments. Option [h,p,u] are required.\n");
      show_usage();
      return 0;
  }else{
      
      dbconf->password = (char *)malloc(256);
      dbconf->password = getpass("Enter password: ");
      argument_fullfilled = 1;
  }


  if (optind < argc){
      dbconf->database = argv[optind];
  }
  if(!argument_fullfilled){
      return 0;
  }
  return 1;

}
