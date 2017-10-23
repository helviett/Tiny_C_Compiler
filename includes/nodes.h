//
// Created by keltar on 10/14/17.
//

#ifndef TINY_C_COMPILER_NODE_H
#define TINY_C_COMPILER_NODE_H

#include "token.h"
#include <iostream>
#include <utility>
#include <vector>

enum class SubtreeType
{
    Left, Right
};

class Node
{
public:
    virtual void Print(std::ostream &os) = 0;
};

class PostfixExprNode: public Node
{
public:
    virtual void Print(std::ostream &os) = 0;
};

class PostfixIncrementNode: public PostfixExprNode
{
public:
    explicit PostfixIncrementNode(PostfixExprNode *node): node(node) {}
    virtual void Print(std::ostream &os);
private:
    PostfixExprNode *node;
};

class PostfixDecrementNode: public PostfixExprNode
{
public:
    explicit PostfixDecrementNode(PostfixExprNode *node): node(node) {}
    virtual void Print(std::ostream &os);
private:
    PostfixExprNode *node;
};

class PrimaryExprNode: public PostfixExprNode
{
public:
    void Print(std::ostream &os) override = 0;
};


class IdNode: public PrimaryExprNode
{
public:
    explicit IdNode(Token *token);
    void Print(std::ostream &os) override;
private:
    Token *token;
};

class StructureOrUnionMemberAccess: public PostfixExprNode
{
public:
    StructureOrUnionMemberAccess(PostfixExprNode *structureOrUnion, IdNode *member): member(member),
                                                                                             structureOrUnion(structureOrUnion) {}
    virtual void Print(std::ostream &os);
private:
    PostfixExprNode *structureOrUnion;
    IdNode *member;
};


class ConstNode: public PrimaryExprNode
{
public:
    explicit ConstNode(Token *token): token(token) {}
    void Print(std::ostream &os) override = 0;
protected:
    Token *token;
};

class IntConstNode: public ConstNode
{
public:
    explicit IntConstNode(Token *token);
    void Print(std::ostream &os) override;
};

class FloatConstNode: public ConstNode
{
public:
    explicit FloatConstNode(Token *token);
    void Print(std::ostream &os) override;
};

class StringLiteralNode: public PrimaryExprNode
{
public:
    explicit StringLiteralNode(Token *token);
    void Print(std::ostream &os) override;
private:
    Token *token;
};

#endif //TINY_C_COMPILER_NODE_H
