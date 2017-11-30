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

std::ostream &operator<<(std::ostream &os, Parser &parser)
{
    os << parser.tree;
    return os;
}

// primary-expr ::= id | constant | string-literal | (expr)

ExprNode *Parser::parsePrimaryExpr()
{
    auto t = scanner->Current();
    scanner->Next();
    switch (t->type)
    {
        case TokenType::NUM_INT:
            return new IntConstNode(t);
        case TokenType::NUM_FLOAT:
            return new FloatConstNode(t);
        case TokenType::ID:
            return sematicAnalyzer.BuildIdNode(t);
        case TokenType::STRING:
            return new StringLiteralNode(t);
        case TokenType::LBRACKET:
            ExprNode *e = parseExpr();
            requireNext(TokenType::RBRACKET);
            return e;
    }
    throw InvalidExpression(scanner->Current());
}

//postfix-expr ::= primary-expr | postifx-expr [expr] | postfix-expr (`argument-expr-list)
//| postfix-expr . id | postfix-expr -> id | postfix-expr ++ | postfix-expr --
//| (type-id) {initializer-list} | (type-id) {initializer-list, }

ExprNode *Parser::parsePostfixExpr()
{
    auto t = scanner->Current();
    ExprNode *pe = parsePrimaryExpr();
    t = scanner->Current();
    bool stillPostfixOperator = true;
    while (stillPostfixOperator)
        switch (t->type)
        {
            case TokenType::DOUBLE_PLUS:
                t = scanner->Next();
                pe = sematicAnalyzer.BuildPostfixIncrementNode(pe);
                break;
            case TokenType::DOUBLE_MINUS:
                t = scanner->Next();
                pe = sematicAnalyzer.BuildPostfixDecrementNode(pe);
                break;
            case TokenType::DOT:
                t = scanner->Next();
                require(TokenType::ID);
                pe = sematicAnalyzer.BuildStructureOrUnionMemberAccessNode(pe, new IdNode(t));
                t = scanner->Next();
                break;
            case TokenType::ARROW:
                t = scanner->Next();
                require(TokenType::ID);
                pe = sematicAnalyzer.BuildStructureOrUnionMemberAccessByPointerNode(pe, new IdNode(t));
                t = scanner->Next();
                break;
            case TokenType::LSQUARE_BRACKET:
                t = scanner->Next();
                pe = sematicAnalyzer.BuildArrayAccessNode(pe, parseExpr());
                require(TokenType::RSQUARE_BRACKET);
                t = scanner->Next();
                break;
            case TokenType::LBRACKET:
                t = scanner->Next();
                pe = sematicAnalyzer.BuildFunctionCallNode(pe, parseArgumentExprList());
                require(TokenType::RBRACKET);
                t = scanner->Next();
                break;
            default:
                stillPostfixOperator = false;
        }
    return pe;
}

//unary-expr ::= postfix-expr | ++ unary-expr | -- unary-expr | unary-op cast-expr
//| sizeof unary-expr | sizeof (type-id)

ExprNode *Parser::parseUnaryExpr()
{
    ExprNode *ue;
    auto t = scanner->Current();
    switch (t->type)
    {
        case TokenType::DOUBLE_PLUS:
            t = scanner->Next();
            ue = sematicAnalyzer.BuildPrefixIncrementNode(parseUnaryExpr());
            break;
        case TokenType::DOUBLE_MINUS:
            t = scanner->Next();
            ue = sematicAnalyzer.BuildPrefixDecrementNode(parseUnaryExpr());
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
                ue = sematicAnalyzer.BuildUnaryOpNode(t, parseCastExpr());
                t = scanner->Current();
                break;
            }
            ue = parsePostfixExpr();
    }
    return ue;
}

//cast-expr ::= unary-expr | (type-id) cast-expr

ExprNode *Parser::parseCastExpr()
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

