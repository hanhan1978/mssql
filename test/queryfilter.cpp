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
    char * input2 = (char *)malloc(128);
    char * output2;
    sprintf(input2, "show  databases;");
    output2 = remove_consective_blank(input2);
    printf(">>>>>> [%s]\n", output2);
    EXPECT_THAT(output2, StrEq("show databases;"));

    char * input = (char *)malloc(128);
    char * output;
    sprintf(input, "SELECT  *    FROM  HOGE;");
    output = remove_consective_blank(input);
    EXPECT_THAT(output, StrEq("SELECT * FROM HOGE;"));
    printf(">>>>>> [%s]\n", output);
    free(input);free(output);

}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
