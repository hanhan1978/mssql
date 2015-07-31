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
    char * testquery = (char *)malloc(2048);
    char * resquery  = (char *)malloc(2048);
    sprintf(testquery, "show tables;");
    trans_dialect(resquery, testquery);
    EXPECT_THAT(resquery, StartsWith("SELECT name AS Tables FROM sysobjects"));
}

TEST(TransFunctionTest, TestRemoveConsectiveBlank)
{
    char * sql = (char *)malloc(128);
    sprintf(sql, "SELECT  *    FROM  HOGE;");
    sql = remove_consective_blank(sql);
    EXPECT_THAT(sql, StrEq("SELECT * FROM HOGE;"));

    sql = (char *)malloc(128);
    sprintf(sql, "show  databases;");
    sql = remove_consective_blank(sql);
    EXPECT_THAT(sql, StrEq("show databases;"));
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