//multiplicative-expr ::= cast-expr | multiplicative-expr * cast-expr
//                        | multiplicative-expr / cast-expr
//                        | multiplicative-expr % cast-expr

ExprNode *Parser::parseMultiplicativeExpr()
{
    static std::unordered_set<TokenType> types = {TokenType::ASTERIX, TokenType::FORWARD_SLASH, TokenType::REMINDER};
    return parseBinoOps(this, &Parser::parseCastExpr, types);
}

//addictive-expr ::= multiplicative-expr
//                   | addictive-expr + multiplicative-expr
//                   | addictive-expr - multiplicative-expr

ExprNode *Parser::parseAddictiveExpr()
{
    static std::unordered_set<TokenType> types = {TokenType::PLUS, TokenType::MINUS};
    return parseBinoOps(this, &Parser::parseMultiplicativeExpr, types);
}

//shift-expr ::= addictive-expr
//               | shift-expr << addictive-expr
//               | shift-expr >> addictive-expr

ExprNode *Parser::parseShiftExpr()
{
    static std::unordered_set<TokenType> types = {TokenType::BITWISE_LSHIFT, TokenType::BITWISE_RSHIFT};
    return parseBinoOps(this, &Parser::parseAddictiveExpr, types);
}

//rel-expr ::= shift-expr | rel-expr < shift-expr | rel-expr > shift-expr
//             | rel-expr <= shift expr | rel-expr >= shift-expr

ExprNode *Parser::parseRelationalExpr()
{
    static std::unordered_set<TokenType> types = {TokenType::RELOP_GT, TokenType::RELOP_LT,
                                                  TokenType::RELOP_GE, TokenType::RELOP_LE};
    return parseBinoOps(this, &Parser::parseShiftExpr, types);
}

//eq-expr ::= rel-expr | eq-expr == rel-expr | eq-expr != rel-expr

ExprNode *Parser::parseEqualityExpr()
{
    static std::unordered_set<TokenType> types = {TokenType::RELOP_EQ, TokenType::RELOP_NE};
    return parseBinoOps(this, &Parser::parseRelationalExpr, types);
}

//AND-expr ::= eq-expr | AND-expr & eq-expr

ExprNode *Parser::parseAndExpr()
{
    static std::unordered_set<TokenType> types = {TokenType::BITWISE_AND};
    return parseBinoOps(this, &Parser::parseEqualityExpr, types);
}

//exclusive-OR-expr ::= AND-expr | exclusive-OR-expr ^ AND-expr

ExprNode *Parser::parseExclusiveOrExpr()
{
    static std::unordered_set<TokenType> types = {TokenType::BITWISE_XOR};
    return parseBinoOps(this, &Parser::parseAndExpr, types);
}

//inclusive-OR-expr ::= exclusive-OR-expr | inclusive-OR-expr '|' exclusive-OR-expr

ExprNode *Parser::parseInclusiveOrExpr()
{
    static std::unordered_set<TokenType> types = {TokenType::BITWISE_OR};
    return parseBinoOps(this, &Parser::parseExclusiveOrExpr, types);
}

//logical-AND-expr ::= inclusive-OR-expr | logical-AND-expr && inclusive-OR-expr

ExprNode *Parser::parseLogicalAndExpr()
{
    static std::unordered_set<TokenType> types = {TokenType::LOGIC_AND};
    return parseBinoOps(this, &Parser::parseInclusiveOrExpr, types);
}

//logical-OR-expr ::= logical-AND-expr | logical-OR-expr || logical-AND-expr

ExprNode *Parser::parseLogicalOrExpr()
{
    static std::unordered_set<TokenType> types = {TokenType::LOGIC_OR};
    return parseBinoOps(this, &Parser::parseLogicalAndExpr, types);
}

