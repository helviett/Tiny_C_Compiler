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

void BinOpNode::Print(std::ostream &os, int depth, std::vector<int> &depths, SubtreeType type)
{
    depth++;
    right->Print(os, depth, depths, SubtreeType::Right);
    if (depth >= 2)
        depths[depth - 2] = 0;
    if (type == SubtreeType::Right && depth >= 2)
        depths[depth - 2] = 1;
    depths[depth - 1] = 1;
    os << std::endl;

    for (int i = 0; i < depth - 1; ++i)
    {
        if (i == depth - 2)
            os << 'x';
        else if (depths[i])
            os << '|';
        else
            os << ' ';
        for (int j = 1; j < 5; ++j)
            if (i < depth - 2)
                os << ' ';
            else
                os << '-';

    }

    os << op->stringValue << std::endl;

    for (int i = 0; i < depth; ++i)
    {
        if (depths[i])
            os << '|';
        else
            os << ' ';

        for (int j = 1; j < 5; ++j)
            os << ' ';
    }

    left->Print(os, depth, depths, SubtreeType::Left);
}

void IntConstNode::Print(std::ostream &os, int depth, std::vector<int> &depths, SubtreeType type)
{
    depth++;
    if (depth >= 2)
        depths[depth - 2] = 0;
    if (type == SubtreeType::Right && depth >= 2)
        depths[depth - 2] = 1;
    os << std::endl;

    for (int i = 0; i < depth - 1; ++i)
    {
        if (i == depth - 2)
            os << 'x';
        else if (depths[i])
            os << '|';
        else
            os << ' ';
        for (int j = 1; j < 5; ++j)
            if (i < depth - 2)
                os << ' ';
            else
                os << '-';

    }

    os << value << std::endl;

    for (int i = 0; i < depth; ++i)
    {
        if (depths[i])
            os << '|';
        else
            os << ' ';

        for (int j = 1; j < 5; ++j)
            os << ' ';
    }
}
