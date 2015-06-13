#include <gtest/gtest.h>
#include <gmock/gmock.h>
extern "C"
{
#include "../src/mssql.h"
}

using ::testing::StartsWith;

TEST(QueryTranslateTest, ShowTables)
{
    char * testquery = (char *)malloc(2048);
    char * resquery  = (char *)malloc(2048);
    sprintf(testquery, "show tables;");
    resquery = trans_dialect(testquery);
    EXPECT_THAT(resquery, StartsWith("SELECT name AS Tables FROM sysobjects"));
}

TEST(SetConstructTest2, ConstructFromArray2)
{
    EXPECT_THAT("Hello", StartsWith("Hello"));
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
