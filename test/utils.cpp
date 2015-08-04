#include <gtest/gtest.h>
#include <gmock/gmock.h>
extern "C"
{
#include "./test.h"
}

using ::testing::StartsWith;
using ::testing::StrEq;

TEST(UtilsTest, TestRemoveConsectiveBlank)
{
    char * output;

    const char input[] = "show  databases;";
    output = remove_consective_blank(input);
    EXPECT_THAT(output, StrEq("show databases;"));
    free(output);

    const char input2[] = "SELECT  *    FROM  HOGE;";
    output = remove_consective_blank(input2);
    EXPECT_THAT(output, StrEq("SELECT * FROM HOGE;"));
    free(output);
}

TEST(UtilsTest, TestRtrim)
{
    char input[] = "hoge;   ";
    EXPECT_THAT(rtrim(input), StrEq("hoge"));

    char input2[] = "hoge2;   ";
    EXPECT_THAT(rtrim(input2), StrEq("hoge2"));

    char input3[] = "hoge3\\G; \r\t \n ";
    EXPECT_THAT(rtrim(input3), StrEq("hoge3"));

    char input4[] = "hoge4 ;\\G; \r\t \n ";
    EXPECT_THAT(rtrim(input4), StrEq("hoge4"));
}

TEST(UtilsTest, TestLtrim)
{
    char input[] = "   hoge;";
    EXPECT_THAT(ltrim(input), StrEq("hoge;"));

    char input2[] = "\r\n\t  hoge2;";
    EXPECT_THAT(ltrim(input2), StrEq("hoge2;"));
}

TEST(UtilsTest, TestTrim)
{
    char input[] = "   hoge;   ";
    EXPECT_THAT(trim(input), StrEq("hoge"));

    char input2[] = "\r\n\t  hoge2 ;\\G; \r\t \n ";
    EXPECT_THAT(trim(input2), StrEq("hoge2"));
}

TEST(UtilsTest, TestReplaceSpace)
{
    char input[] = "\r\n\t  ho\r\nge; \r\n\t \r g";
    EXPECT_THAT(replaceSpace(input), StrEq("     ho  ge;       g"));

}

TEST(UtilsTest, TestNormalize)
{
    char input[] = "\r\n\t  ho\r\nge; \r\n\t \r ";
    EXPECT_THAT(normalize(input), StrEq("ho ge"));

    char input2[] = "\r \n \t  ho \r\n ge \\G; \r\n\t \r ";
    EXPECT_THAT(normalize(input2), StrEq("ho ge"));
}

TEST(UtilsTest, TestIsPretty)
{
    char input[] = "show tables\\G";
    EXPECT_TRUE(is_pretty(input));

    char input2[] = "show tables\\G;";
    EXPECT_TRUE(is_pretty(input2));

    char input3[] = "show tables   \\G;";
    EXPECT_TRUE(is_pretty(input3));

    char input4[] = "show tables   ;\\G;";
    EXPECT_FALSE(is_pretty(input4));

    char input5[] = "show tables;";
    EXPECT_FALSE(is_pretty(input5));

    char input6[] = "show tables ;";
    EXPECT_FALSE(is_pretty(input6));

    char input7[] = "show tables ; ";
    EXPECT_FALSE(is_pretty(input7));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
