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

class ExprNode: public Node
{
public:
    void Print(std::ostream &os, int depth, std::vector<int> &depths, SubtreeType type) override = 0;
};

class BinOpNode: public ExprNode
{
public:
    BinOpNode(Token *op, ExprNode *left, ExprNode *right);

    void Print(std::ostream &os, int depth, std::vector<int> &depths, SubtreeType type) override;
private:
    ExprNode *left, *right;
    Token *op;
};

class ConstNode: public ExprNode
{
public:
    void Print(std::ostream &os, int depth, std::vector<int> &depths, SubtreeType type) override = 0;
};

class IntConstNode: public ConstNode
{
public:
    explicit IntConstNode(uint64_t value): value(value) {}
    void Print(std::ostream &os, int depth, std::vector<int> &depths, SubtreeType type) override;
private:
    uint64_t value;
};

class FloatConstNode: public ConstNode
{
public:
    explicit FloatConstNode(long double value): value(value) {}
    void Print(std::ostream &os, int depth, std::vector<int> &depths, SubtreeType type) override;
private:
    long double value;
};

class IdNode: public ExprNode
{
public:
    explicit IdNode(std::string value): value(std::move(value)) {}
    void Print(std::ostream &os, int depth, std::vector<int> &depths, SubtreeType type) override;
private:
    std::string value;
};

#endif //TINY_C_COMPILER_NODE_H
