//
// Created by keltar on 10/14/17.
//

#include "../includes/parser.h"

Parser::Parser() = default;

Parser::Parser(Tokenizer *tokenizer)
{
    scanner = tokenizer;
}

void Parser::Parse()
{
    scanner->Next();
    tree.root = parsePrimaryExpr();
}

PrimaryExprNode *Parser::parsePrimaryExpr()
{
    Token *t = scanner->Current();
    switch (t->type)
    {
        case TokenType::NUM_INT:
            scanner->Next();
            return new IntConstNode(t);
        case TokenType::NUM_FLOAT:
            scanner->Next();
            return new FloatConstNode(t);
        case TokenType::ID:
            scanner->Next();
            return new IdNode(t);
        case TokenType::STRING:
            scanner->Next();
            return new StringLiteralNode(t);
        case TokenType::LBRACKET:
            scanner->Next();
            PrimaryExprNode *e = parsePrimaryExpr();
            if (scanner->Current()->type != TokenType::RBRACKET)
                throw SyntaxError(t, "Missing closing bracket. ");
            scanner->Next();
            return e;
    }
    throw SyntaxError(t, "Missing operand. ");
}

void Parser::Print()
{
    tree.Print();
}

std::ostream &operator<<(std::ostream &os, Parser &parser)
{
    os << parser.tree;
    return os;
}
