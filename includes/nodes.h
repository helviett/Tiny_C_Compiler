//
// Created by keltar on 10/14/17.
//

#ifndef TINY_C_COMPILER_NODE_H
#define TINY_C_COMPILER_NODE_H

#include "token.h"
#include "specifier_qualifier.h"
#include <iostream>
#include <utility>
#include <vector>

// Abstract Class
class Node
{
public:
    virtual void Print(std::ostream &os, int depth) = 0;
};

class TypeSpecifiers;
class TypeQualifierNode;

class DeclarationSpecifierNode: public Node
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

class SimpleSpecifier: public DeclarationSpecifierNode
{
public:
    explicit SimpleSpecifier(Token *specifier): value(specifier) {}
    void Print(std::ostream &os, int depth) override;
protected:
    Token *value;
};

class TypeSpecifierQualifierNode: public SimpleSpecifier
{
public:
    TypeSpecifierQualifierNode() = default;
    explicit TypeSpecifierQualifierNode(Token *value): SimpleSpecifier(value) {}
    void Print(std::ostream &os, int depth) override;
};

class TypeSpecifierNode: public TypeSpecifierQualifierNode
{
public:
    explicit TypeSpecifierNode(Token *specifier): TypeSpecifierQualifierNode(specifier) {}
    void Print(std::ostream &os, int depth) override;
};

class TypeQualifierNode: public TypeSpecifierQualifierNode
{
public:
    explicit TypeQualifierNode(Token *qualifier): TypeSpecifierQualifierNode(qualifier) {}
    void Print(std::ostream &os, int depth) override;
};

class StorageClassSpecifierNode: public SimpleSpecifier
{
public:
    explicit StorageClassSpecifierNode(Token *specifier): SimpleSpecifier(specifier) {}
    void Print(std::ostream &os, int depth) override;
};

class FunctionSpecifierNode: public SimpleSpecifier
{
public:
    explicit FunctionSpecifierNode(Token *specifier): SimpleSpecifier(specifier) {}
    void Print(std::ostream &os, int depth) override;
};

//
//postfix-expr ::= primary-expr | postfix-expr [expr] | postfix-expr (`argument-expr-list)
//                | postfix-expr . id | postfix-expr -> id | postfix-expr ++ | postfix-expr --
//                | (type-name) {initializer-list} | (type-name) {initializer-list, }

class PostfixExprNode: public Node
{
public:
    virtual void Print(std::ostream &os, int depth) = 0;
};

class PostfixIncrementNode: public PostfixExprNode
{
public:
    explicit PostfixIncrementNode(PostfixExprNode *node): node(node) {}
    virtual void Print(std::ostream &os, int depth);
private:
    PostfixExprNode *node;
};

class PostfixDecrementNode: public PostfixExprNode
{
public:
    explicit PostfixDecrementNode(PostfixExprNode *node): node(node) {}
    virtual void Print(std::ostream &os, int depth);
private:
    PostfixExprNode *node;
};

class IdNode;

class StructureOrUnionMemberAccessNode: public PostfixExprNode
{
public:
    StructureOrUnionMemberAccessNode(PostfixExprNode *structureOrUnion, IdNode *member): member(member),
                                                                                     structureOrUnion(structureOrUnion) {}

    void Print(std::ostream &os, int depth) override;
private:
    PostfixExprNode *structureOrUnion;
    IdNode *member;
};

class StructureOrUnionMemberAccessByPointerNode: public PostfixExprNode
{
public:
    StructureOrUnionMemberAccessByPointerNode(PostfixExprNode *structureOrUnion, IdNode *member): member(member),
                                                                                     structureOrUnion(structureOrUnion) {}

    void Print(std::ostream &os, int depth) override;
private:
    PostfixExprNode *structureOrUnion;
    IdNode *member;
};

class ArrayAccess: public PostfixExprNode
{
public:
    ArrayAccess(PostfixExprNode *left, PostfixExprNode *inBrackets): left(left), inBrackets(inBrackets) {}
    void Print(std::ostream &os, int depth) override;
private:
    PostfixExprNode *left, *inBrackets;
};

class AssignmentExprNode;

