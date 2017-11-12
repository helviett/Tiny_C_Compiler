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
    tree.root = parseTranslationUnit();
}


PostfixExprNode *Parser::parsePrimaryExpr()
{
    auto t = scanner->Current();
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
            PostfixExprNode *e = parseExpr();
            require(TokenType::RBRACKET);
            scanner->Next();
            return e;
    }
    throw InvalidExpression(scanner->Current());
}


std::ostream &operator<<(std::ostream &os, Parser &parser)
{
    os << parser.tree;
    return os;
}

PostfixExprNode *Parser::parsePostfixExpr()
{
    auto t = scanner->Current();
    PostfixExprNode *pe = parsePrimaryExpr();
    t = scanner->Current();
    bool stillPostfixOperator = true;
    while (stillPostfixOperator)
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
                require(TokenType::ID);
                pe = new StructureOrUnionMemberAccessNode(pe, new IdNode(t));
                t = scanner->Next();
                break;
            case TokenType::ARROW:
                t = scanner->Next();
                require(TokenType::ID);
                pe = new StructureOrUnionMemberAccessByPointerNode(pe, new IdNode(t));
                t = scanner->Next();
                break;
            case TokenType::LSQUARE_BRACKET:
                t = scanner->Next();
                pe = new ArrayAccess(pe, parseExpr());
                require(TokenType::RSQUARE_BRACKET);
                t = scanner->Next();
                break;
            case TokenType::LBRACKET:
                t = scanner->Next();
                pe = new FunctionCallNode(pe, parseArgumentExprList());
                require(TokenType::RBRACKET);
                t = scanner->Next();
                break;
            default:
                stillPostfixOperator = false;
        }
    return pe;
}

PostfixExprNode *Parser::parseUnaryExpr()
{
    PostfixExprNode *ue;
    auto t = scanner->Current();
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
                    require(TokenType::RBRACKET);
                    scanner->Next();
                }
                else
                    ue = new SizeofExprNode(parseUnaryExpr());
            }
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
    if (scanner->Current()->type == TokenType::LBRACKET &&
            (isTypeQualifier(scanner->Peek()) || isTypeSpecifier(scanner->Peek())))
    {
        scanner->Next();
        TypeNameNode *typName = parseTypeName();
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
    auto *e = (PostfixExprNode *)(self->*f)();
    auto t = self->scanner->Current();
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
    auto t = scanner->Current();
    if (t->type == TokenType::QUESTION_MARK)
    {
        t = scanner->Next();
        PostfixExprNode *then = parseExpr();
        t = scanner->Current();
        require(TokenType::COLON);
        t = scanner->Next();
        PostfixExprNode *lse = parseConditionalExpr();
        return new TernaryOperatorNode(loe, then, lse);
    }
    return loe;
}

PostfixExprNode *Parser::parseAssignmentExpr()
{
    PostfixExprNode *ce = parseConditionalExpr();
    auto t = scanner->Current();
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
    auto tnn = parseSpecifierQualifierList();
    if (tnn->Size() == 0) throw NoDeclarationSpecifiers(scanner->Current());
    auto abstractDeclarator = parseDeclarator(DeclaratorType::ABSTRACT);
    return new TypeNameNode(tnn, abstractDeclarator);
}

bool Parser::isTypeSpecifier(std::shared_ptr<Token> token)
{
    return token->type == TokenType::KEYWORD ? TypeSpecifiers.find(token->keyword) != TypeSpecifiers.end() : false;
}

bool Parser::isUnaryOp(std::shared_ptr<Token> token)
{
    return UnaryOps.find(token->type) != UnaryOps.end();
}

bool Parser::isAssignmentOp(std::shared_ptr<Token> token)
{
    return  AssignmentOps.find(token->type) != AssignmentOps.end();
}

