#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
     
/* Flag set by ‘--verbose’. */
static int verbose_flag;

int set_cmd_option (int argc, char **argv); 

int main (int argc, char **argv) {
    set_cmd_option(argc, argv);
}

int set_cmd_option(int argc, char **argv) {
  int c;

  while (1)
    {
      static struct option long_options[] =
        {
          {"verbose", no_argument,       &verbose_flag, 1},
          {"add",     no_argument,       0, 'a'},
          {"port",    required_argument, 0, 'p'},
          {"host",    required_argument, 0, 'h'},
          {0, 0, 0, 0}
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;

      c = getopt_long (argc, argv, "ap:h:",
                       long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1){
          printf("abort1\n");
          abort ();
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

//        case 'a':
//          puts ("option -a\n");
//          break;

        case 'p':
          printf ("option -c with value `%s'\n", optarg);
          break;

        case 'h':
          printf ("option -h with value `%s'\n", optarg);
          break;

        default:
          printf("abort2\n");
          abort ();
        }
    }


  if (verbose_flag)
    puts ("verbose flag is set");

  if (optind < argc)
    {
      printf ("non-option ARGV-elements: ");
      while (optind < argc)
        printf ("%s ", argv[optind++]);
      putchar ('\n');
    }

}