ExprNode *Parser::parseBinoOps(Parser *self, ExprNode *(Parser::*f)(),
                               std::unordered_set<TokenType> types)
{
    auto *e = (ExprNode *)(self->*f)();
    auto t = self->scanner->Current();
    while (types.find(t->type) != types.end())
    {
        self->scanner->Next();
        auto right = (ExprNode *) ((*self).*f)();
        e = sematicAnalyzer.BuildBinOpNode(e, right, t);
        t = self->scanner->Current();
    }
    return e;
}

//conditional-expr ::= logical-OR-expr | logical-OR-expr ? expr : conditional-expr

ExprNode *Parser::parseConditionalExpr()
{
    ExprNode *loe =  parseLogicalOrExpr();
    auto t = scanner->Current();
    if (t->type == TokenType::QUESTION_MARK)
    {
        t = scanner->Next();
        ExprNode *then = parseExpr();
        t = scanner->Current();
        require(TokenType::COLON);
        t = scanner->Next();
        ExprNode *lse = parseConditionalExpr();
        return new TernaryOperatorNode(loe, then, lse);
    }
    return loe;
}

//assignment-expr ::= conditional-expr | unary-expr assignment-op assignment-expr

ExprNode *Parser::parseAssignmentExpr()
{
    ExprNode *ce = parseConditionalExpr();
    auto t = scanner->Current();
    if (isAssignmentOp(t))
    {
        scanner->Next();
        return new AssignmentNode(ce, parseAssignmentExpr(), t);

    }
    return ce;
}

//expr ::= assignment-expr | expr , assignment-expr

ExprNode *Parser::parseExpr()
{
    ExprNode *ae = parseAssignmentExpr();
    while (scanner->Current()->type == TokenType::COMMA)
    {
        scanner->Next();
        ae = new CommaSeparatedExprs(ae, parseExpr());
    }
    return ae;
}

//type-id ::= specifier-qualifier-list `abstract-declarator

TypeNameNode *Parser::parseTypeName()
{
    auto tnn = parseSpecifierQualifierList();
    if (tnn->Size() == 0) throw NoDeclarationSpecifiers(scanner->Current());
    auto abstractDeclarator = new DeclaratorNode();
    abstractDeclarator->SetType(TypeBuilder::Build(tnn));
    parseDeclarator(DeclaratorKind::ABSTRACT, abstractDeclarator);
    return new TypeNameNode(abstractDeclarator->GetType());
}

//type-specifier ::= void | char | short | int | long | float | double | singed
//                   | unsigned | struct-specifier | enum-specifier |
//                   | typedef-id

bool Parser::isTypeSpecifier(std::shared_ptr<Token> token)
{
    return token->type == TokenType::KEYWORD ? TypeSpecifiers.find(token->keyword) != TypeSpecifiers.end() : false;
}

//unary-op  ::= & | * | + | - | ~ | !

bool Parser::isUnaryOp(std::shared_ptr<Token> token)
{
    return UnaryOps.find(token->type) != UnaryOps.end();
}

//assignment-op ::= = | *= | /= | %= | += | -= | <<= | >>= | &= | ^= | |=

bool Parser::isAssignmentOp(std::shared_ptr<Token> token)
{
    return  AssignmentOps.find(token->type) != AssignmentOps.end();
}

//type-qualifier ::= const

bool Parser::isTypeQualifier(std::shared_ptr<Token> token)
{
    return token->type == TokenType::KEYWORD ? TypeQualifiers.find(token->keyword) != TypeQualifiers.end() : false;
}

//constant-expr ::= conditional-expr

ExprNode *Parser::parseConstantExpr()
{
    return parseConditionalExpr();
}

//type-qualifier-list ::= type-qualifier | type-qualifier-list type-qualifier

DeclarationSpecifiersNode *Parser::parseTypeQualifierList()
{
    auto tql = new DeclarationSpecifiersNode();
    auto t = scanner->Current();
    while (isTypeQualifier(t))
    {

        tql->Add(new TypeQualifierNode(t));
        t = scanner->Next();
    }
    return tql;
}