class ArgumentExprListNode: public Node
{
public:
    void Print(std::ostream &os, int depth) override;
    void Add(AssignmentExprNode *assignmentExpr);
    uint64_t Size();
private:
    std::list<AssignmentExprNode *> list;
};

class FunctionCallNode: public PostfixExprNode
{
public:
    FunctionCallNode(PostfixExprNode *functionName, ArgumentExprListNode *arguments):
            functionName(functionName), arguments(arguments) {}
    void Print(std::ostream &os, int depth) override;
private:
    PostfixExprNode *functionName;
    ArgumentExprListNode *arguments;
};

//unary-expr ::= postfix-expr | ++ unary-expr | -- unary-expr | unary-op cast-expr
//              | sizeof unary-expr | sizeof (type-name)
class UnaryExprNode: public PostfixExprNode
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

class SizeofExprNode: public  UnaryExprNode
{
public:
    SizeofExprNode(PostfixExprNode *expr): expr(expr) {}
    void Print(std::ostream &os, int depth) override;
private:
    PostfixExprNode *expr;
};

class TypeNameNode;

class SizeofTypeNameNode: public UnaryExprNode
{
public:
    SizeofTypeNameNode(TypeNameNode *typeName): typeName(typeName) {}
    void Print(std::ostream &os, int depth) override;
private:
    TypeNameNode *typeName;
};

class UnaryOpNode: public UnaryExprNode
{
public:
    UnaryOpNode (Token *unaryOp, PostfixExprNode *expr): unaryOp(unaryOp), expr(expr) {}
    void Print(std::ostream &os, int depth) override;
private:
    Token *unaryOp;
    PostfixExprNode *expr;
};

class PrefixIncrementNode: public UnaryExprNode
{
public:
    explicit PrefixIncrementNode(PostfixExprNode *node): node(node){}
    void Print(std::ostream &os, int depth) override;
private:
    PostfixExprNode *node;
};

class PrefixDecrementNode: public UnaryExprNode
{
public:
    explicit PrefixDecrementNode(PostfixExprNode *node): node(node){}
    void Print(std::ostream &os, int depth) override;
private:
    PostfixExprNode *node;
};

// cast-expr ::= unary-expr | (type-name) cast-expr
class CastExprNode: public UnaryExprNode
{
public:
    CastExprNode(){}
    void Print(std::ostream &os, int depth) override = 0;
};

class BinOpNode: public CastExprNode
{
public:
    BinOpNode(PostfixExprNode *left, PostfixExprNode *right, Token *op): left(left), right(right), op(op) {}
    void Print(std::ostream &os, int depth) override;
private:
    PostfixExprNode *left, *right;
    Token *op;
};

//multiplicative-expr ::= cast-expr | multiplicative-expr * cast-expr
//                       | multiplicative-expr / cast-expr
//                       | multiplicative-expr % cast-expr

class MultiplicativeExprNode: public CastExprNode
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

//addictive-expr ::= multiplicative-expr
//                   | addictive-expr + multiplicative-expr
//                   | addictive-expr - multiplicative-expr

class AddictiveExprNode: public CastExprNode
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

//shift-expr ::= addictive-expr
//               | shift-expr << addictive-expr
//               | shift-expr >> addictive-expr

class ShiftExprNode: public AddictiveExprNode
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

//rel-expr ::= shift-expr | rel-expr < shift-expr | rel-expr > shift-expr
//             | rel-expr <= shift expr | rel-expr >= shift-expr

class RelationalExprNode: public ShiftExprNode
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

//eq-expr ::= rel-expr | eq-expr == rel-expr | eq-expr != rel-expr

class EqualityExprNode: public RelationalExprNode
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

//AND-expr ::= eq-expr | AND-expr & eq-expr

class AndExprNode: public EqualityExprNode
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

//exclusive-OR-expr ::= AND-expr | exclusive-OR-expr ^ AND-expr

class ExclusiveOrExprNode: public AndExprNode
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

//inclusive-OR-expr ::= exclusive-OR-expr | inclusive-OR-expr '|' exclusive-OR-expr

class InclusiveOrExprNode: public ExclusiveOrExprNode
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

//logical-AND-expr ::= inclusive-OR-expr | logical-AND-expr && inclusive-OR-expr

