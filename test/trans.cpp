#include <gtest/gtest.h>
extern "C"
{
#include "../src/mssql.h"
}

TEST(SetConstructTest, ConstructFromArray)
{
    char * testquery = (char *)malloc(2048);
    char * resquery  = (char *)malloc(2048);
    sprintf(testquery, "show tables;");
    resquery = trans_dialect(testquery);
    printf("%s¥n", resquery);
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