//statement ::= labeled-statement | compound-statement
//              | expression-statement | selection-statement
//              | iteration-statement | jump-statement

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

//expression-statement ::= `expr ;

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

//selection-statement ::= if (expr) statement
//| if (expr) statement else statement

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

//jump-statement ::= goto id ;
//| continue ;
//| break ;
//| return `expr ;

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

//iteration-statement ::= while (expr) statement
//| do statement while (expr) ;
//| for (`expr ; `expr ; `expr) statement

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

//for (`expr ; `expr ; `expr) statement

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

//while (expr) statement

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

//do statement while (expr) ;

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

void Parser::parsePointer(DeclaratorNode *declarator)
{
    if (scanner->Current()->type != TokenType::ASTERIX) return;
    scanner->Next();
    auto tql = parseTypeQualifierList(); // TODO that's what SymPointer gonna store
    declarator->SetType(new SymPointer(declarator->GetType()));
    parsePointer(declarator);
}

//declarator ::= `pointer direct-declarator

void Parser::parseDeclarator(DeclaratorKind kind, DeclaratorNode *declarator)
{
    parsePointer(declarator);
    parseDirectDeclarator(kind, declarator);
}

//direct-declarator ::= id | (declarator)
//                      | direct-declarator [constant-expr]
//                      | direct-declarator (`parameter-type-list)

void Parser::parseDirectDeclarator(DeclaratorKind kind, DeclaratorNode *declarator)
{
    bool gotId = false;
    SymType *lastType = nullptr;
    DeclaratorNode *newDecl = nullptr;
    if (scanner->Current()->type == TokenType::LBRACKET)
    {
        scanner->Next();
        newDecl = new DeclaratorNode();
        parseDeclarator(kind, newDecl);
        auto type = newDecl->GetType();

        while (type)
        {
            switch (type->GetTypeKind())
            {
                case TypeKind::POINTER:
                    lastType = type;
                    type = ((SymPointer *)type)->GetTarget();
                    break;
                case TypeKind::ARRAY:
                    lastType = type;
                    type = ((SymArray *)type)->GetValueType();
                    break;
                case TypeKind::FUNCTION:
                    lastType = type;
                    type = ((SymFunction *)type)->GetReturnType();
                    break;
            }
        }
        gotId = true;
        if (newDecl) declarator->SetId(newDecl->GetId());
        require(TokenType::RBRACKET);
        scanner->Next();
    }

    if (kind == DeclaratorKind::NORMAL && !gotId) require(TokenType::ID);
    if (kind != DeclaratorKind::ABSTRACT && scanner->Current()->type == TokenType::ID)
    {
        declarator->SetId(new IdNode(scanner->Current()));
        scanner->Next();
    }
    while (scanner->Current()->type == TokenType::LSQUARE_BRACKET || scanner->Current()->type == TokenType::LBRACKET)
    {
        if (scanner->Current()->type == TokenType::LSQUARE_BRACKET)
            parseArrayDeclarator(declarator);
        else
            parseFunctionDeclarator(declarator);
    }
    if (lastType)
    {
        switch (lastType->GetTypeKind())
        {
            case TypeKind::POINTER:
                ((SymPointer *)lastType)->SetTarget(declarator->GetType());
                break;
            case TypeKind::ARRAY:
                ((SymArray *)lastType)->SetValueType(declarator->GetType());
                break;
            case TypeKind::FUNCTION:
                ((SymFunction *)lastType)->SetReturnType(declarator->GetType());
                break;
        }
        declarator->SetType(newDecl->GetType());
    }

}


