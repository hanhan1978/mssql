#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>


char * trans_dialect(const char *); //public

int regex_size();

//int main (){
//
//  char * output;
//  output = trans_dialect("show tables like 'fuga%'");
//  printf("sql -> %s\n", output);
//
//  output = trans_dialect("show tables");
//  printf("sql -> %s\n", output);
//
//  output = trans_dialect("desc hoge");
//  printf("sql -> %s\n", output);
//}

typedef struct dialect{
    char *regex;
    char *sql;
} dialect;

int regex_size(){
  return 6;
}

dialect * get_regex(){
  int reg_size = regex_size();
  struct dialect * da = (struct dialect *)malloc(sizeof(struct dialect) * reg_size);

  int i = 0;
  for(i; i < reg_size; i++){
    da[i].regex = (char *) malloc(512);
    da[i].sql = (char *) malloc(2048);
  }
  strcpy(da[0].regex, "^show databases$");
  strcpy(da[0].sql, "SELECT name AS DBName FROM master.dbo.sysdatabases WHERE dbid > 4");
  strcpy(da[1].regex, "^show tables$");
  strcpy(da[1].sql, "SELECT name AS Tables FROM sysobjects WHERE xtype = 'U' ORDER BY name");
  strcpy(da[2].regex, "^show tables like ([%'\"a-z_-]+)$");
  strcpy(da[2].sql, "SELECT name AS Tables FROM sysobjects WHERE xtype = 'U' AND name LIKE %s ORDER BY name");
  strcpy(da[3].regex, "^show processlist$");
  strcpy(da[3].sql, "SELECT es.session_id AS sess_id, er.request_id AS req_id, er.command, es.status, DB_NAME(DB_ID()) AS database_name, er.wait_time, er.open_resultset_count AS result_set, es.total_elapsed_time AS elapsed_time, es.cpu_time, es.memory_usage, es.lock_timeout, es.host_name, es.program_name, es.login_name FROM sys.dm_exec_sessions es LEFT JOIN sys.dm_exec_requests er ON es.session_id = er.session_id LEFT JOIN (SELECT * FROM sys.dm_exec_connections WHERE most_recent_sql_handle <> 0x0) AS ec ON es.session_id = ec.session_id OUTER APPLY sys.dm_exec_sql_text(er.sql_handle) AS er_text OUTER APPLY sys.dm_exec_sql_text(ec.most_recent_sql_handle) AS ec_text WHERE es.session_id <> @@SPID ORDER BY sess_id ASC");
  strcpy(da[4].regex, "^desc ([%'\"a-z_-]+)$");
  strcpy(da[4].sql, "SELECT c.name 'Column Name', t.Name 'Data type', c.max_length 'Max Length', c.is_nullable 'NULL', c.collation_name 'COLLATE', ISNULL(i.is_primary_key, 0) 'Primary Key' FROM sys.columns c INNER JOIN sys.types t ON c.user_type_id = t.user_type_id LEFT OUTER JOIN sys.index_columns ic ON ic.object_id = c.object_id AND ic.column_id = c.column_id AND ic.index_id=1 LEFT OUTER JOIN sys.indexes i ON ic.object_id = i.object_id AND ic.index_id = i.index_id WHERE c.object_id = OBJECT_ID('%s')");
  strcpy(da[5].regex, "^describe ([%'\"a-z_-]+)$");
  strcpy(da[5].sql, "SELECT c.name 'Column Name', t.Name 'Data type', c.max_length 'Max Length', c.is_nullable 'NULL', c.collation_name 'COLLATE', ISNULL(i.is_primary_key, 0) 'Primary Key' FROM sys.columns c INNER JOIN sys.types t ON c.user_type_id = t.user_type_id LEFT OUTER JOIN sys.index_columns ic ON ic.object_id = c.object_id AND ic.column_id = c.column_id AND ic.index_id=1 LEFT OUTER JOIN sys.indexes i ON ic.object_id = i.object_id AND ic.index_id = i.index_id WHERE c.object_id = OBJECT_ID('%s')");
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

