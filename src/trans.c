#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mssql.h"
#include "slre.h"

int is_pretty(char *sql){
    struct slre_cap caps[4];
    if(slre_match("\\\\G\\s*;?\\s*?$", sql, strlen(sql), caps, 4, SLRE_IGNORE_CASE) > 0) {
        return 1;
    }
    return 0;
}

char * format_string(char * sql){
    struct slre_cap caps[4];
    if(slre_match("(\\s?\\\\?g?;?)\\s?$", sql, strlen(sql), caps, 4, SLRE_IGNORE_CASE) > 0) {
        trim_by_pointer(sql, caps[0].ptr);
    }
    
    return sql;
}

char * remove_consective_blank(char * str){
    int i = 0;
    int k = 0;
    char * fstr = (char *)malloc(2048);
    char pre = str[i];
    while(1){
        if(str[i] == '\0'){
            break;
        }
        i++;
    }
    return fstr;
}

/*
 * trim string when the pointer appear
 */
char * trim_by_pointer(char * str, const char * point){
    int i = 0;
    while(1){
        if(&str[i] >= point || str[i] == '\0'){
            str[i] = '\0';
            break;
        }
        i++;
    }
    return str;
}

char * trans_dialect(char * line){
    char * sql;
    char * sqlstr = (char *)malloc(2048); ;
    pretty_print=0;
    struct slre_cap caps[4];

    if (slre_match("^show databases\\s*(\\\\g;?|;)\\s*$", line, strlen(line), caps, 4, SLRE_IGNORE_CASE) > 0) {
        sprintf(sqlstr, "SELECT name AS DBName FROM master.dbo.sysdatabases WHERE dbid > 4 %s", caps[0].ptr);
    }else if (slre_match("^show tables\\s*(\\\\g;?|;)\\s*$", line, strlen(line), caps, 4, SLRE_IGNORE_CASE) > 0) {
        sprintf(sqlstr, "SELECT name AS Tables FROM sysobjects WHERE xtype = 'U' %s", caps[0].ptr);
    }else if (slre_match("^show tables\\s+like\\s+([%'\"a-z]+)(\\\\g;?|;)\\s*$", line, strlen(line), caps, 4, SLRE_IGNORE_CASE) > 0) {
        char * tmp = (char *)malloc(1024);
        strncpy(tmp, caps[0].ptr, caps[0].len);
        sprintf(sqlstr, "SELECT name AS Tables FROM sysobjects WHERE xtype = 'U' AND name LIKE %s ORDER BY name;", tmp);
        free(tmp);
    }else if (slre_match("^show tables\\s*(\\\\g;?|;)\\s*$", line, strlen(line), caps, 4, SLRE_IGNORE_CASE) > 0) {
        sprintf(sqlstr, "SELECT name AS Tables FROM sysobjects WHERE xtype = 'U' ORDER BY name %s", caps[0].ptr);
    }else if (slre_match("^show processlist\\s*(\\\\g;?|;)\\s*$", line, strlen(line), caps, 4, SLRE_IGNORE_CASE) > 0) {
        sprintf(sqlstr, " SELECT "
            "es.session_id AS sess_id, "
            "er.request_id AS req_id, "
            "er.command, "
            "es.status, "
            "DB_NAME(DB_ID()) AS database_name, "
            "er.wait_time, "
            "er.open_resultset_count AS result_set, "
            "es.total_elapsed_time AS elapsed_time, "
            "es.cpu_time, "
            "es.memory_usage, "
            "es.lock_timeout, "
            "es.host_name, "
            "es.program_name, "
            "es.login_name "
         " FROM "
            "sys.dm_exec_sessions es "
            "LEFT JOIN "
            "sys.dm_exec_requests er "
            "ON "
            "es.session_id = er.session_id "
            "LEFT JOIN "
            "(SELECT * FROM sys.dm_exec_connections WHERE most_recent_sql_handle <> 0x0) AS ec "
            "ON "
            "es.session_id = ec.session_id "
            "OUTER APPLY "
            "sys.dm_exec_sql_text(er.sql_handle) AS er_text "
            "OUTER APPLY "
            "sys.dm_exec_sql_text(ec.most_recent_sql_handle) AS ec_text "
         " WHERE "
            "es.session_id <> @@SPID "
         " ORDER BY "
            "sess_id ASC %s", caps[0].ptr);
    }else if (slre_match("^descr?i?b?e? ([^;\\s\\\\]+)\\s*(\\\\g;?|;)\\s*$", line, strlen(line), caps, 4, SLRE_IGNORE_CASE) > 0) {
        sprintf(sqlstr,"SELECT " 
        "    c.name 'Column Name',"
        "    t.Name 'Data type',"
        "    c.max_length 'Max Length',"
        "    c.is_nullable,"
        "    c.collation_name 'COLLATE',"
        "    ISNULL(i.is_primary_key, 0) 'Primary Key' "
        "FROM    "
        "    sys.columns c "
        "INNER JOIN "
        "    sys.types t ON c.user_type_id = t.user_type_id "
        "LEFT OUTER JOIN "
        "    sys.index_columns ic ON ic.object_id = c.object_id AND ic.column_id = c.column_id AND ic.index_id=1 "
        "LEFT OUTER JOIN "
        "    sys.indexes i ON ic.object_id = i.object_id AND ic.index_id = i.index_id "
        "WHERE"
        "    c.object_id = OBJECT_ID('%.*s') %.*s", caps[0].len, caps[0].ptr, caps[1].len, caps[1].ptr);
    }else{
        sqlstr=NULL;
    }

    if (sqlstr) {
        sql = (char *)malloc(strlen(sqlstr));
        strcpy(sql, sqlstr);
        free(sqlstr);
    }else{
        sql = (char *)malloc(strlen(line));
        strcpy(sql, line);
    }
    //check for print type
    if(slre_match("\\\\G\\s*;?$", sql, strlen(sql), caps, 4, 0) > 0) {
        pretty_print = 1;
        char * pos = strstr(sql, "\\G");
        * pos = '\0';
    }else if(slre_match("\\\\g\\s*;?$", sql, strlen(sql), caps, 4, 0) > 0) {
        char * pos = strstr(sql, "\\g");
        * pos = '\0';
    }
    return sql;
}