void Parser::parseFunctionDeclarator(DeclaratorNode *declarator)
{
    scanner->Next();
    auto ptl = parseParameterTypeList();
    std::vector<SymVariable *> orderedParamTypes;
    orderedParamTypes.reserve(ptl->List().size());
    auto table = new SymbolTable();
    for (auto it: ptl->List())
    {
        std::string name = it->GetId() ? it->GetId()->GetName() : "#" + std::to_string(orderedParamTypes.size());

        auto var = new SymVariable(name, (*it).GetType());
        var->SetName(name);
        orderedParamTypes.push_back(var);
        table->Insert(name, var);
    }
    table->SetParent(sematicAnalyzer.GetScopeTree()->GetActiveScope());
    require(TokenType::RBRACKET);
    declarator->SetType(new SymFunction(declarator->GetType(), table, orderedParamTypes));
    scanner->Next();
}

void Parser::parseArrayDeclarator(DeclaratorNode *declarator)
{
    require(TokenType::LSQUARE_BRACKET);
    scanner->Next();
    if (scanner->Current()->type == TokenType::RSQUARE_BRACKET)
    {
        scanner->Next();
        declarator->SetType(new SymArray(declarator->GetType(), nullptr));
        return;
    }
    auto ce = parseConstantExpr();
    require(TokenType::RSQUARE_BRACKET);
    scanner->Next();
    declarator->SetType(new SymArray(declarator->GetType(), ce));
}

//pointer ::= * `type-qualifier-list | * `type-qualifier-list pointer

PointerNode *Parser::parsePointer()
{
    if (scanner->Current()->type != TokenType::ASTERIX) return nullptr;
    scanner->Next();
    return new PointerNode(parseTypeQualifierList(), parsePointer());
}

//argument-expr-list ::= argument-expr | argument-expr-list, argument-expr

ArgumentExprListNode *Parser::parseArgumentExprList()
{
    auto ael = new ArgumentExprListNode();
    while (scanner->Current()->type != TokenType::RBRACKET)
    {
        ael->Add(parseAssignmentExpr());
        if (scanner->Current()->type != TokenType::RBRACKET)
        {
            require(TokenType::COMMA);
            scanner->Next();
        }
    }
    return ael;
}

//storage-class-specifier ::= typedef | extern | static | auto | register

bool Parser::isStorageClassSpecifier(std::shared_ptr<Token> token)
{
    return token->type == TokenType::KEYWORD ?
           StorageClassSpecifiers.find(token->keyword) != StorageClassSpecifiers.end() : false;
}

//function-specifier ::= inline

bool Parser::isFunctionSpecifier(std::shared_ptr<Token> token)
{
    return token->type == TokenType::KEYWORD && token->keyword == Keyword::INLINE;
}

//parameter-declaration ::= declaration-specifiers declarator | declaration-specifiers `abstract-declarator

ParameterDeclarationNode *Parser::parseParameterDeclaration()
{
    auto declarator = new DeclaratorNode();
    declarator->SetType(TypeBuilder::Build(parseDeclarationSpecifiers()));
    parseDeclarator(DeclaratorKind::ABSTRACT_OR_NORMAL, declarator);
    return new ParameterDeclarationNode(declarator);
}

//declaration-specifiers ::= storage-class-specifier `declaration-specifier |
//| type-specifier `declaration-specifier
//| type-qualifier `declaration-specifier
//| function-specifier declaration-specifier

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

//parameter-list ::= parameter-declaration | parameter-list , parameter-declaration

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

//parameter-type-list ::= parameter-list

ParameterList *Parser::parseParameterTypeList()
{
    return parseParameterList();
}

//declaration-specifiers ::= storage-class-specifier `declaration-specifier |
//| type-specifier `declaration-specifier
//| type-qualifier `declaration-specifier
//| function-specifier declaration-specifier

bool Parser::isDeclarationSpecifier(std::shared_ptr<Token> token)
{
    return isTypeSpecifier(token) || isStorageClassSpecifier(token) || isTypeQualifier(token)
           || isFunctionSpecifier(token);
}

//declaration ::= declaration-specifiers `init-declarator-list ;