bool Parser::isTypeQualifier(std::shared_ptr<Token> token)
{
    return token->type == TokenType::KEYWORD ? TypeQualifiers.find(token->keyword) != TypeQualifiers.end() : false;
}

PostfixExprNode *Parser::parseConstantExpr()
{
    return parseConditionalExpr();
}

TypeQualifierListNode *Parser::parseTypeQualifierList()
{
    auto tql = new TypeQualifierListNode();
    auto t = scanner->Current();
    while (isTypeQualifier(t))
    {

        tql->Add(new TypeQualifierNode(t));
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
    if (scanner->Current()->type == TokenType::ID && scanner->Peek()->type == TokenType::COLON)
        return parseLabelStatement();
    if (scanner->Current()->type == TokenType::LCURLY_BRACKET)
        return parseCompoundStatement();
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
    require(TokenType::SEMICOLON);
    scanner->Next();
    return et;
}

SelectionStatementNode *Parser::parseSelectionStatement()
{
    requierKeyword(Keyword::IF);
    scanner->Next();
    require(TokenType::LBRACKET);
    scanner->Next();
    auto expr = parseExpr();
    require(TokenType::RBRACKET);
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
    auto t = scanner->Current();
    scanner->Next();
    if (t->type == TokenType::KEYWORD)
        switch (t->keyword)
        {
            case Keyword::GOTO:
                require(TokenType::ID);
                js = new GotoStatementNode(new IdNode(scanner->Current()));
                scanner->Next();
                break;
            case Keyword::CONTINUE:
                js = new ContinueStatementNode();
                break;
            case Keyword::BREAK:
                js = new BreakStatementNode();
                break;
            case Keyword::RETURN:
                js = scanner->Current()->type == TokenType::SEMICOLON ? new ReturnStatementNode(nullptr) :
                     new ReturnStatementNode(parseExpr());
                break;
        }
    require(TokenType::SEMICOLON);
    scanner->Next();
    return js;
}

IterationStatementNode *Parser::parseIterationStatement()
{
    require(TokenType::KEYWORD);
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
    requierKeyword(Keyword::FOR);
    scanner->Next();
    require(TokenType::LBRACKET);
    scanner->Next();
    auto init = parseExprStatement(), condition = parseExprStatement();
    if (scanner->Current()->type == TokenType::RBRACKET)
    {
        scanner->Next();
        return new ForStatementNode(init, condition, nullptr, parseStatement());
    }
    auto iteration = parseExpr();
    require(TokenType::RBRACKET);
    scanner->Next();
    return new ForStatementNode(init, condition, iteration, parseStatement());
}

WhileStatementNode *Parser::parseWhileStatement()
{
    requierKeyword(Keyword::WHILE);
    scanner->Next();
    require(TokenType::LBRACKET);
    scanner->Next();
    auto condition = parseExpr();
    require(TokenType::RBRACKET);
    scanner->Next();
    return new WhileStatementNode(condition, parseStatement());
}

DoWhileStatementNode *Parser::parseDoWhileStatement()
{
    requierKeyword(Keyword::DO);
    scanner->Next();
    auto body = parseStatement();
    requierKeyword(Keyword::WHILE);
    scanner->Next();
    require(TokenType::LBRACKET);
    scanner->Next();
    auto condition = parseExpr();
    require(TokenType::RBRACKET);
    scanner->Next();
    require(TokenType::SEMICOLON);
    scanner->Next();
    return new DoWhileStatementNode(condition, body);
}

DeclaratorNode *Parser::parseDeclarator(DeclaratorType type)
{
    PointerNode *pointer = nullptr;
    if (scanner->Current()->type == TokenType::ASTERIX) pointer = parsePointer();
    return new DeclaratorNode(pointer, parseDirectDeclarator(type));
}

DirectDeclaratorNode *Parser::parseDirectDeclarator(DeclaratorType type)
{
    bool gotId = false;
    DirectDeclaratorNode *directDeclarator = nullptr;
    if (scanner->Current()->type == TokenType::LBRACKET)
    {
        scanner->Next();
        directDeclarator = (DirectDeclaratorNode *)(parseDeclarator(type));
        gotId = true;
        require(TokenType::RBRACKET);
        scanner->Next();
    }

    if (type == DeclaratorType::NORMAL && !gotId) require(TokenType::ID);
    if (type != DeclaratorType::ABSTRACT && scanner->Current()->type == TokenType::ID)
    {
        directDeclarator = (DirectDeclaratorNode *)new IdNode(scanner->Current());
        scanner->Next();
    }
    while (scanner->Current()->type == TokenType::LSQUARE_BRACKET || scanner->Current()->type == TokenType::LBRACKET)
    {
        if (scanner->Current()->type == TokenType::LSQUARE_BRACKET)
            directDeclarator = parseArrayDeclarator(directDeclarator);
        else
            directDeclarator = parseFunctionDeclarator(directDeclarator);
    }
    return directDeclarator;
}

ArrayDeclaratorNode *Parser::parseArrayDeclarator(DirectDeclaratorNode *directDeclarator)
{
    require(TokenType::LSQUARE_BRACKET);
    scanner->Next();
    if (scanner->Current()->type == TokenType::RSQUARE_BRACKET)
    {
        scanner->Next();
        return new ArrayDeclaratorNode(directDeclarator, nullptr);
    }
    auto ce = parseConstantExpr();
    require(TokenType::RSQUARE_BRACKET);
    scanner->Next();
    return new ArrayDeclaratorNode(directDeclarator, (ConditionalExprNode *)(ce));
}

ArgumentExprListNode *Parser::parseArgumentExprList()
{
    auto ael = new ArgumentExprListNode();
    while (scanner->Current()->type != TokenType::RBRACKET)
    {
        ael->Add((AssignmentExprNode *)parseAssignmentExpr());
        if (scanner->Current()->type != TokenType::RBRACKET)
        {
            require(TokenType::COMMA);
            scanner->Next();
        }
    }
    return ael;
}

bool Parser::isStorageClassSpecifier(std::shared_ptr<Token> token)
{
    return token->type == TokenType::KEYWORD ?
           StorageClassSpecifiers.find(token->keyword) != StorageClassSpecifiers.end() : false;
}

bool Parser::isFunctionSpecifier(std::shared_ptr<Token> token)
{
    return token->type == TokenType::KEYWORD && token->keyword == Keyword::INLINE;
}

ParameterDeclarationNode *Parser::parseParameterDeclaration()
{
    return new ParameterDeclarationNode(parseDeclarationSpecifiers(), parseDeclarator(DeclaratorType::ABSTRACT_OR_NORMAL));
}

DeclarationSpecifiersNode *Parser::parseDeclarationSpecifiers()
{
    auto ds = new DeclarationSpecifiersNode();
    while(isDeclarationSpecifier(scanner->Current()))
    {
        if (scanner->Current()->keyword == Keyword::STRUCT)
            ds->Add((DeclarationSpecifierNode *)parseStructSpecifier());
        else if (scanner->Current()->keyword == Keyword::ENUM)
            ds->Add((DeclarationSpecifierNode *)parseEnumSpecifier());
        else
        {
            ds->Add(new SimpleSpecifier(scanner->Current()));
            scanner->Next();
        }
    }
    if (!ds->Size()) throw NoDeclarationSpecifiers(scanner->Current());
    return ds;
}

ParameterList *Parser::parseParameterList()
{
    auto pl = new ParameterList();
    while (scanner->Current()->type != TokenType::RBRACKET)
    {
        pl->Add(parseParameterDeclaration());
        if (scanner->Current()->type != TokenType::RBRACKET)
        {
            require(TokenType::COMMA);
            scanner->Next();
        }
    }
    return pl;
}

ParameterTypeList *Parser::parseParameterTypeList()
{
    return parseParameterList();
}

bool Parser::isDeclarationSpecifier(std::shared_ptr<Token> token)
{
    return isTypeSpecifier(token) || isStorageClassSpecifier(token) || isTypeQualifier(token)
           || isFunctionSpecifier(token);
}

FunctionDeclaratorNode *Parser::parseFunctionDeclarator(DirectDeclaratorNode *directDeclarator)
{
    scanner->Next();
    auto ptl = parseParameterTypeList();
    require(TokenType::RBRACKET);
    scanner->Next();
    return new FunctionDeclaratorNode(directDeclarator, ptl);
}

DeclarationNode * Parser::parseDeclaration(DeclarationSpecifiersNode *declarationSpecifiers,
                                           InitDeclaratorNode *declarator)
{

    auto ds = declarationSpecifiers ? declarationSpecifiers : parseDeclarationSpecifiers();
    if (scanner->Current()->type == TokenType::SEMICOLON && !declarator)
    {
        scanner->Next();
        return new DeclarationNode(ds, nullptr);
    }
    auto idl = parseInitDeclaratorList(declarator);
    require(TokenType::SEMICOLON);
    scanner->Next();
    return new DeclarationNode(ds, idl);
}

InitDeclaratorListNode *Parser::parseInitDeclaratorList(InitDeclaratorNode *declarator)
{
    auto idl = new InitDeclaratorListNode();
    if (declarator)
    {
        idl->Add(declarator);
        if (scanner->Current()->type != TokenType::COMMA) return idl;
        scanner->Next();
    }
    do
    {
        idl->Add(parseInitDeclarator());
    } while (scanner->Current()->type == TokenType::COMMA && scanner->Next());
    return idl;
}

InitDeclaratorNode *Parser::parseInitDeclarator()
{
    auto dcltr = parseDeclarator(DeclaratorType::NORMAL);
    InitializerNode *initializer = nullptr;
    if (scanner->Current()->type == TokenType::ASSIGNMENT)
    {
        scanner->Next();
        initializer = parseInitializer();
    }
    return new InitDeclaratorNode(dcltr, initializer);
}

InitializerNode *Parser::parseInitializer()
{
    if (scanner->Current()->type == TokenType::LCURLY_BRACKET)
    {
        auto il =  (InitializerNode *)parseInitializerList();
        require(TokenType::RCURLY_BRACKET);
        scanner->Next();
        return il;
    }
    return (InitializerNode *)parseAssignmentExpr();
}

LabelStatementNode *Parser::parseLabelStatement()
{
    require(TokenType::ID);
    auto id = new IdNode(scanner->Current());
    scanner->Next();
    require(TokenType::COLON);
    scanner->Next();
    return new LabelStatementNode(id, parseStatement());
}

CompoundStatement *Parser::parseCompoundStatement()
{
    require(TokenType::LCURLY_BRACKET);
    if (scanner->Next()->type == TokenType::RCURLY_BRACKET && scanner->Next()) return new CompoundStatement(nullptr);
    auto blockItemList = parseBlockItemList();
    require(TokenType::RCURLY_BRACKET);
    scanner->Next();
    return new CompoundStatement(blockItemList);
}

BlockItemListNode *Parser::parseBlockItemList()
{
    auto blockItemList = new BlockItemListNode();
    while (scanner->Current()->type != TokenType::RCURLY_BRACKET)
    {
        blockItemList->Add(parseBlockItem());
    }
    return blockItemList;
}

BlockItemNode *Parser::parseBlockItem()
{
    return (isDeclarationSpecifier(scanner->Current()) ? (BlockItemNode *)parseDeclaration() : (BlockItemNode *)parseStatement());
}

EnumSpecifierNode *Parser::parseEnumSpecifier()
{
    IdNode *id = nullptr;
    EnumeratorList *list = nullptr;
    requierKeyword(Keyword::ENUM);
    if (scanner->Next()->type == TokenType::ID)
    {
        id = new IdNode(scanner->Current());
        scanner->Next();
    }
    if (!id) require(TokenType::LCURLY_BRACKET);
    if (scanner->Current()->type == TokenType::LCURLY_BRACKET && scanner->Next())
    {
        list = parseEnumeratorList();
        if (!list->Size()) EmptyEnumeratorListError(scanner->Current());
        require(TokenType::RCURLY_BRACKET);
        scanner->Next();
    }
    return new EnumSpecifierNode(id, list);
}

EnumeratorList *Parser::parseEnumeratorList()
{
    auto list = new EnumeratorList();
    do
    {
        if (scanner->Current()->type == TokenType::RCURLY_BRACKET) break;
        list->Add(parseEnumerator());
    } while(scanner->Current()->type == TokenType::COMMA && scanner->Next());
    return list;
}

EnumeratorNode *Parser::parseEnumerator()
{
    require(TokenType::ID);
    auto id = new IdNode(scanner->Current());
    scanner->Next();
    if (scanner->Current()->type == TokenType::ASSIGNMENT && scanner->Next())
        return new EnumeratorNode(id, (ConstantExprNode *)parseConstantExpr());
    return new EnumeratorNode(id, nullptr);
}

bool Parser::isSimpleSpecifier(std::shared_ptr<Token> token)
{
    return isTypeQualifier(token) || isTypeSpecifier(token) ||
            isStorageClassSpecifier(token) || isFunctionSpecifier(token);
}

StructSpecifierNode *Parser::parseStructSpecifier()
{
    requierKeyword(Keyword::STRUCT);
    scanner->Next();
    IdNode *id = scanner->Current()->type == TokenType::ID ? new IdNode(scanner->Current()) : nullptr;
    if (!id)
    {
        require(TokenType::LCURLY_BRACKET);
        scanner->Next();
        return new StructSpecifierNode(id, parseStructDeclarationList());
    }
    scanner->Next();
    if (scanner->Current()->type == TokenType::LCURLY_BRACKET && scanner->Next())
        return new StructSpecifierNode(id, parseStructDeclarationList());
    return new StructSpecifierNode(id, nullptr);
}

StructDeclarationListNode *Parser::parseStructDeclarationList()
{
    auto sdl = new StructDeclarationListNode();
    do
    {
        sdl->Add(parseStructDeclaration());
    } while (scanner->Current()->type != TokenType::RCURLY_BRACKET);
    scanner->Next();
    return sdl;
}

StructDeclarationNode *Parser::parseStructDeclaration()
{
    auto structDecl = new StructDeclarationNode(parseSpecifierQualifierList(), parseStructDeclaratorList());
    require(TokenType::SEMICOLON);
    scanner->Next();
    return structDecl;
}

StructDeclaratorNode *Parser::parseStructDeclarator()
{
    if (scanner->Current()->type == TokenType::COLON && scanner->Next())
        return new StructDeclaratorNode(nullptr, (ConstantExprNode *)parseConstantExpr());
    auto declarator = parseDeclarator(DeclaratorType::NORMAL);
    if (scanner->Current()->type == TokenType::COLON && scanner->Next())
        return new StructDeclaratorNode(declarator, (ConstantExprNode *)parseConstantExpr());
    return new StructDeclaratorNode(declarator, nullptr);
}


StructDeclaratorListNode *Parser::parseStructDeclaratorList()
{
    auto sdl = new StructDeclaratorListNode();
    do
    {
        sdl->Add(parseStructDeclarator());
    } while (scanner->Current()->type == TokenType::COMMA && scanner->Next());
    return sdl;
}

SpecifierQualifierListNode *Parser::parseSpecifierQualifierList()
{
    auto tnn = new SpecifierQualifierListNode();
    auto t = scanner->Current();
    bool spec;
    while ((spec = isTypeSpecifier(t)) || isTypeQualifier(t))
    {

        tnn->Add(spec ? (TypeSpecifierQualifierNode *)new TypeSpecifierNode(t) :
                 (TypeSpecifierQualifierNode *)new TypeQualifierNode(t)) ;
        t = scanner->Next();
    }
    return tnn;
}

InitializerListNode *Parser::parseInitializerList()
{
    require(TokenType::LCURLY_BRACKET);
    scanner->Next();
    auto il = new InitializerListNode();
    do
    {
        if (scanner->Current()->type == TokenType::RCURLY_BRACKET) break;
        il->Add(parseDesignatedInitializer());
    } while (scanner->Current()->type == TokenType::COMMA && scanner->Next());
    return il;
}

DesignationNode *Parser::parseDesignation()
{
    auto designatorList = parseDesignatorList();
    require(TokenType::ASSIGNMENT);
    scanner->Next();
    return new DesignationNode(designatorList);
}

DesignatorListNode *Parser::parseDesignatorList()
{
    auto dl = new DesignatorListNode();
    do
    {
        dl->Add(parseDesignator());
    } while(scanner->Current()->type == TokenType::LSQUARE_BRACKET || scanner->Current()->type == TokenType::DOT);
    return dl;
}

DesignatorNode *Parser::parseDesignator()
{
    if (scanner->Current()->type == TokenType::LSQUARE_BRACKET)
    {
        scanner->Next();
        auto constExpr = parseConstantExpr();
        require(TokenType::RSQUARE_BRACKET);
        scanner->Next();
        return new ArrayDesignator((ConstantExprNode *)constExpr);
    }
    require(TokenType::DOT);
    scanner->Next();
    require(TokenType::ID);
    auto smd = new StructMemberDesignator(new IdNode(scanner->Current()));
    scanner->Next();
    return smd;
}

DesignatedInitializerNode *Parser::parseDesignatedInitializer()
{
    if (scanner->Current()->type == TokenType::DOT || scanner->Current()->type == TokenType::LSQUARE_BRACKET)
        return new DesignatedInitializerNode(parseDesignation(), parseInitializer());
    return new DesignatedInitializerNode(nullptr, parseInitializer());
}

TranslationUnitNode *Parser::parseTranslationUnit()
{
    auto tu = new TranslationUnitNode();
    while (scanner->Current()->type != TokenType::END_OF_FILE)
        tu->Add(parseExternalDeclaration());
    return tu;
}

ExternalDeclarationNode *Parser::parseExternalDeclaration()
{
    auto ds = parseDeclarationSpecifiers();
    if (scanner->Current()->type == TokenType::SEMICOLON)
    {
        scanner->Next();
        return (ExternalDeclarationNode *)new DeclarationNode(ds, nullptr);
    }
    auto declarator = parseDeclarator(DeclaratorType::NORMAL);
    if (scanner->Current()->type == TokenType::LCURLY_BRACKET)
        return (ExternalDeclarationNode *)new FunctionDefinitionNode(ds, declarator, parseCompoundStatement());
    if (scanner->Current()->type == TokenType::ASSIGNMENT)
    {
        scanner->Next();
        return (ExternalDeclarationNode *)parseDeclaration(ds, new InitDeclaratorNode(declarator, parseInitializer()));
    }
    return (ExternalDeclarationNode *)parseDeclaration(ds, new InitDeclaratorNode(declarator, nullptr));
}

void Parser::require(TokenType typeExpectation)
{
    if (scanner->Current()->type != typeExpectation) throw UnexpectedTokenError(scanner->Current(), typeExpectation);
}

void Parser::requierKeyword(Keyword expectedKeyword)
{
    if (scanner->Current()->type != TokenType::KEYWORD || scanner->Current()->keyword != expectedKeyword)
        throw UnexpectedKeywordError(scanner->Current(), expectedKeyword);
}
