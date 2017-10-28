//
// Created by keltar on 10/14/17.
//

#ifndef TINY_C_COMPILER_NODE_H
#define TINY_C_COMPILER_NODE_H

#include "token.h"
#include "specifier_qualifier_list.h"
#include <iostream>
#include <utility>
#include <vector>

// Abstract Class
class Node
{
public:
    virtual void Print(std::ostream &os, int depth) = 0;
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

class TypeNameNode: public Node
{
public:
    void Print(std::ostream &os, int depth) override;
    SpecifierQualifierList &List();
private:
    SpecifierQualifierList list;
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