DeclarationNode * Parser::parseDeclaration(DeclarationSpecifiersNode *declarationSpecifiers,
                                           InitDeclaratorNode *declarator)
{

    auto ds = declarationSpecifiers ? declarationSpecifiers : parseDeclarationSpecifiers();
    if (scanner->Current()->type == TokenType::SEMICOLON && !declarator)
    {
        scanner->Next();
        return new DeclarationNode(ds, nullptr);
    }
    auto idl = parseInitDeclaratorList(ds, declarator);
    require(TokenType::SEMICOLON);
    scanner->Next();
    return new DeclarationNode(ds, idl);
}

//init-declarator-list ::= init-declarator | init-declarator-list , init-declarator

InitDeclaratorListNode *Parser::parseInitDeclaratorList(DeclarationSpecifiersNode *declarationSpecifiers, InitDeclaratorNode *declarator)
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
        idl->Add(parseInitDeclarator(declarationSpecifiers));
    } while (scanner->Current()->type == TokenType::COMMA && scanner->Next());
    return idl;
}

//init-declarator ::= declarator | declaratxor = initializer

InitDeclaratorNode *Parser::parseInitDeclarator(DeclarationSpecifiersNode *declarationSpecifiers)
{
    // TODO pass built type instead of building every time
    auto declarator = new DeclaratorNode();
    declarator->SetType(TypeBuilder::Build(declarationSpecifiers));
    parseDeclarator(DeclaratorKind::NORMAL, declarator);
    InitializerNode *initializer = nullptr;
    if (scanner->Current()->type == TokenType::ASSIGNMENT)
    {
        scanner->Next();
        initializer = parseInitializer();
    }
    return sematicAnalyzer.BuildInitDeclaratorNode(declarator, initializer);
}

//initializer ::= assignment-expr | {initializer-list} | {initializer-list , }

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

//labeled-statement ::= id : statement

LabelStatementNode *Parser::parseLabelStatement()
{
    require(TokenType::ID);
    auto id = new IdNode(scanner->Current());
    scanner->Next();
    require(TokenType::COLON);
    scanner->Next();
    return new LabelStatementNode(id, parseStatement());
}

//compound-statement ::= {`block-item-list}

CompoundStatement *Parser::parseCompoundStatement()
{

    require(TokenType::LCURLY_BRACKET);
    sematicAnalyzer.GetScopeTree()->StartScope();
    if (scanner->Next()->type == TokenType::RCURLY_BRACKET && scanner->Next()) return new CompoundStatement(nullptr);
    auto blockItemList = parseBlockItemList();
    require(TokenType::RCURLY_BRACKET);
    sematicAnalyzer.GetScopeTree()->EndScope();
    scanner->Next();
    return new CompoundStatement(blockItemList);
}

//block-item-list ::= block-item | block-item-list block-item

BlockItemListNode *Parser::parseBlockItemList()
{
    auto blockItemList = new BlockItemListNode();
    while (scanner->Current()->type != TokenType::RCURLY_BRACKET)
    {
        blockItemList->Add(parseBlockItem());
    }
    return blockItemList;
}

//block-item ::= declaration | statement

BlockItemNode *Parser::parseBlockItem()
{
    return (isDeclarationSpecifier(scanner->Current()) ? (BlockItemNode *)parseDeclaration() : (BlockItemNode *)parseStatement());
}

//enum-specifier ::= enum `id {enumerator-list}
//| enum `id {enumerator-list , }
//| enum id

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

//enumerator-list ::= enumerator | enumerator-list , enumerator

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

//enumerator ::= enumeration-constant, enumeration-constant = constant-expr

EnumeratorNode *Parser::parseEnumerator()
{
    require(TokenType::ID);
    auto id = new IdNode(scanner->Current());
    scanner->Next();
    if (scanner->Current()->type == TokenType::ASSIGNMENT && scanner->Next())
        return new EnumeratorNode(id, (ExprNode *)parseConstantExpr());
    return new EnumeratorNode(id, nullptr);
}

// a specifier that consists of 1 keyword: type-qualifier | type-specifier
// | storage-class-specifier | function-specifier

