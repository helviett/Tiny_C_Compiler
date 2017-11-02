//
// Created by keltar on 10/14/17.
//

#ifndef TINY_C_COMPILER_PARSER_H
#define TINY_C_COMPILER_PARSER_H

#include "tokenizer.h"
#include "syntax_tree.h"
#include <functional>

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

enum class DeclaratorType
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
    PostfixExprNode            *parsePrimaryExpr();
    PostfixExprNode            *parsePostfixExpr();
    PostfixExprNode            *parseUnaryExpr();
    PostfixExprNode            *parseCastExpr();
    PostfixExprNode            *parseMultiplicativeExpr();
    PostfixExprNode            *parseAddictiveExpr();
    PostfixExprNode            *parseShiftExpr();
    PostfixExprNode            *parseRelationalExpr();
    PostfixExprNode            *parseEqualityExpr();
    PostfixExprNode            *parseAndExpr();
    PostfixExprNode            *parseExclusiveOrExpr();
    PostfixExprNode            *parseInclusiveOrExpr();
    PostfixExprNode            *parseLogicalAndExpr();
    PostfixExprNode            *parseLogicalOrExpr();
    PostfixExprNode            *parseConditionalExpr();
    PostfixExprNode            *parseAssignmentExpr();
    PostfixExprNode            *parseExpr();
    PostfixExprNode            *parseConstantExpr();
    TypeNameNode               *parseTypeName();
    TypeQualifierListNode      *parseTypeQualifierList();
    PointerNode                *parsePointer();
    StatementNode              *parseStatement();
    ExprStatmentNode           *parseExprStatement();
    SelectionStatementNode     *parseSelectionStatement();
    JumpStatementNode          *parseJumpStatement();
    IterationStatementNode     *parseIterationStatement();
    ForStatementNode           *parseForStatement();
    WhileStatementNode         *parseWhileStatement();
    DoWhileStatementNode       *parseDoWhileStatement();
    DeclaratorNode             *parseDeclarator(DeclaratorType type);
    DirectDeclaratorNode       *parseDirectDeclarator(DeclaratorType type);
    ArrayDeclaratorNode        *parseArrayDeclarator(DirectDeclaratorNode *directDeclarator);
    ArgumentExprListNode       *parseArgumentExprList();
    ParameterDeclarationNode   *parseParameterDeclaration();
    DeclarationSpecifiersNode  *parseDeclarationSpecifiers();
    ParameterList              *parseParameterList();
    ParameterTypeList          *parseParameterTypeList();
    DeclarationNode            *parseDeclaration(DeclarationSpecifiersNode *declarationSpecifiers = nullptr,
                                                 InitDeclaratorNode *declarator = nullptr);
    InitDeclaratorListNode     *parseInitDeclaratorList(InitDeclaratorNode *declarator = nullptr);
    InitDeclaratorNode         *parseInitDeclarator();
    InitializerNode            *parseInitializer();
    FunctionDeclaratorNode     *parseFunctionDeclarator(DirectDeclaratorNode *directDeclarator);
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
    StructDeclaratorNode       *parseStructDeclarator();
    StructDeclaratorListNode   *parseStructDeclaratorList();
    SpecifierQualifierListNode *parseSpecifierQualifierList();
    InitializerListNode        *parseInitializerList();
    DesignationNode            *parseDesignation();
    DesignatorListNode         *parseDesignatorList();
    DesignatorNode             *parseDesignator();
    DesignatedInitializerNode  *parseDesignatedInitializer();
    TranslationUnitNode        *parseTranslationUnit();
    ExternalDeclarationNode    *parseExternalDeclaration();
    PostfixExprNode *parseGeneral(Parser *self, PostfixExprNode *(Parser::*f)(),
                                  std::unordered_set<TokenType> types);
    bool isTypeSpecifier(Token *token);
    bool isUnaryOp(Token *token);
    bool isAssignmentOp(Token *token);
    bool isTypeQualifier(Token *token);
    bool isStorageClassSpecifier(Token *token);
    bool isFunctionSpecifier(Token *token);
    bool isDeclarationSpecifier(Token *token);
    bool isSimpleSpecifier(Token *token);
    Tokenizer *scanner;
    SyntaxTree tree;
};

#endif //TINY_C_COMPILER_PARSER_H
