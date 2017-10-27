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

PostfixExprNode *Parser::parsePrimaryExpr()
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
            PostfixExprNode *e = parseExpr(); // that's temporary function call;
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

PostfixExprNode *Parser::parsePostfixExpr()
{
    Token *t = scanner->Current();
    if (t->type == TokenType::LBRACKET)
    {
        t = scanner->Next();
        auto typeToCast = 0;

    }
    // else
    PostfixExprNode *pe = parsePrimaryExpr();
    t = scanner->Current();
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
            case TokenType::LSQUARE_BRACKET:
                t = scanner->Next();
                pe = new ArrayAccess(pe, parseExpr());
                if ((t = scanner->Current())->type != TokenType::RSQUARE_BRACKER) throw "";
                scanner->Next();
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
        case TokenType::KEYWORD:
            if (t->keyword == Keyword::SIZEOF)
            {
                t = scanner->Next();
                if (t->type == TokenType::LBRACKET)
                {
                    scanner->Next();
                    ue = new SizeofTypeNameNode(parseTypeName());
                    if (scanner->Current()->type != TokenType::RBRACKET) throw "";
                    scanner->Next();
                }
                else
                    ue = new SizeofExprNode(parseUnaryExpr());
            }
            else throw "";
            break;
        default:
            if (isUnaryOp(t))
            {
                scanner->Next();
                ue = new UnaryOpNode(t, parseCastExpr());
                t = scanner->Current();
                break;
            }
            ue = parsePostfixExpr();
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
    PostfixExprNode *loe =  parseLogicalOrExpr();
    Token *t = scanner->Current();
    if (t->type == TokenType::QUESTION_MARK)
    {
        t = scanner->Next();
        PostfixExprNode *then = parseExpr();
        t = scanner->Current();
        if (t->type != TokenType::COLON)
            throw "";
        t = scanner->Next();
        PostfixExprNode *lse = parseConditionalExpr();
        return new TernaryOperatorNode(loe, then, lse);
    }
    return loe;
}

PostfixExprNode *Parser::parseAssignmentExpr()
{
    PostfixExprNode *ce = parseConditionalExpr();
    Token *t = scanner->Current();
    if (isAssignmentOp(t))
    {
        scanner->Next();
        return new AssignmentNode(ce, parseAssignmentExpr(), t);

    }
    return ce;
}

PostfixExprNode *Parser::parseExpr()
{
    return parseAssignmentExpr();
}

TypeNameNode *Parser::parseTypeName()
{
    auto tnn = new TypeNameNode();
    Token *t = scanner->Current();
    bool spec;
    while ((spec = isTypeSpecifier(t)) || isTypeQualifier(t))
    {

        tnn->List().push_back(spec ? (TypeSpecifierQualifier *)new TypeSpecifier(t) :
                              (TypeSpecifierQualifier *)new TypeQualifier(t)) ;
        t = scanner->Next();
    }
    if (tnn->List().size() == 0) throw "";
    return tnn;
}

bool Parser::isTypeSpecifier(Token *token)
{
    if (token->type == TokenType::KEYWORD)
        return TypeSpecifiers.find(token->keyword) != TypeSpecifiers.end();
    return false;
}

bool Parser::isUnaryOp(Token *token)
{

    return token->type == TokenType::MINUS || token->type == TokenType::PLUS || token->type == TokenType::LOGIC_NO
           || token->type == TokenType::BITWISE_NOT || token->type == TokenType::ASTERIX
           || token->type == TokenType::BITWISE_AND;
}

bool Parser::isAssignmentOp(Token *token)
{
    return  token->type == TokenType::ASSIGNMENT || token->type == TokenType::ASSIGNMENT_BY_PRODUCT
            || token->type == TokenType::ASSIGNMENT_BY_QUOTIENT || token->type == TokenType::ASSIGNMENT_BY_REMINDER
            || token->type == TokenType::ASSIGNMENT_BY_SUM || token->type == TokenType::ASSIGNMENT_BY_DIFFERENCE
            || token->type == TokenType::ASSIGNMENT_BY_BITWISE_LSHIFT
            || token->type == TokenType::ASSIGNMENT_BY_BITWISE_RSHIFT
            || token->type == TokenType::ASSIGNMENT_BY_BITWISE_AND
            || token->type == TokenType::ASSIGNMENT_BY_BITWISE_OR
            || token->type == TokenType::ASSIGNMENT_BY_BITWISE_XOR;
}

bool Parser::isTypeQualifier(Token *token)
{
    if (token->type == TokenType::KEYWORD)
        return TypeQualifiers.find(token->keyword) != TypeQualifiers.end();
    return false;
}
