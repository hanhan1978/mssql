#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>


char * trans_dialect(const char *); //public

int regex_size();

int main (){

  char * output;
  output = trans_dialect("show tables like 'fuga%'");
  printf("sql -> %s\n", output);

  output = trans_dialect("show tables");
  printf("sql -> %s\n", output);
}

typedef struct dialect{
    char *regex;
    char *sql;
} dialect;

int regex_size(){
  return 3;
}

dialect * get_regex(){
  int reg_size = regex_size();
  struct dialect * da = (struct dialect *)malloc(sizeof(struct dialect) * reg_size);

  int i = 0;
  for(i; i < reg_size; i++){
    da[i].regex = (char *) malloc(1024);
    da[i].sql = (char *) malloc(1024);
  }
  strcpy(da[0].regex, "^show databases$");
  strcpy(da[0].sql, "SELECT name AS DBName FROM master.dbo.sysdatabases WHERE dbid > 4");
  strcpy(da[1].regex, "^show tables$");
  strcpy(da[1].sql, "SELECT name AS Tables FROM sysobjects WHERE xtype = 'U' ORDER BY name");
  strcpy(da[2].regex, "^show tables like ([%'\"a-z]+)$");
  strcpy(da[2].sql, "SELECT name AS Tables FROM sysobjects WHERE xtype = 'U' AND name LIKE %s ORDER BY name");
  strcpy(da[3].regex, "");
  strcpy(da[3].sql, "SELECT name AS Tables FROM sysobjects WHERE xtype = 'U' AND name LIKE %s ORDER BY name");
  strcpy(da[4].regex, "^show tables like ([%'\"a-z]+)$");
  strcpy(da[4].sql, "SELECT name AS Tables FROM sysobjects WHERE xtype = 'U' AND name LIKE %s ORDER BY name");
  return da;
}

char * trans_dialect(const char * input){
  int i=0;
  char * output;
  struct dialect * ds = get_regex();
  regex_t reg;
  regmatch_t match[2];
  char errbuf[100];
  int reti;

  for(i; i< regex_size() ; i++){
    if(!regcomp(&reg, ds[i].regex, REG_EXTENDED | REG_ICASE)){
      reti = regexec(&reg, input, 2, match, 0);
      if(!reti){
        int output_length = strlen(ds[i].sql);
        if(match[1].rm_so > 0){
          char matched[match[1].rm_eo - match[1].rm_so + 1];
          int k = 0;
          for(k; k < match[1].rm_eo - match[1].rm_so ; k++){
            matched[k] = *(input + match[1].rm_so + k);
          }
          matched[k] = '\0';
          //printf("k -> %d, matched -> %s \n", k, matched);
          output_length += match[1].rm_eo - match[1].rm_so;
          output =(char *)malloc(output_length * sizeof(char));
          sprintf(output, ds[i].sql, matched);
          return output;
        }
        output =(char *)malloc(output_length * sizeof(char));
        strcpy(output, ds[i].sql);
        return output;
      }
    }
  }
  output = (char *)malloc(strlen(input));
  strcpy(output, input); 
  return output;
}