bool Parser::isSimpleSpecifier(std::shared_ptr<Token> token)
{
    return isTypeQualifier(token) || isTypeSpecifier(token) ||
            isStorageClassSpecifier(token) || isFunctionSpecifier(token);
}

//struct-specifier ::= struct `id {struct-declaration-list}
//| struct id

StructSpecifierNode *Parser::parseStructSpecifier()
{
    requierKeyword(Keyword::STRUCT);
    scanner->Next();
    IdNode *id = maybe(TokenType::ID) ? new IdNode(scanner->Current()) : nullptr;
    if (!id)
    {
        requireNext(TokenType::LCURLY_BRACKET);
        return sematicAnalyzer.BuildStructSpecifierNode(id, parseStructDeclarationList());
    }
    scanner->Next();
    if (maybeNext(TokenType::LCURLY_BRACKET))
        return sematicAnalyzer.BuildStructSpecifierNode(id, parseStructDeclarationList());
    return new StructSpecifierNode(new SymRecord(id));
}

//struct-declaration-list ::= struct-declaration | struct-declaration-list struct-declaration

StructDeclarationListNode *Parser::parseStructDeclarationList()
{
    auto sdl = new StructDeclarationListNode();
    do
    {
        sdl->Add(parseStructDeclaration());
    } while (!maybe(TokenType::RCURLY_BRACKET));
    scanner->Next();
    return sdl;
}

//struct-declaration ::= specifier-qualifier-list struct-declarator-list ;

StructDeclarationNode *Parser::parseStructDeclaration()
{
    auto structDecl = new StructDeclarationNode(
            parseStructDeclaratorList(TypeBuilder::Build(parseSpecifierQualifierList())));
    requireNext(TokenType::SEMICOLON);
    return structDecl;
}

//struct-declarator ::= declarator | `declarator : constant-expr

StructDeclaratorNode *Parser::parseStructDeclarator(SymType *baseType)
{
    if (maybeNext(TokenType::COLON))
        return new StructDeclaratorNode(nullptr, (ExprNode *)parseConstantExpr());
    auto declarator = new DeclaratorNode();
    declarator->SetType(baseType);
    parseDeclarator(DeclaratorKind::NORMAL, declarator);
    if (scanner->Current()->type == TokenType::COLON && scanner->Next())
        return new StructDeclaratorNode(declarator, (ExprNode *)parseConstantExpr());
    return new StructDeclaratorNode(declarator, nullptr);
}

//struct-declarator-list ::= struct-declarator | struct-declarator-list , struct-declarator

StructDeclaratorListNode *Parser::parseStructDeclaratorList(SymType *baseType)
{
    auto sdl = new StructDeclaratorListNode();
    do
    {
        sdl->Add(parseStructDeclarator(baseType));
    } while (maybeNext(TokenType::COMMA));
    return sdl;
}

//specifier-qualifier-list ::= type-specifier `specifier-qualifier-list
//| type-qualifier `specifier-qualifier-list

