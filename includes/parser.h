//
// Created by keltar on 10/14/17.
//

#ifndef TINY_C_COMPILER_PARSER_H
#define TINY_C_COMPILER_PARSER_H

#include "tokenizer.h"
#include "syntax_tree.h"

class Parser
{
public:
    explicit Parser(Tokenizer *tokenizer);
    Parser();

    void Parse();
    friend std::ostream &operator<<(std::ostream &os, Parser &parser);
private:
    PrimaryExprNode *parsePrimaryExpr();
    PostfixExprNode *parsePostrixExpr();
    PostfixExprNode *parseUnaryExpr();
    PostfixExprNode *parseCastExpr();
    PostfixExprNode *parseMultiplicativeExpr();
    PostfixExprNode *parseAddictiveExpr();
    PostfixExprNode *parseShiftExpr();
    PostfixExprNode *parseRelationalExpr();
    PostfixExprNode *parseEqualityExpr();
    PostfixExprNode *parseAndExpr();
    PostfixExprNode *parseExclusiveOrExpr();
    PostfixExprNode *parseInclusiveOrExpr();

    Tokenizer *scanner;
    SyntaxTree tree;
};

#endif //TINY_C_COMPILER_PARSER_H