class LogicalAndExprNode: public InclusiveOrExprNode
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

//logical-OR-expr ::= logical-AND-expr | logical-OR-expr || logical-AND-expr

class LogicalOrExprNode: public LogicalAndExprNode
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

//conditional-expr ::= logical-OR-expr | logical-OR-expr ? expr : conditional-expr

class ConditionalExprNode: public LogicalOrExprNode
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

class TernaryOperatorNode: public ConditionalExprNode
{
public:
    TernaryOperatorNode(PostfixExprNode *condition, PostfixExprNode *iftrue, PostfixExprNode *iffalse):
                    condition(condition), iftrue(iftrue), iffalse(iffalse) {}
    void Print(std::ostream &os, int depth) override;
private:
    PostfixExprNode *condition, *iftrue, *iffalse;
};

//constant-expr ::= conditional-expr

class ConstantExprNode: public ConditionalExprNode
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

//assignment-expr ::= conditional-expr | unary-expr assignment-op assignment-expr

class AssignmentExprNode: public ConditionalExprNode
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

class AssignmentNode: public AssignmentExprNode
{
public:
    AssignmentNode(PostfixExprNode *left, PostfixExprNode *right, Token *assignmentOp): left(left), right(right),
                                                                                    assignmentOp(assignmentOp) {}
    void Print(std::ostream &os, int depth) override;
private:
    PostfixExprNode *left, *right;
    Token *assignmentOp;
};

//expr ::= assignment-expr | expr , assignment-expr

class ExprNode: public AssignmentExprNode
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

class CommaSeparatedExprs: public ExprNode
{
public:
    CommaSeparatedExprs(PostfixExprNode *left, PostfixExprNode *right): left(left), right(right) {}
    void Print(std::ostream &os, int depth) override;
private:
    PostfixExprNode *left, *right;
};

class SpecifierQualifierListNode;
class DeclaratorNode;

class TypeNameNode: public Node
{
public:
    TypeNameNode(SpecifierQualifierListNode *specifierQualifierList, DeclaratorNode *abstractDeclarator):
            specifierQualifierList(specifierQualifierList), abstractDeclarator(abstractDeclarator) {}
    void Print(std::ostream &os, int depth) override;
private:
    SpecifierQualifierListNode *specifierQualifierList;
    DeclaratorNode *abstractDeclarator;
};

//specifier-qualifier-list ::= type-specifier `specifier-qualifier-list
//| type-qualifier `specifier-qualifier-list

class SpecifierQualifierListNode: public Node
{
public:
    void Print(std::ostream &os, int depth) override;
    void Add(TypeSpecifierQualifierNode *typeSpecifierQualifier);
    uint64_t Size();
private:
    std::list<TypeSpecifierQualifierNode *> specifierQualifierList;
};

//type-qualifier-list ::= type-qualifier | type-qualifier-list type-qualifier

class TypeQualifierListNode: public Node
{
public:
    void Print(std::ostream &os, int depth) override;
    void Add(TypeQualifierNode *typeSpecifierQualifier);
    uint64_t Size();
private:
    std::list<TypeQualifierNode *> qualifierList;
};

//pointer ::= * `type-qualifier-list | * `type-qualifier-list pointer

class PointerNode: public Node
{
public:
    PointerNode(TypeQualifierListNode *typeQualifierList, PointerNode *pointer):
            typeQualifierList(typeQualifierList), pointer(pointer) {}
    void Print(std::ostream &os, int depth) override;
private:
    TypeQualifierListNode *typeQualifierList;
    PointerNode *pointer;
};

class TypeCastNode: public CastExprNode
{
public:
    TypeCastNode(TypeNameNode *typeName, PostfixExprNode *castExpr): typeName(typeName), castExpr(castExpr) {}
    void Print(std::ostream &os, int depth) override;
private:
    TypeNameNode *typeName;
    PostfixExprNode *castExpr;
};

//statement ::= labeled-statement | compound-statement
//              | expression-statement | selection-statement
//              | iteration-statement | jump-statement

class StatementNode: public Node
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

//expression-statement ::= `expr ;

