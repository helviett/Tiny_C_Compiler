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
    tree.root = parseDeclarator();
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
    if (scanner->Current()->type == TokenType::LBRACKET)
    {
        scanner->Next();
        TypeNameNode *typName = parseTypeName();
        if (scanner->Current()->type != TokenType::RBRACKET) throw "";
        scanner->Next();
        return new TypeCastNode(typName, parseCastExpr());
    }
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
    PostfixExprNode *ae = parseAssignmentExpr();
    while (scanner->Current()->type == TokenType::COMMA)
    {
        scanner->Next();
        ae = new CommaSeparatedExprs(ae, parseExpr());
    }
    return ae;
}

TypeNameNode *Parser::parseTypeName()
{
    auto tnn = new SpecifierQualifierListNode();
    Token *t = scanner->Current();
    bool spec;
    while ((spec = isTypeSpecifier(t)) || isTypeQualifier(t))
    {

        tnn->Add(spec ? (TypeSpecifierQualifier *)new TypeSpecifier(t) :
                              (TypeSpecifierQualifier *)new TypeQualifier(t)) ;
        t = scanner->Next();
    }
    if (tnn->Size() == 0) throw "";
    return (TypeNameNode *)tnn;
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

PostfixExprNode *Parser::parseConstantExpr()
{
    return parseConditionalExpr();
}

TypeQualifierListNode *Parser::parseTypeQualifierList()
{
    auto tql = new TypeQualifierListNode();
    Token *t = scanner->Current();
    while (isTypeQualifier(t))
    {

        tql->Add(new TypeQualifier(t));
        t = scanner->Next();
    }
    return tql;
}

PointerNode *Parser::parsePointer()
{
    if (scanner->Current()->type != TokenType::ASTERIX) return nullptr;
    scanner->Next();
    return new PointerNode(parseTypeQualifierList(), parsePointer());
}

StatementNode *Parser::parseStatement()
{
    if (scanner->Current()->type == TokenType::KEYWORD)
        switch (scanner->Current()->keyword)
        {
            case Keyword::IF:
                return parseSelectionStatement();
            case Keyword::GOTO: case Keyword::CONTINUE: case Keyword::BREAK:
            case Keyword::RETURN:
                return parseJumpStatement();
            case Keyword::FOR: case Keyword::DO: case Keyword::WHILE:
                return parseIterationStatement();
        }
    return reinterpret_cast<StatementNode *>(parseExprStatement());
}

ExprStatmentNode *Parser::parseExprStatement()
{
    if (scanner->Current()->type == TokenType::SEMICOLON)
    {
        scanner->Next();
        return new ExprStatmentNode(nullptr);
    }
    auto et = new ExprStatmentNode(parseExpr());
    if (scanner->Current()->type != TokenType::SEMICOLON) throw "";
    scanner->Next();
    return et;
}

SelectionStatementNode *Parser::parseSelectionStatement()
{
    if (scanner->Current()->type != TokenType::KEYWORD || scanner->Current()->keyword != Keyword::IF) throw "";
    scanner->Next();
    if (scanner->Current()->type != TokenType::LBRACKET) throw "";
    scanner->Next();
    auto expr = parseExpr();
    if (scanner->Current()->type != TokenType::RBRACKET) throw "";
    scanner->Next();
    auto then = parseStatement();
    if (scanner->Current()->type == TokenType::KEYWORD && scanner->Current()->keyword == Keyword::ELSE)
    {
        scanner->Next();
        return new IfElseStatementNode(expr, then, parseStatement());
    }
    return new IfStatementNode(expr, then);
}

JumpStatementNode *Parser::parseJumpStatement()
{
    JumpStatementNode *js = nullptr;
    if (scanner->Current()->type == TokenType::KEYWORD)
        switch (scanner->Current()->keyword)
        {
            case Keyword::GOTO:
                if (scanner->Next()->type != TokenType::ID) throw "";
                js = new GotoStatementNode(new IdNode(scanner->Current()));
                scanner->Next();
                break;
            case Keyword::CONTINUE:
                scanner->Next()->type;
                js = new ContinueStatementNode();
                break;
            case Keyword::BREAK:
                scanner->Next()->type;
                js = new BreakStatementNode();
                break;
            case Keyword::RETURN:
                js = scanner->Next()->type == TokenType::SEMICOLON ? new ReturnStatementNode(nullptr) :
                     new ReturnStatementNode(parseExpr());
                break;
            default:
                throw "";
        }
    if (scanner->Current()->type != TokenType::SEMICOLON) throw "";
    scanner->Next();
    return js;
}

IterationStatementNode *Parser::parseIterationStatement()
{
    if (scanner->Current()->type != TokenType::KEYWORD) throw "";
    switch (scanner->Current()->keyword)
    {
        case Keyword::FOR:
            return parseForStatement();
        case Keyword::DO:
            return parseDoWhileStatement();
        case Keyword::WHILE:
            return parseWhileStatement();

    }
}

ForStatementNode *Parser::parseForStatement()
{
    if (scanner->Current()->type != TokenType::KEYWORD || scanner->Current()->keyword != Keyword::FOR) throw "";
    if (scanner->Next()->type != TokenType::LBRACKET) throw "";
    scanner->Next();
    auto init = parseExprStatement(), condition = parseExprStatement();
    if (scanner->Current()->type == TokenType::RBRACKET)
    {
        scanner->Next();
        return new ForStatementNode(init, condition, nullptr, parseStatement());
    }
    auto iteration = parseExpr();
    if (scanner->Current()->type != TokenType::RBRACKET) throw "";
    scanner->Next();
    return new ForStatementNode(init, condition, iteration, parseStatement());
}

WhileStatementNode *Parser::parseWhileStatement()
{
    if (scanner->Current()->type != TokenType::KEYWORD || scanner->Current()->keyword != Keyword::WHILE) throw "";
    if (scanner->Next()->type != TokenType::LBRACKET) throw "";
    scanner->Next();
    auto condition = parseExpr();
    if (scanner->Current()->type != TokenType::RBRACKET) throw "";
    scanner->Next();
    return new WhileStatementNode(condition, parseStatement());
}

DoWhileStatementNode *Parser::parseDoWhileStatement()
{
    if (scanner->Current()->type != TokenType::KEYWORD || scanner->Current()->keyword != Keyword::DO) throw "";
    scanner->Next();
    auto body = parseStatement();
    if (scanner->Current()->type != TokenType::KEYWORD || scanner->Current()->keyword != Keyword::WHILE) throw "";
    if (scanner->Next()->type != TokenType::LBRACKET) throw "";
    scanner->Next();
    auto condition = parseExpr();
    if (scanner->Current()->type != TokenType::RBRACKET) throw "";
    if (scanner->Next()->type != TokenType::SEMICOLON) throw "";
    scanner->Next();
    return new DoWhileStatementNode(condition, body);
}

DeclaratorNode *Parser::parseDeclarator()
{
    PointerNode *pointer = nullptr;
    if (scanner->Current()->type == TokenType::ASTERIX) pointer = parsePointer();
    return new DeclaratorNode(pointer, parseDirectDeclarator());
}

DirectDeclaratorNode *Parser::parseDirectDeclarator()
{
    if (scanner->Current()->type == TokenType::LBRACKET)
    {
        scanner->Next();
        auto declarator = parseDeclarator();
        if (scanner->Current()->type != TokenType::RBRACKET) throw "";
        scanner->Next();
        return (DirectDeclaratorNode *)declarator;
    }
    else if (scanner->Current()->type != TokenType::ID) throw "";
    DirectDeclaratorNode *directDeclarator = (DirectDeclaratorNode *)new IdNode(scanner->Current());
    scanner->Next();
    while (scanner->Current()->type == TokenType::LSQUARE_BRACKET)
    {
        directDeclarator = parseArrayDeclarator(directDeclarator);
    }
    return directDeclarator;
}

ArrayDeclaratorNode *Parser::parseArrayDeclarator(DirectDeclaratorNode *directDeclarator)
{
    if (scanner->Current()->type == TokenType::RSQUARE_BRACKER)
        return new ArrayDeclaratorNode(directDeclarator, nullptr);
    scanner->Next();
    auto ce = parseConstantExpr();
    if (scanner->Current()->type != TokenType::RSQUARE_BRACKER) throw "";
    scanner->Next();
    return new ArrayDeclaratorNode(directDeclarator, (ConditionalExprNode *)(ce));
}
