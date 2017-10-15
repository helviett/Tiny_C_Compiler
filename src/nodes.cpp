//
// Created by keltar on 10/14/17.
//

#include "../includes/nodes.h"

BinOpNode::BinOpNode(Token *op, ExprNode *left, ExprNode *right)
{
    this->op = op;
    this->left = left;
    this->right = right;
}

void BinOpNode::Print(std::ostream &os, int depth)
{
    left->Print(os, depth + 1);
    std::cout << std::string(depth * 4, ' ') << op->stringValue << std::endl;
    right->Print(os, depth + 1);
}

void IntConstNode::Print(std::ostream &os, int depth)
{
    std::cout << std::string(depth * 4, ' ') << value << std::endl;
}
