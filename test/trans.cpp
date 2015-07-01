#include <gtest/gtest.h>
#include <gmock/gmock.h>
extern "C"
{
#include "../src/mssql.h"
}

using ::testing::StartsWith;
using ::testing::StrEq;

TEST(QueryTranslateTest, ShowTables)
{
    char * testquery = (char *)malloc(2048);
    char * resquery  = (char *)malloc(2048);
    sprintf(testquery, "show tables;");
    resquery = trans_dialect(testquery);
    EXPECT_THAT(resquery, StartsWith("SELECT name AS Tables FROM sysobjects"));
}

TEST(QueryTranslateTest, ShowDatabases)
{
    char * testquery = (char *)malloc(2048);
    char * resquery  = (char *)malloc(2048);
    sprintf(testquery, "show databases;");
    resquery = trans_dialect(testquery);
    EXPECT_THAT(resquery, StartsWith("SELECT name AS DBName FROM master.dbo.sysdatabases"));
}

//TEST(TransFunctionTest, TestRemoveConsectiveBlank)
//{
//    char * sql = (char *)malloc(128);
//    sprintf(sql, "show  databases;");
//    sql = remove_consective_blank(sql);
//    EXPECT_THAT(sql, StrEq("show  databases"));
//
//    sprintf(sql, "SELECT   *  FROM    HOGE;");
//    sql = remove_consective_blank(sql);
//    EXPECT_THAT(sql, StrEq("SELECT * FROM HOGE;"));
//}

TEST(TransFunctionTest, TestFormatString)
{
    char * sql = (char *)malloc(128);
    sprintf(sql, "show databases;");
    sql = format_string(sql);
    EXPECT_THAT(sql, StrEq("show databases"));


    sprintf(sql, "show databases\\g;");
    format_string(sql);
    EXPECT_THAT(sql, StrEq("show databases"));

    sprintf(sql, "show databases \\g; ");
    format_string(sql);
    EXPECT_THAT(sql, StrEq("show databases"));

    sprintf(sql, "show databases ; ");
    sql = format_string(sql);
    EXPECT_THAT(sql, StrEq("show databases"));

//    sprintf(sql, "show  databases ; ");
//    sql = format_string(sql);
//    EXPECT_THAT(sql, StrEq("show databases"));
//
//    sprintf(sql, "show   databases ; ");
//    sql = format_string(sql);
//    EXPECT_THAT(sql, StrEq("show databases"));
//
//    sprintf(sql, "show \r \n  databases ; ");
//    sql = format_string(sql);
//    EXPECT_THAT(sql, StrEq("show databases"));
}

TEST(TransFunctionTest, TestIsPretty)
{
    char * str = (char *)malloc(1024);
    sprintf(str, "SELECT * FROM fuga\\G");
    ASSERT_TRUE(is_pretty(str));
    sprintf(str, "SELECT * FROM fuga\\g");
    ASSERT_TRUE(is_pretty(str));
    sprintf(str, "SELECT * FROM fuga\\G;");
    ASSERT_TRUE(is_pretty(str));
    sprintf(str, "SELECT * FROM fuga\\g;");
    ASSERT_TRUE(is_pretty(str));
    sprintf(str, "SELECT * FROM fuga \\G");
    ASSERT_TRUE(is_pretty(str));
    sprintf(str, "SELECT * FROM fuga\\G ");
    ASSERT_TRUE(is_pretty(str));
    sprintf(str, "SELECT * FROM fuga \\G ");
    ASSERT_TRUE(is_pretty(str));
    sprintf(str, "SELECT * FROM fuga \\G;");
    ASSERT_TRUE(is_pretty(str));
    sprintf(str, "SELECT * FROM fuga\\G; ");
    ASSERT_TRUE(is_pretty(str));
    sprintf(str, "SELECT * FROM fuga \\G; ");
    ASSERT_TRUE(is_pretty(str));

    sprintf(str, "SELECT * FROM fuga;");
    ASSERT_FALSE(is_pretty(str));
    sprintf(str, "SELECT * FROM fuga ;");
    ASSERT_FALSE(is_pretty(str));
    sprintf(str, "SELECT * FROM fuga; ");
    ASSERT_FALSE(is_pretty(str));
    sprintf(str, "SELECT * FROM fuga ; ");
    ASSERT_FALSE(is_pretty(str));
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
