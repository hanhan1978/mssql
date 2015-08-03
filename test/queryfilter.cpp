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
    char * resquery;
    sprintf(testquery, "show tables");
    resquery = trans_dialect(testquery);
    EXPECT_THAT(resquery, StartsWith("SELECT name AS Tables FROM sysobjects"));
}

TEST(TransFunctionTest, TestRemoveConsectiveBlank)
{
    char * output2;
    const char input2[] = "show  databases;";
    output2 = remove_consective_blank(input2);
    
    EXPECT_THAT(output2, StrEq("show databases;"));

//    char * input = (char *)malloc(128);
//    char * output;
//    sprintf(input, "SELECT  *    FROM  HOGE;");
//    output = remove_consective_blank(input);
//    EXPECT_THAT(output, StrEq("SELECT * FROM HOGE;"));
//    free(input);free(output);

}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
