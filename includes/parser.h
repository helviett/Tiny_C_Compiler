//
// Created by keltar on 10/14/17.
//

#ifndef TINY_C_COMPILER_PARSER_H
#define TINY_C_COMPILER_PARSER_H

#include "tokenizer.h"
#include "syntax_tree.h"
#include <functional>

static std::unordered_set<std::string> TypeSpecifiers =
{
    "void", "char", "short", "int", "long", "float", "double", "singed", "unsigned"
};

static std::unordered_set<std::string> TypeQualifiers =
{
        "volatile", "const", "restrict"
};

class Parser
{
public:
    explicit Parser(Tokenizer *tokenizer);
    Parser();

    void Parse();
    friend std::ostream &operator<<(std::ostream &os, Parser &parser);
private:
    PostfixExprNode *parsePrimaryExpr();
    PostfixExprNode *parsePostfixExpr();
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
    PostfixExprNode *parseLogicalAndExpr();
    PostfixExprNode *parseLogicalOrExpr();
    PostfixExprNode *parseConditionalExpr();
    PostfixExprNode *parseAssignmentExpr();
    PostfixExprNode *parseExpr();
    TypeNameNode    *parseTypeName();

    PostfixExprNode *parseGeneral(Parser *self, PostfixExprNode *(Parser::*f)(),
                                  std::unordered_set<TokenType> types);
    bool isTypeSpecifier(Token *token);
    bool isUnaryOp(Token *token);
    bool isAssignmentOp(Token *token);
    bool isTypeQualifier(Token *token);

    Tokenizer *scanner;
    SyntaxTree tree;
};

#endif //TINY_C_COMPILER_PARSER_H