DeclarationSpecifiersNode *Parser::parseSpecifierQualifierList()
{
    auto tnn = new DeclarationSpecifiersNode();
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

//initializer-list ::= `designation initializer | initializer-list , `designation initializer

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

//designation ::= designator-list =

DesignationNode *Parser::parseDesignation()
{
    auto designatorList = parseDesignatorList();
    require(TokenType::ASSIGNMENT);
    scanner->Next();
    return new DesignationNode(designatorList);
}

//designator-list ::= designator | designator-list designator

DesignatorListNode *Parser::parseDesignatorList()
{
    auto dl = new DesignatorListNode();
    do
    {
        dl->Add(parseDesignator());
    } while(scanner->Current()->type == TokenType::LSQUARE_BRACKET || scanner->Current()->type == TokenType::DOT);
    return dl;
}

//designator ::= [constant-expr] | . id

DesignatorNode *Parser::parseDesignator()
{
    if (scanner->Current()->type == TokenType::LSQUARE_BRACKET)
    {
        scanner->Next();
        auto constExpr = parseConstantExpr();
        require(TokenType::RSQUARE_BRACKET);
        scanner->Next();
        return new ArrayDesignator((ExprNode *)constExpr);
    }
    require(TokenType::DOT);
    scanner->Next();
    require(TokenType::ID);
    auto smd = new StructMemberDesignator(new IdNode(scanner->Current()));
    scanner->Next();
    return smd;
}

// `designation initializer

DesignatedInitializerNode *Parser::parseDesignatedInitializer()
{
    if (scanner->Current()->type == TokenType::DOT || scanner->Current()->type == TokenType::LSQUARE_BRACKET)
        return new DesignatedInitializerNode(parseDesignation(), parseInitializer());
    return new DesignatedInitializerNode(nullptr, parseInitializer());
}

//translation-unit ::= external-declaration | translation-unit external-declaration

TranslationUnitNode *Parser::parseTranslationUnit()
{
    auto tu = new TranslationUnitNode();
    while (scanner->Current()->type != TokenType::END_OF_FILE)
        tu->Add(parseExternalDeclaration());
    return tu;
}

//external-declaration ::= function-definition | declaration

ExternalDeclarationNode *Parser::parseExternalDeclaration()
{
    auto ds = parseDeclarationSpecifiers();
    auto type = TypeBuilder::Build(ds);
    if (scanner->Current()->type == TokenType::SEMICOLON)
    {
        scanner->Next();
        return (ExternalDeclarationNode *)new DeclarationNode(ds, nullptr);
    }
    auto declarator = new DeclaratorNode();
    declarator->SetType(type);
    parseDeclarator(DeclaratorKind::NORMAL, declarator);
    if (scanner->Current()->type == TokenType::LCURLY_BRACKET)
    {
        if (declarator->GetType()->GetTypeKind() != TypeKind::FUNCTION) throw "";
        auto f = (SymFunction *)declarator->GetType();
        auto fdeclaration = (SymFunction *)sematicAnalyzer.GetScopeTree()->Find(declarator->GetId()->GetName());
        if (fdeclaration)
        {
            if (fdeclaration->GetTypeKind() != TypeKind::FUNCTION) throw "";
            if (!(fdeclaration->Equal(f))) throw "";
            // TODO check body existence
        }
        sematicAnalyzer.GetScopeTree()->GetActiveScope()->Insert(declarator->GetId()->GetName(), f);
        sematicAnalyzer.GetScopeTree()->SetActiveScope(f->GetParamsTable());
        auto res = (ExternalDeclarationNode *)new FunctionDefinitionNode(declarator, parseCompoundStatement());
        sematicAnalyzer.GetScopeTree()->EndScope();
        return res;
    }
    if (scanner->Current()->type == TokenType::ASSIGNMENT)
    {
        scanner->Next();
        return (ExternalDeclarationNode *)
                parseDeclaration(ds, sematicAnalyzer.BuildInitDeclaratorNode(declarator, parseInitializer()));
    }
    return (ExternalDeclarationNode *)parseDeclaration(ds, sematicAnalyzer.BuildInitDeclaratorNode(declarator, nullptr));
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

bool Parser::isProperFunctionDeclaration(SymFunction *definition, SymFunction *declaration)
{
    return definition == declaration;
}

void Parser::requireNext(TokenType typeExpectation)
{
    require(typeExpectation);
    scanner->Next();
}

void Parser::requireKeywordNext(Keyword expectedKeyword)
{
    requierKeyword(expectedKeyword);
    scanner->Next();
}

bool Parser::maybe(TokenType typeExpectation)
{
    return scanner->Current()->type == typeExpectation;
}

bool Parser::maybeNext(TokenType typeExpectation)
{
    return maybe(typeExpectation) && scanner->Next();
}
