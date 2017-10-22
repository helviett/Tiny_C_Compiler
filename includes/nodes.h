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
    Node *parent = nullptr;
    Node *child = nullptr;

    virtual void Print(std::ostream &os, int depth, std::vector<int> &depths, SubtreeType type) = 0;
};

class PrimaryExprNode: public Node
{
public:
    void Print(std::ostream &os, int depth, std::vector<int> &depths, SubtreeType type) override = 0;
};

class ConstNode: public PrimaryExprNode
{
public:
    ConstNode(Token *token): token(token) {}
    void Print(std::ostream &os, int depth, std::vector<int> &depths, SubtreeType type) override = 0;
protected:
    Token *token;
};

class IntConstNode: public ConstNode
{
public:
    explicit IntConstNode(Token *token);
    void Print(std::ostream &os, int depth, std::vector<int> &depths, SubtreeType type) override;
};

class FloatConstNode: public ConstNode
{
public:
    explicit FloatConstNode(Token *token);
    void Print(std::ostream &os, int depth, std::vector<int> &depths, SubtreeType type) override;
};

class IdNode: public PrimaryExprNode
{
public:
    explicit IdNode(Token *token);
    void Print(std::ostream &os, int depth, std::vector<int> &depths, SubtreeType type) override;
private:
    Token *token;
};

class StringLiteralNode: public PrimaryExprNode
{
public:
    explicit StringLiteralNode(Token *token);
    void Print(std::ostream &os, int depth, std::vector<int> &depths, SubtreeType type) override;
private:
    Token *token;
};

#endif //TINY_C_COMPILER_NODE_H
