//
// Created by keltar on 10/9/17.
//

#include <gtest/gtest.h>
#include "token.h"
#include "tokenizer.h"


class TokenizerTest: public ::testing::Test
{
protected:
    Tokenizer T;
};

TEST_F(TokenizerTest, IDs)
{
    T.OpenFile("test_src/0.cpp");
    auto t = T.Next();
    EXPECT_EQ(t->type, ID);
}