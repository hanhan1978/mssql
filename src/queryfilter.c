#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>


char * remove_consective_blank(const char *);  //private
char * remove_semicolon(char *);  //private
char * trim_by_pointer(char *);  //private

char * trans_dialect(char *, const char *); //public


int main(){
    char * input; char * output;
    input = (char *)malloc(128);
    sprintf(input, "SELECT  *    FROM  HOGE;");
    output = remove_consective_blank(input);
    printf("[%s]%i\n", output, strlen(output));
    free(input);

    input = (char *)malloc(128);
    sprintf(input, "show  databases;");
    output = remove_consective_blank(input);
    printf("[%s]%i\n", output, strlen(output));
}

char * trans_dialect(char * output, const char * input){
  output = (char *)malloc(strlen(input));

  return output;
}

char * remove_consective_blank(const char * input){
  int i = 0;
  int k = 0;

  printf("input >>>> [%s]%i\n", input, strlen(input));
  char output[strlen(input)];
  char pre_ch;

  while(1){
    if(input[i] == '\0'){
      break;
    }
    if(input[i] != ' ' || pre_ch != ' '){
      output[k] = input[i];
      printf("retprogress >>>> [%s]%i\n", output, strlen(output));
      k++;
    }
    pre_ch = input[i]; 
    i++;
  }
  output[k] == '\0';
  char * retstr = (char *)malloc(k);
  strncpy(retstr, output, k);
  printf("output >>>> [%s]%i\n", retstr, strlen(retstr));
  return retstr; 
}
