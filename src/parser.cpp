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
    tree.root = parseExpr();
}

ExprNode *Parser::parseExpr()
{
    ExprNode *e = parseTerm();
    Token *t = scanner->Current();
    while (t->type == TokenType::PLUS || t->type == TokenType::MINUS)
    {
        scanner->Next();
        return new BinOpNode(t, e, parseExpr());
    }
    return e;
}

ExprNode *Parser::parseTerm()
{
    ExprNode *e = parseFactor();
    Token *t = scanner->Current();
    while (t->type == TokenType::ASTERIX || t->type == TokenType::FORWARD_SLASH)
    {
        scanner->Next();
        return new BinOpNode(t, e, parseTerm());
    }
    return e;
}

ExprNode *Parser::parseFactor()
{
    Token *t = scanner->Current();
    if (t->type == TokenType::ID)
    {
        //return IdNode;
    }
    if (t->type == TokenType::NUM_INT)
    {
        scanner->Next();
        return new IntConstNode(t->intValue);
    }
    if (t->type == TokenType::LBRACKET)
    {
        scanner->Next();
        ExprNode *e = parseExpr();
        if (scanner->Current()->type != TokenType::RBRACKET)
            throw "";
        scanner->Next();
        return e;
    }
    throw "";
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
