//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_EXPRESSIONS_H
#define TINY_C_COMPILER_EXPRESSIONS_H

#include "node.h"
#include "../token.h"
#include <list>

class SymType;

class ExprNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override = 0;
    SymType *GetType() const;
    void SetType(SymType *type);
protected:
    SymType *type{nullptr};
};

class PostfixIncrementNode: public ExprNode
{
public:
    explicit PostfixIncrementNode(ExprNode *node);
    virtual void Print(std::ostream &os, std::string ident, bool isTail);
private:
    ExprNode *node;
};

class PostfixDecrementNode: public ExprNode
{
public:
    explicit PostfixDecrementNode(ExprNode *node);
    virtual void Print(std::ostream &os, std::string ident, bool isTail);
private:
    ExprNode *node;
};

class IdNode;

class StructureOrUnionMemberAccessNode: public ExprNode
{
public:
    StructureOrUnionMemberAccessNode(ExprNode *structureOrUnion, IdNode *member);

    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    ExprNode *structureOrUnion;
    IdNode *member;
};

class StructureOrUnionMemberAccessByPointerNode: public ExprNode
{
public:
    StructureOrUnionMemberAccessByPointerNode(ExprNode *structureOrUnion, IdNode *member);

    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    ExprNode *structureOrUnion;
    IdNode *member;
};

class ArrayAccess: public ExprNode
{
public:
    ArrayAccess(ExprNode *left, ExprNode *inBrackets);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    ExprNode *left, *inBrackets;
};

class AssignmentExprNode;

class ArgumentExprListNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(AssignmentExprNode *assignmentExpr);
    uint64_t Size();
private:
    std::list<AssignmentExprNode *> list;
};

class FunctionCallNode: public ExprNode
{
public:
    FunctionCallNode(ExprNode *functionName, ArgumentExprListNode *arguments);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    ExprNode *functionName;
    ArgumentExprListNode *arguments;
};

class SizeofExprNode: public  ExprNode
{
public:
    SizeofExprNode(ExprNode *expr);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    ExprNode *expr;
};

class TypeNameNode;

class SizeofTypeNameNode: public ExprNode
{
public:
    SizeofTypeNameNode(TypeNameNode *typeName);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    TypeNameNode *typeName;
};

class UnaryOpNode: public ExprNode
{
public:
    UnaryOpNode (std::shared_ptr<Token> unaryOp, ExprNode *expr);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    std::shared_ptr<Token> unaryOp;
    ExprNode *expr;
};

class PrefixIncrementNode: public ExprNode
{
public:
    explicit PrefixIncrementNode(ExprNode *node);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    ExprNode *node;
};

class PrefixDecrementNode: public ExprNode
{
public:
    explicit PrefixDecrementNode(ExprNode *node);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    ExprNode *node;
};

class BinOpNode: public ExprNode
{
public:
    BinOpNode(ExprNode *left, ExprNode *right, std::shared_ptr<Token> op);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    ExprNode *left, *right;
    std::shared_ptr<Token> op;
};

class TernaryOperatorNode: public ExprNode
{
public:
    TernaryOperatorNode(ExprNode *condition, ExprNode *iftrue, ExprNode *iffalse);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    ExprNode *condition, *iftrue, *iffalse;
};

class AssignmentExprNode: public ExprNode
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override = 0;
};

class AssignmentNode: public AssignmentExprNode
{
public:
    AssignmentNode(ExprNode *left, ExprNode *right, std::shared_ptr<Token> assignmentOp);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    ExprNode *left, *right;
    std::shared_ptr<Token> assignmentOp;
};

class CommaSeparatedExprs: public ExprNode
{
public:
    CommaSeparatedExprs(ExprNode *left, ExprNode *right);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    ExprNode *left, *right;
};

class IdNode: public ExprNode
{
public:
    explicit IdNode(std::shared_ptr<Token> token);
    IdNode(std::shared_ptr<Token> token, SymType *type);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    std::string GetName() const;
private:
    std::shared_ptr<Token> token;
};

class ConstNode: public ExprNode
{
public:
    explicit ConstNode(std::shared_ptr<Token> token);
    void Print(std::ostream &os, std::string ident, bool isTail) override = 0;
protected:
    std::shared_ptr<Token> token;
};

class IntConstNode: public ConstNode
{
public:
    explicit IntConstNode(std::shared_ptr<Token> token);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
};

class FloatConstNode: public ConstNode
{
public:
    explicit FloatConstNode(std::shared_ptr<Token> token);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
};

class StringLiteralNode: public ExprNode
{
public:
    explicit StringLiteralNode(std::shared_ptr<Token> token);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    std::shared_ptr<Token> token;
};

#endif //TINY_C_COMPILER_EXPRESSIONS_H
