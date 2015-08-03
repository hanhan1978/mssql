#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

//public
int is_pretty(const char * input);
char * normalize(const char * input);

//private
char * remove_consective_blank(const char *);  
char * rtrim(const char * input);
char * ltrim(const char * input);
char * trim(const char * input);
char * replaceSpace(const char * input);


char * normalize(const char * input){
  char * replaced = replaceSpace(input);
  printf("[%s]\n", replaced);
  char * trimmed = trim(replaced);
  printf("[%s]\n", trimmed);
  char * normalized = remove_consective_blank(trimmed);
  printf("[%s]\n", normalized);
  free(replaced);
  free(trimmed);
  return normalized;
}

int is_pretty(const char * input){
  regex_t reg;
  regmatch_t match;

  if(!regcomp(&reg, "([^[:space:];])[[:space:]]*\\\\g[;[:space:]]+$", REG_EXTENDED | REG_ICASE)){
    return regexec(&reg, input, 1, &match, 0) <= 0;
  }
  return 0;
}

char * replaceSpace(const char * input){
  int i = 0;
  char * output = (char *) malloc (sizeof(char) * strlen(input));
  for(i ; i<strlen(input); i++){
    if(input[i] == '\n' || input[i] == '\t' || input[i] == '\r'){
      output[i] = ' ';
    }else if(i == strlen(input) -1){
      output[i] = '\0';
    }else {
      output[i] = input[i];
    }
  }
  return output;
}

char * trim(const char * input){
  char * ltrimmed = ltrim(input);
  char * rtrimmed = rtrim(ltrimmed);
  free(ltrimmed);
  return rtrimmed;
}

char * rtrim(const char * input){
  char * output;
  regex_t reg;
  regmatch_t match;
  int reti;

  if(!regcomp(&reg, "([^[:space:];])[[:space:]]*\\\\?[g;[:space:]]+$", REG_EXTENDED | REG_ICASE)){
    reti = regexec(&reg, input, 1, &match, 0);
    if(!reti){
      output = (char *)malloc(sizeof(char) * (match.rm_so + 1));
      strncpy(output, input, match.rm_so + 1);
      output[match.rm_so +1] = '\0';
      return output;
    }
  }
  output = (char *)malloc(sizeof(char) * strlen(input));
  strcpy(output, input); 
  return output;
}

char * ltrim(const char * input){
  char * output;
  regex_t reg;
  regmatch_t match;
  int reti;

  if(!regcomp(&reg, "^[[:space:]]+([^[:space:]])", REG_EXTENDED | REG_ICASE)){
    reti = regexec(&reg, input, 1, &match, 0);
    if(!reti){
      output = (char *)malloc(sizeof(char) * (strlen(input) - match.rm_eo));
      strncpy(output, input + match.rm_eo - 1, strlen(input) - match.rm_eo + 1);
      output[strlen(input) - match.rm_eo] = '\0';
      return output;
    }
  }
  output = (char *)malloc(sizeof(char) * strlen(input));
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
  output[k] = '\0';
  char * retstr = (char *)malloc(sizeof(char) * k);
  strncpy(retstr, output, k);
  retstr[k] = '\0';
  return retstr; 
}