class ExprStatmentNode: StatementNode
{
public:
    explicit ExprStatmentNode(PostfixExprNode *expr): expr(expr) {}
    void Print(std::ostream &os, int depth) override;
private:
    PostfixExprNode *expr;
};

//selection-statement ::= if (expr) statement
//| if (expr) statement else statement
//| switch (expr) statement

class SelectionStatementNode: public StatementNode
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

class IfStatementNode: public SelectionStatementNode
{
public:
    IfStatementNode() = default;
    IfStatementNode(PostfixExprNode *expr, StatementNode *then): expr(expr), then(then) {}
    void Print(std::ostream &os, int depth) override;
protected:
    PostfixExprNode *expr;
    StatementNode *then;
};

class IfElseStatementNode: public IfStatementNode
{
public:
    IfElseStatementNode(PostfixExprNode *expr, StatementNode *then, StatementNode *_else):
            IfStatementNode(expr, then), _else(_else) {}
    void Print(std::ostream &os, int depth) override;
private:
    StatementNode *_else;
};

//jump-statement ::= goto id ;
//                  | continue ;
//                  | break ;
//                  | return `expr ;

class JumpStatementNode: public StatementNode
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

class GotoStatementNode: public JumpStatementNode
{
public:
    explicit GotoStatementNode(IdNode *id): id(id) {}
    void Print(std::ostream &os, int depth) override;
private:
    IdNode *id;
};

class ContinueStatementNode: public JumpStatementNode
{
public:
    ContinueStatementNode() = default;
    void Print(std::ostream &os, int depth) override;
};

class BreakStatementNode: public JumpStatementNode
{
public:
    BreakStatementNode() = default;
    void Print(std::ostream &os, int depth) override;
};

class ReturnStatementNode: public JumpStatementNode
{
public:
    explicit ReturnStatementNode(PostfixExprNode *expr): expr(expr) {}
    void Print(std::ostream &os, int depth) override;
private:
    PostfixExprNode *expr;
};

//iteration-statement ::= while (expr) statement
//                      | do statement while (expr) ;
//                      | for (`expr ; `expr ; `expr) statement
//                      | for (declaration `expr; `expr) statement

class IterationStatementNode: public StatementNode
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

class WhileStatementNode: public IterationStatementNode
{
public:
    WhileStatementNode(PostfixExprNode *condition, StatementNode *body): condition(condition), body(body) {}
    void Print(std::ostream &os, int depth) override;
private:
    PostfixExprNode *condition;
    StatementNode *body;
};

class DoWhileStatementNode: public IterationStatementNode
{
public:
    DoWhileStatementNode(PostfixExprNode *condition, StatementNode *body): condition(condition), body(body) {}
    void Print(std::ostream &os, int depth) override;
private:
    PostfixExprNode *condition;
    StatementNode *body;
};

class ForStatementNode: public IterationStatementNode
{
public:
    ForStatementNode(ExprStatmentNode *init, ExprStatmentNode *condition,
                     PostfixExprNode *iteration, StatementNode *body):
            init(init), condition(condition), iteration(iteration), body(body) {}
    void Print(std::ostream &os, int depth) override;
private:
    ExprStatmentNode *init, *condition;
    PostfixExprNode *iteration;
    StatementNode *body;
};

//labeled-statement ::= id : statement

class LabeledStatementNode: public StatementNode
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

class LabelStatementNode: public LabeledStatementNode
{
public:
    LabelStatementNode(IdNode *labelName, StatementNode *statement): labelName(labelName), statement(statement) {}
    void Print(std::ostream &os, int depth) override;
private:
    IdNode *labelName;
    StatementNode *statement;
};

//compound-statement ::= {`block-item-list}

class BlockItemListNode;

class CompoundStatement: public StatementNode
{
public:
    explicit CompoundStatement(BlockItemListNode *blockItemList): blockItemList(blockItemList) {}
    void Print(std::ostream &os, int depth) override;
private:
    BlockItemListNode *blockItemList;
};

class BlockItemNode: public Node
{
public:
    explicit BlockItemNode(Node *declOrStatement): declOrStatement(declOrStatement) {}
    void Print(std::ostream &os, int depth) override;
private:
    Node *declOrStatement;
};

