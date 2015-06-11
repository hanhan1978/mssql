#include <gtest/gtest.h>
#include <gmock/gmock.h>
extern "C"
{
#include "../src/mssql.h"
}

using ::testing::StartsWith;

TEST(SetConstructTest, ConstructFromArray)
{
    char * testquery = (char *)malloc(2048);
    char * resquery  = (char *)malloc(2048);
    sprintf(testquery, "show tables;");
    resquery = trans_dialect(testquery);
    printf("%s¥n", resquery);
}

TEST(SetConstructTest2, ConstructFromArray2)
{
    EXPECT_THAT("Helle", StartsWith("Hello"));
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
