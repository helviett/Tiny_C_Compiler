//
// Created by keltar on 10/14/17.
//

#ifndef TINY_C_COMPILER_PARSER_H
#define TINY_C_COMPILER_PARSER_H

#include "tokenizer.h"
#include "syntax_tree.h"
#include "symbols.h"
#include "type_builder.h"
#include "scope_tree.h"
#include <functional>
#include <stack>
#include <map>

static std::unordered_set<Keyword> TypeSpecifiers =
{
    Keyword::VOID, Keyword::CHAR, Keyword::SHORT, Keyword::INT, Keyword::LONG,
    Keyword::FLOAT, Keyword::DOUBLE, Keyword::SIGNED, Keyword::UNSIGNED, Keyword::STRUCT, Keyword::ENUM
};

static std::unordered_set<Keyword> TypeQualifiers =
{
    Keyword::VOLATILE, Keyword::CONST
};

static std::unordered_set<Keyword> StorageClassSpecifiers =
{
    Keyword::TYPEDEF, Keyword::EXTERN, Keyword::STATIC, Keyword::REGISTER
};

static std::unordered_set<TokenType> AssignmentOps =
{
    TokenType::ASSIGNMENT, TokenType::ASSIGNMENT_BY_PRODUCT,
    TokenType::ASSIGNMENT_BY_QUOTIENT, TokenType::ASSIGNMENT_BY_REMINDER,
    TokenType::ASSIGNMENT_BY_SUM, TokenType::ASSIGNMENT_BY_DIFFERENCE,
    TokenType::ASSIGNMENT_BY_BITWISE_RSHIFT, TokenType::ASSIGNMENT_BY_BITWISE_AND,
    TokenType::ASSIGNMENT_BY_BITWISE_OR, TokenType::ASSIGNMENT_BY_BITWISE_XOR,
    TokenType::ASSIGNMENT_BY_BITWISE_LSHIFT
};

static std::unordered_set<TokenType> UnaryOps =
{
    TokenType::MINUS, TokenType::PLUS, TokenType::LOGIC_NO,
    TokenType::BITWISE_NOT, TokenType::ASTERIX,
    TokenType::BITWISE_AND
};

enum class DeclaratorKind
{
    ABSTRACT, NORMAL, ABSTRACT_OR_NORMAL
};

class Parser
{
public:
    explicit Parser(Tokenizer *tokenizer);
    Parser();

    void Parse();
    friend std::ostream &operator<<(std::ostream &os, Parser &parser);
private:
    ExprNode            *parsePrimaryExpr();
    ExprNode            *parsePostfixExpr();
    ExprNode            *parseUnaryExpr();
    ExprNode            *parseCastExpr();
    ExprNode            *parseMultiplicativeExpr();
    ExprNode            *parseAddictiveExpr();
    ExprNode            *parseShiftExpr();
    ExprNode            *parseRelationalExpr();
    ExprNode            *parseEqualityExpr();
    ExprNode            *parseAndExpr();
    ExprNode            *parseExclusiveOrExpr();
    ExprNode            *parseInclusiveOrExpr();
    ExprNode            *parseLogicalAndExpr();
    ExprNode            *parseLogicalOrExpr();
    ExprNode            *parseConditionalExpr();
    ExprNode            *parseAssignmentExpr();
    ExprNode            *parseExpr();
    ExprNode            *parseConstantExpr();
    TypeNameNode               *parseTypeName();
    DeclarationSpecifiersNode      *parseTypeQualifierList();
    PointerNode                *parsePointer();
    StatementNode              *parseStatement();
    ExprStatmentNode           *parseExprStatement();
    SelectionStatementNode     *parseSelectionStatement();
    JumpStatementNode          *parseJumpStatement();
    IterationStatementNode     *parseIterationStatement();
    ForStatementNode           *parseForStatement();
    WhileStatementNode         *parseWhileStatement();
    DoWhileStatementNode       *parseDoWhileStatement();
    void                        parseDeclarator(DeclaratorKind kind, DeclaratorNode *declarator);
    void                        parseDirectDeclarator(DeclaratorKind kind, DeclaratorNode *declarator);
    void                        parsePointer(DeclaratorNode *declarator);
    void                        parseFunctionDeclarator(DeclaratorNode *declarator);
    void                        parseArrayDeclarator(DeclaratorNode *declarator);
    ArgumentExprListNode       *parseArgumentExprList();
    ParameterDeclarationNode   *parseParameterDeclaration();
    DeclarationSpecifiersNode  *parseDeclarationSpecifiers();
    ParameterList              *parseParameterList();
    ParameterList               *parseParameterTypeList();
    DeclarationNode            *parseDeclaration(DeclarationSpecifiersNode *declarationSpecifiers = nullptr,
                                                 InitDeclaratorNode *declarator = nullptr);
    InitDeclaratorListNode     *parseInitDeclaratorList(DeclarationSpecifiersNode *declarationSpecifiers,
                                                        InitDeclaratorNode *declarator = nullptr);
    InitDeclaratorNode         *parseInitDeclarator(DeclarationSpecifiersNode *declarationSpecifiers);
    InitializerNode            *parseInitializer();
    LabelStatementNode         *parseLabelStatement();
    CompoundStatement          *parseCompoundStatement();
    BlockItemListNode          *parseBlockItemList();
    BlockItemNode              *parseBlockItem();
    EnumSpecifierNode          *parseEnumSpecifier();
    EnumeratorList             *parseEnumeratorList();
    EnumeratorNode             *parseEnumerator();
    StructSpecifierNode        *parseStructSpecifier();
    StructDeclarationListNode  *parseStructDeclarationList();
    StructDeclarationNode      *parseStructDeclaration();
    StructDeclaratorNode       *parseStructDeclarator(SymType *baseType);
    StructDeclaratorListNode   *parseStructDeclaratorList(SymType *baseType);
    DeclarationSpecifiersNode  *parseSpecifierQualifierList();
    InitializerListNode        *parseInitializerList();
    DesignationNode            *parseDesignation();
    DesignatorListNode         *parseDesignatorList();
    DesignatorNode             *parseDesignator();
    DesignatedInitializerNode  *parseDesignatedInitializer();
    TranslationUnitNode        *parseTranslationUnit();
    ExternalDeclarationNode    *parseExternalDeclaration();
    ExprNode *parseBinoOps(Parser *self, ExprNode *(Parser::*f)(),
                           std::unordered_set<TokenType> types);
    bool isTypeSpecifier(std::shared_ptr<Token> token);
    bool isUnaryOp(std::shared_ptr<Token> token);
    bool isAssignmentOp(std::shared_ptr<Token> token);
    bool isTypeQualifier(std::shared_ptr<Token> token);
    bool isStorageClassSpecifier(std::shared_ptr<Token> token);
    bool isFunctionSpecifier(std::shared_ptr<Token> token);
    bool isDeclarationSpecifier(std::shared_ptr<Token> token);
    bool isSimpleSpecifier(std::shared_ptr<Token> token);
    void require(TokenType typeExpectation);
    void requierKeyword(Keyword expectedKeyword);

    std::vector<std::map<std::string, Symbol *>> tablesOfSymbols;
    Tokenizer *scanner;
    SyntaxTree tree;
    ScopeTree scopeTree;
};

#endif //TINY_C_COMPILER_PARSER_H