class BlockItemListNode: public Node
{
public:
    void Print(std::ostream &os, int depth) override;
    void Add(BlockItemNode *blockItem);
    uint64_t Size();
private:
    std::list<BlockItemNode *> list;
};

//direct-declarator ::= id | direct-declarator [constant-expr]
//                      | direct-declarator (parameter-type-list)

class DirectDeclaratorNode;

class DeclaratorNode: public Node
{
public:
    DeclaratorNode () = default;
    DeclaratorNode(PointerNode *pointer, DirectDeclaratorNode *directDeclarator):
            pointer(pointer), directDeclarator(directDeclarator) {}
    void Print(std::ostream &os, int depth) override;
private:
    DirectDeclaratorNode *directDeclarator;
    PointerNode *pointer;
};

class DirectDeclaratorNode: public DeclaratorNode
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

class ArrayDeclaratorNode: public DirectDeclaratorNode
{
public:
    ArrayDeclaratorNode(DirectDeclaratorNode *directDeclarator, ConditionalExprNode *size):
            directDeclarator(directDeclarator), size(size) {}
    void Print(std::ostream &os, int depth) override;
private:
    DirectDeclaratorNode *directDeclarator;
    ConditionalExprNode  *size;
};

class ParameterTypeList;

class FunctionDeclaratorNode: public DirectDeclaratorNode
{
public:
    FunctionDeclaratorNode(DirectDeclaratorNode *directDeclarator, ParameterTypeList *params):
            params(params), directDeclarator(directDeclarator) {}
    void Print(std::ostream &os, int depth) override;
private:
    DirectDeclaratorNode *directDeclarator;
    ParameterTypeList    *params;
};

//parameter-declaration ::= declaration-specifiers declarator | declaration-specifiers `abstract-declarator

class DeclarationSpecifiersNode: public Node
{
public:
    void Print(std::ostream &os, int depth) override;
    void Add(DeclarationSpecifierNode *specifier);
    uint64_t Size();
private:
    std::list<DeclarationSpecifierNode *> list;
};

class ParameterDeclarationNode: public Node
{
public:
    ParameterDeclarationNode(DeclarationSpecifiersNode *specifiers, DeclaratorNode *declarator):
            specifiers(specifiers), declarator(declarator) {}
    void Print(std::ostream &os, int depth) override;
private:
    DeclarationSpecifiersNode *specifiers;
    DeclaratorNode *declarator;
};

//parameter-type-list ::= parameter-list | parameter-list , ...

class ParameterTypeList: public Node
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

//parameter-list ::= parameter-declaration | parameter-list , parameter-declaration

class ParameterList: public ParameterTypeList
{
public:
    void Print(std::ostream &os, int depth) override;
    void Add(ParameterDeclarationNode *specifier);
    uint64_t Size();
protected:
    std::list<ParameterDeclarationNode *> list;
};

//declaration ::= declaration-specifiers `init-declarator-list ;
class InitDeclaratorListNode;

class DeclarationNode: public Node
{
public:
    DeclarationNode(DeclarationSpecifiersNode *declarationSpecifiers, InitDeclaratorListNode *list):
            declarationSpecifiers(declarationSpecifiers), list(list) {}
    void Print(std::ostream &os, int depth) override;
private:
    DeclarationSpecifiersNode *declarationSpecifiers;
    InitDeclaratorListNode    *list;
};

class InitializerNode;

class InitDeclaratorNode: public Node
{
public:
    InitDeclaratorNode(DeclaratorNode *declarator, InitializerNode *initializer):
            declarator(declarator), initializer(initializer) {}
    void Print(std::ostream &os, int depth) override;
private:
    DeclaratorNode *declarator;
    InitializerNode *initializer;
};

class InitDeclaratorListNode: public Node
{
public:
    void Print(std::ostream &os, int depth) override;
    void Add(InitDeclaratorNode *initDeclarator);
    uint64_t Size();
protected:
    std::list<InitDeclaratorNode *> list;
};

//initializer ::= assignment-expr | {initializer-list} | {initializer-list , }

class InitializerNode: public Node
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

//enumerator ::= enumeration-constant, enumeration-constant = constant-expr

