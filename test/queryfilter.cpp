#include <gtest/gtest.h>
#include <gmock/gmock.h>
extern "C"
{
#include "./test.h"
}

using ::testing::StartsWith;
using ::testing::StrEq;

TEST(QueryTranslateTest, ShowTables)
{
    const char query[] ="show tables";
    EXPECT_THAT(trans_dialect(query), StartsWith("SELECT name AS Tables FROM sysobjects"));

    const char query2[] ="show databases";
    EXPECT_THAT(trans_dialect(query2), StartsWith("SELECT name AS DBName FROM master.dbo.sysdatabases WHERE dbid > 4"));

    const char query3[] ="show tables like 'hoge%'";
    EXPECT_THAT(trans_dialect(query3), StartsWith("SELECT name AS Tables FROM sysobjects WHERE xtype = 'U' AND name LIKE %s ORDER BY name"));

    const char query4[] ="show processlist";
    EXPECT_THAT(trans_dialect(query4), StartsWith("SELECT es.session_id AS sess_id, er.request_id AS req_id, er.command, es.status, DB_NAME(DB_ID()) AS database_name, er.wait_time, er.open_resultset_count AS result_set, es.total_elapsed_time AS elapsed_time, es.cpu_time, es.memory_usage, es.lock_timeout, es.host_name, es.program_name, es.login_name FROM sys.dm_exec_sessions es LEFT JOIN sys.dm_exec_requests er ON es.session_id = er.session_id LEFT JOIN (SELECT * FROM sys.dm_exec_connections WHERE most_recent_sql_handle <> 0x0) AS ec ON es.session_id = ec.session_id OUTER APPLY sys.dm_exec_sql_text(er.sql_handle) AS er_text OUTER APPLY sys.dm_exec_sql_text(ec.most_recent_sql_handle) AS ec_text WHERE es.session_id <> @@SPID ORDER BY sess_id ASC"));
    
    const char query5[] ="describe hoge";
    EXPECT_THAT(trans_dialect(query5), StartsWith("SELECT c.name 'Column Name', t.Name 'Data type', c.max_length 'Max Length', c.is_nullable 'NULL', c.collation_name 'COLLATE', ISNULL(i.is_primary_key, 0) 'Primary Key' FROM sys.columns c INNER JOIN sys.types t ON c.user_type_id = t.user_type_id LEFT OUTER JOIN sys.index_columns ic ON ic.object_id = c.object_id AND ic.column_id = c.column_id AND ic.index_id=1 LEFT OUTER JOIN sys.indexes i ON ic.object_id = i.object_id AND ic.index_id = i.index_id WHERE c.object_id = OBJECT_ID('%s')"));

}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
