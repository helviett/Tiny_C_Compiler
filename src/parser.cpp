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

// primary-expr ::= id | constant | string-literal | (expr)

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
            PrimaryExprNode *e = parsePrimaryExpr(); // that's temporary function call;
            if (scanner->Current()->type != TokenType::RBRACKET)
                throw SyntaxError(t, "Missing closing bracket. ");
            scanner->Next();
            return e;
    }
    throw SyntaxError(t, "Missing operand. ");
}


std::ostream &operator<<(std::ostream &os, Parser &parser)
{
    os << parser.tree;
    return os;
}

PostfixExprNode *Parser::parsePostrixExpr()
{
    PostfixExprNode *pe = parsePrimaryExpr();
    Token *t = scanner->Current();
    bool canBeContinued = true;
    while (canBeContinued)
        switch (t->type)
        {
            case TokenType::DOUBLE_PLUS:
                t = scanner->Next();
                pe = new PostfixIncrementNode(pe);
                break;
            case TokenType::DOUBLE_MINUS:
                t = scanner->Next();
                pe = new PostfixDecrementNode(pe);
                break;
            case TokenType::DOT:
                t = scanner->Next();
                if (t->type != TokenType::ID) throw "";
                pe = new StructureOrUnionMemberAccessNode(pe, new IdNode(t));
                t = scanner->Next();
                break;
            case TokenType::ARROW:
                t = scanner->Next();
                if (t->type != TokenType::ID) throw "";
                pe = new StructureOrUnionMemberAccessByPointerNode(pe, new IdNode(t));
                t = scanner->Next();
                break;
            default:
                canBeContinued = false;
        }
    return pe;
}

PostfixExprNode *Parser::parseUnaryExpr()
{
    PostfixExprNode *ue;
    Token *t = scanner->Current();
    switch (t->type)
    {
        case TokenType::DOUBLE_PLUS:
            t = scanner->Next();
            ue = new PrefixIncrementNode(parseUnaryExpr());
            break;
        case TokenType::DOUBLE_MINUS:
            t = scanner->Next();
            ue = new PrefixDecrementNode(parseUnaryExpr());
            break;
        default:
            ue = parsePostrixExpr();
    }
    return ue;
}

PostfixExprNode *Parser::parseCastExpr()
{
    return parseUnaryExpr();
}

PostfixExprNode *Parser::parseMultiplicativeExpr()
{
    static std::unordered_set<TokenType> types = {TokenType::ASTERIX, TokenType::FORWARD_SLASH, TokenType::REMINDER};
    return parseGeneral(this, &Parser::parseCastExpr, types);
}

PostfixExprNode *Parser::parseAddictiveExpr()
{
    static std::unordered_set<TokenType> types = {TokenType::PLUS, TokenType::MINUS};
    return parseGeneral(this, &Parser::parseMultiplicativeExpr, types);
}

PostfixExprNode *Parser::parseShiftExpr()
{
    static std::unordered_set<TokenType> types = {TokenType::BITWISE_LSHIFT, TokenType::BITWISE_RSHIFT};
    return parseGeneral(this, &Parser::parseAddictiveExpr, types);
}

PostfixExprNode *Parser::parseRelationalExpr()
{
    static std::unordered_set<TokenType> types = {TokenType::RELOP_GT, TokenType::RELOP_LT,
                                                  TokenType::RELOP_GE, TokenType::RELOP_LE};
    return parseGeneral(this, &Parser::parseShiftExpr, types);
}

PostfixExprNode *Parser::parseEqualityExpr()
{
    static std::unordered_set<TokenType> types = {TokenType::RELOP_EQ, TokenType::RELOP_NE};
    return parseGeneral(this, &Parser::parseRelationalExpr, types);
}

PostfixExprNode *Parser::parseAndExpr()
{
    static std::unordered_set<TokenType> types = {TokenType::BITWISE_AND};
    return parseGeneral(this, &Parser::parseEqualityExpr, types);
}

PostfixExprNode *Parser::parseExclusiveOrExpr()
{
    static std::unordered_set<TokenType> types = {TokenType::BITWISE_XOR};
    return parseGeneral(this, &Parser::parseAndExpr, types);
}

PostfixExprNode *Parser::parseInclusiveOrExpr()
{
    static std::unordered_set<TokenType> types = {TokenType::BITWISE_OR};
    return parseGeneral(this, &Parser::parseExclusiveOrExpr, types);
}

PostfixExprNode *Parser::parseLogicalAndExpr()
{
    static std::unordered_set<TokenType> types = {TokenType::LOGIC_AND};
    return parseGeneral(this, &Parser::parseInclusiveOrExpr, types);
}

PostfixExprNode *Parser::parseLogicalOrExpr()
{
    static std::unordered_set<TokenType> types = {TokenType::LOGIC_OR};
    return parseGeneral(this, &Parser::parseLogicalAndExpr, types);
}

PostfixExprNode *Parser::parseGeneral(Parser *self, PostfixExprNode *(Parser::*f)(),
                                      std::unordered_set<TokenType> types)
{
    auto *e = (PostfixExprNode *)((*self).*f)();
    Token *t = self->scanner->Current();
    while (types.find(t->type) != types.end())
    {
        self->scanner->Next();
        auto right = (PostfixExprNode *) ((*self).*f)();
        e = new BinOpNode(e, right, t);
        t = self->scanner->Current();
    }
    return e;
}

PostfixExprNode *Parser::parseConditionalExpr()
{
    return parseLogicalOrExpr();
}

PostfixExprNode *Parser::parseAssignmentExpr()
{
    return parseConditionalExpr();
}

PostfixExprNode *Parser::parseExpr()
{
    return parseAssignmentExpr();
}
