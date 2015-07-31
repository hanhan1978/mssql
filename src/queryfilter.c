#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>


char * remove_consective_blank(char *);  //private
char * remove_semicolon(char *);  //private
char * trim_by_pointer(char *);  //private

char * trans_dialect(char *, const char *); //public

/*
int main(){
    char * str = (char *)malloc(128);
    sprintf(str, "show  databases;");
    printf("%i\n", strlen(str));
    printf("%s\n", str);
    str = remove_consective_blank(str);
    sprintf(sql, "SELECT   *  FROM    HOGE;");
    printf("%i\n", strlen(str));
    printf("%s\n", str);
}
*/
char * trans_dialect(char * output, const char * input){
  output = (char *)malloc(strlen(input));

  return output;
}

char * remove_consective_blank(char * str){
  int i = 0;
  int k = 0;

  char * retstr = (char *)malloc(strlen(str));
  char pre_ch;

  while(1){
    if(str[i] == '\0'){
      break;
    }
    if(str[i] != ' ' || pre_ch != ' '){
      retstr[k] = str[i];
      k++;
    }
    pre_ch = str[i]; 
    i++;
  }
  retstr[k] == '\0';
  return retstr; 
}
