#include <stdio.h>
#include "mssql.h"

void show_usage(){
    printf("mssql Ver %s\n", VERSION);
    printf("Usage: mssql -h {hostname} -u {username} -p {password} {database}\n");
    printf("options:\n");
    printf("    -h         hostname\n");
    printf("    -u         username\n");
    printf("    -p         password\n");
}
