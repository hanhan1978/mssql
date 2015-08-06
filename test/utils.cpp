#include <gtest/gtest.h>
#include <gmock/gmock.h>
extern "C"
{
#include "./test.h"
}

using ::testing::StartsWith;
using ::testing::StrEq;

TEST(UtilsTest, TestIsBlank)
{
    char input1[] = "";
    EXPECT_TRUE(is_blank(input1));
    char input2[] = " ";
    EXPECT_TRUE(is_blank(input2));
    char input3[] = "  ";
    EXPECT_TRUE(is_blank(input3));
    char input4[] = "a";
    EXPECT_FALSE(is_blank(input4));
}

TEST(UtilsTest, TestNeedExecution)
{
    char input[] = "show tables\\G";
    EXPECT_TRUE(need_execution(input));

    char input2[] = "show tables \\G  ";
    EXPECT_TRUE(need_execution(input2));

    char input3[] = "show tables \\G ; ";
    EXPECT_TRUE(need_execution(input3));

    char input4[] = "show tables;";
    EXPECT_TRUE(need_execution(input4));

    char input5[] = "show tables ;";
    EXPECT_TRUE(need_execution(input5));

    char input6[] = "show tables ; ";
    EXPECT_TRUE(need_execution(input6));

    char input7[] = "show tables";
    EXPECT_FALSE(need_execution(input7));
}

TEST(UtilsTest, TestIsTermination)
{

    char input1[] = "exit";
    EXPECT_TRUE(is_termination(input1));
    char input2[] = "\\q";
    EXPECT_TRUE(is_termination(input2));
    char input3[] = " exit ";
    EXPECT_TRUE(is_termination(input3));
    char input4[] = " exit; ";
    EXPECT_TRUE(is_termination(input4));
    char input5[] = " exit\\G ";
    EXPECT_TRUE(is_termination(input5));
    char input6[] = " \\q\\G ";
    EXPECT_TRUE(is_termination(input6));
    char input7[] = " \\q; ";
    EXPECT_TRUE(is_termination(input7));
    char input8[] = "do exit ";
    EXPECT_FALSE(is_termination(input8));
    char input9[] = "do \\q ";
    EXPECT_FALSE(is_termination(input9));
    char input10[] = "do hoge ";
    EXPECT_FALSE(is_termination(input10));

}

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
