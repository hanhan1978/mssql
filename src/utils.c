#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

//public
int is_pretty(const char * input);
char * normalize(const char * input);
int need_execution(const char * input);
int is_termination(const char * input);
int is_blank(const char * input);

//private
char * remove_consective_blank(const char *);  
char * rtrim(const char * input);
char * ltrim(const char * input);
char * trim(const char * input);
char * replaceSpace(const char * input);

int is_blank(const char * input){
  regex_t reg;
  regmatch_t match;
  int result = 1;
  if(!regcomp(&reg, "^\\s*$", REG_EXTENDED | REG_ICASE)){
    result = regexec(&reg, input, 1, &match, 0) <= 0;
  }
  return result;
}

char * normalize(const char * input){
  char * replaced = replaceSpace(input);
  char * trimmed = trim(replaced);
  char * normalized = remove_consective_blank(trimmed);
  free(replaced);
  free(trimmed);
  return normalized;
}

int need_execution(const char * input){
  regex_t reg;
  regmatch_t match;
  int result = 0;
  if(!regcomp(&reg, "(\\\\G|;)\\s*$", REG_EXTENDED | REG_ICASE)){
    result = regexec(&reg, input, 1, &match, 0) <= 0;
  }
  return result;
}

int is_termination(const char * input){
  regex_t reg;
  regmatch_t match;
  char * temp = normalize(input);
  int result = 0;
  if(!regcomp(&reg, "^(\\\\q|exit)$", REG_EXTENDED)){
    result = regexec(&reg, temp, 1, &match, 0) <= 0;
  }
  free(temp);
  return result;
}

int is_pretty(const char * input){
  regex_t reg;
  regmatch_t match;

  if(!regcomp(&reg, "([^[:space:];])[[:space:]]*\\\\g[;[:space:]]*$", REG_EXTENDED | REG_ICASE)){
    return regexec(&reg, input, 1, &match, 0) <= 0;
  }
  return 0;
}

char * replaceSpace(const char * input){
  int i = 0;
  char * output = (char *) malloc (sizeof(char) * (strlen(input) + 1));
  for(i ; i<strlen(input); i++){
    if(input[i] == '\n' || input[i] == '\t' || input[i] == '\r'){
      output[i] = ' ';
    }else {
      output[i] = input[i];
    }
    output[strlen(input)] = '\0';
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

  if(!regcomp(&reg, "([^[:space:];])[;[:space:]]*\\\\?[g;[:space:]]+$", REG_EXTENDED | REG_ICASE)){
    reti = regexec(&reg, input, 1, &match, 0);
    if(!reti){
      output = (char *)malloc(sizeof(char) * (match.rm_so + 2)); //added 2 just in case
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
      output = (char *)malloc(sizeof(char) * (strlen(input) - match.rm_eo + 2));//2 is buffer...
      strncpy(output, input + match.rm_eo - 1, strlen(input) - match.rm_eo + 1);
      output[strlen(input) - match.rm_eo + 1] = '\0';
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