class EnumeratorNode: public Node
{
public:
    EnumeratorNode(IdNode *enumerationConstant, ConstantExprNode *value):
            enumerationConstant(enumerationConstant), value(value) {}
    void Print(std::ostream &os, int depth) override;
private:
    IdNode *enumerationConstant;
    ConstantExprNode *value;
};

//enumerator-list ::= enumerator | enumerator-list , enumerator


class EnumeratorList: public Node
{
public:
    void Print(std::ostream &os, int depth) override;
    void Add(EnumeratorNode *initDeclarator);
    uint64_t Size();
protected:
    std::list<EnumeratorNode *> list;
};

//enum-specifier ::= enum `id {enumerator-list}
//                  | enum `id {enumerator-list , }
//                  | enum id

class EnumSpecifierNode: public Node
{
public:
    EnumSpecifierNode(IdNode *id, EnumeratorList *enumeratorList): id(id), enumeratorList(enumeratorList) {}
    void Print(std::ostream &os, int depth) override;
private:
    IdNode *id;
    EnumeratorList *enumeratorList;
};

//struct-declarator ::= declarator | `declarator : constant-expr

class StructDeclaratorNode: public Node
{
public:
    StructDeclaratorNode(DeclaratorNode *declarator, ConstantExprNode *constantExpr):
            declarator(declarator), constantExpr(constantExpr) {}
    void Print(std::ostream &os, int depth) override;
private:
    DeclaratorNode *declarator;
    ConstantExprNode *constantExpr;
};

//struct-declarator-list ::= struct-declarator | struct-declarator-list , struct-declarator

class StructDeclaratorListNode: public Node
{
public:
    void Print(std::ostream &os, int depth) override;
    void Add(StructDeclaratorNode *initDeclarator);
    uint64_t Size();
protected:
    std::list<StructDeclaratorNode *> list;
};

//struct-declaration ::= specifier-qualifier-list struct-declarator-list ;

class StructDeclarationNode: public Node
{
public:
    StructDeclarationNode(SpecifierQualifierListNode *specifierQualifierList,
                      StructDeclaratorListNode *structDeclaratorList):
            specifierQualifierList(specifierQualifierList), structDeclaratorList(structDeclaratorList){}
    void Print(std::ostream &os, int depth) override;
private:
    SpecifierQualifierListNode *specifierQualifierList;
    StructDeclaratorListNode   *structDeclaratorList;
};

//struct-declaration-list ::= struct-declaration | struct-declaration-list struct declaration

class StructDeclarationListNode: public Node
{
public:
    void Print(std::ostream &os, int depth) override;
    void Add(StructDeclarationNode *initDeclarator);
    uint64_t Size();
protected:
    std::list<StructDeclarationNode *> list;
};

//struct-specifier ::= struct `id {struct-declaration-list}
//                     | struct id

class StructSpecifierNode: public DeclarationSpecifierNode
{
public:
    StructSpecifierNode(IdNode *id, StructDeclarationListNode *structDeclaratorList):
            id(id), structDeclaratorList(structDeclaratorList) {}
    void Print(std::ostream &os, int depth) override;
private:
    IdNode *id;
    StructDeclarationListNode *structDeclaratorList;
};

// primary-expr ::= id | constant | string-literal | (expr)

class PrimaryExprNode: public PostfixExprNode
{
public:
    void Print(std::ostream &os, int depth) override = 0;
};

class IdNode: public PrimaryExprNode
{
public:
    explicit IdNode(Token *token);
    void Print(std::ostream &os, int depth) override;
private:
    Token *token;
};

class ConstNode: public PrimaryExprNode
{
public:
    explicit ConstNode(Token *token): token(token) {}
    void Print(std::ostream &os, int depth) override = 0;
protected:
    Token *token;
};

class IntConstNode: public ConstNode
{
public:
    explicit IntConstNode(Token *token);
    void Print(std::ostream &os, int depth) override;
};

class FloatConstNode: public ConstNode
{
public:
    explicit FloatConstNode(Token *token);
    void Print(std::ostream &os, int depth) override;
};

class StringLiteralNode: public PrimaryExprNode
{
public:
    explicit StringLiteralNode(Token *token);
    void Print(std::ostream &os, int depth) override;
private:
    Token *token;
};

#endif //TINY_C_COMPILER_NODE_H
