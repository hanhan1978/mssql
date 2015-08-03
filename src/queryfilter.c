#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>


char * remove_consective_blank(const char *);  //private
char * remove_semicolon(char *);  //private
char * trim_by_pointer(char *);  //private

char * trans_dialect(const char *); //public


typedef struct dialect{
    char *regex;
    char *sql;
} dialect;

dialect * get_regex(){
  int regex_size = 2;
  struct dialect * da = (struct dialect *)malloc(sizeof(struct dialect) * regex_size);

  int i = 0;
  for(i; i < regex_size; i++){
    da[i].regex = (char *) malloc(1024);
    da[i].sql = (char *) malloc(1024);
  }

  strcpy(da[0].regex, "^show tables$");
  strcpy(da[0].sql, "SELECT name AS Tables FROM sysobjects WHERE xtype = 'U'");
  strcpy(da[1].regex, "^show databases$");
  strcpy(da[1].sql, "SELECT name AS DBName FROM master.dbo.sysdatabases WHERE dbid > 4 %s");
  return da;
}


//int main(){
//  char * input;
//  char * output;
//  input = "show databases";
//  output = trans_dialect(input);
//  printf("result -> %s\n", output);
//}



char * trans_dialect(const char * input){
  int i=0;
  char * output;
  struct dialect * ds = get_regex();
  regex_t reg;
  regmatch_t match;
  char errbuf[100];
  int reti;

  for(i; i< 2 ; i++){
    if(!regcomp(&reg, ds[i].regex, REG_EXTENDED | REG_ICASE)){
      reti = regexec(&reg, input, 1, &match, 0);
      if(!reti){
        output =(char *)malloc(strlen(ds[i].sql) * sizeof(char));
        strcpy(output, ds[i].sql);
        return output;
      }
    }
  }
  output = (char *)malloc(strlen(input));
  strcpy(output, input); 
  return output;
}


char * remove_consective_blank(const char * input){
  int i = 0;
  int k = 0;

  char output[strlen(input)];
  char pre_ch;

  while(1){
    if(input[i] == '\0'){
      break;
    }
    if(input[i] != ' ' || pre_ch != ' '){
      output[k] = input[i];
      k++;
    }
    pre_ch = input[i]; 
    i++;
  }
  output[k] == '\0';
  char * retstr = (char *)malloc(sizeof(char) * k);
  strncpy(retstr, output, k);
  return retstr; 
}