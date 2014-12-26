#include <stdio.h>
#include <stdlib.h>
#include "mssql.h"

void show_usage(){
    printf("mssql Ver %s\n", VERSION);
    printf("Usage: mssql -h {hostname} -u {username} -p {password} {database}\n");
    printf("required arguments:\n");
    printf("    -h          hostname\n");
    printf("    -u          username\n");
    printf("    -p          password\n");
    printf("optional arguments:\n");
    printf("    --help      show this help\n");
    printf("    {database}  initial database\n");
    exit(1);
}

void show_version(){
    printf("mssql Ver %s\n", VERSION);
}
