#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

#include "mssql.h"
     


int set_cmd_option(int argc, char **argv, struct dbconfig *dbconf) {
  int c;
  int argument_fullfilled = 0;


  while (1)
    {
      static struct option long_options[] =
        {
          {"add",     no_argument,       0, 'a'},
          {"host",    required_argument, 0, 'h'},
          {"user",    required_argument, 0, 'u'},
          {"password",    required_argument, 0, 'p'},
          {0, 0, 0, 0}
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;

      c = getopt_long (argc, argv, "ap:h:u:",
                       long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1){
          break;
      }

      switch (c)
        {
        case 0:
          /* If this option set a flag, do nothing else now. */
          if (long_options[option_index].flag != 0)
            break;
          printf ("option %s", long_options[option_index].name);
          if (optarg)
            printf (" with arg %s", optarg);
          printf ("\n");
          break;

        case 'u':
          dbconf->username = optarg;
          break;

        case 'p':
          dbconf->password = optarg;
          break;

        case 'h':
          dbconf->hostname = optarg;
          break;

        default:
          abort ();
        }
    }

  if(!strcmp(dbconf->password, "") || !strcmp(dbconf->hostname, "") || !strcmp(dbconf->username , "")){
	  return 0;
  }else{
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
