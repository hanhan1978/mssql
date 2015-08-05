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

    const char query2[] ="show tables";
    EXPECT_THAT(trans_dialect(query2), StartsWith("SELECT name AS Tables FROM sysobjects"));

    const char query3[] ="show tables";
    EXPECT_THAT(trans_dialect(query3), StartsWith("SELECT name AS Tables FROM sysobjects"));

    const char query4[] ="show tables";
    EXPECT_THAT(trans_dialect(query4), StartsWith("SELECT name AS Tables FROM sysobjects"));
    
    const char query5[] ="show tables";
    EXPECT_THAT(trans_dialect(query5), StartsWith("SELECT name AS Tables FROM sysobjects"));
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
