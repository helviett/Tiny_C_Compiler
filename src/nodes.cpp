//
// Created by keltar on 10/14/17.
//

#include "../includes/nodes.h"

void printAbove(std::ostream &os, int depth, std::vector<int> &depths, SubtreeType type)
{
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
}

void printBelow(std::ostream &os, int depth, std::vector<int> &depths, SubtreeType type)
{
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

void IntConstNode::Print(std::ostream &os, int depth, std::vector<int> &depths, SubtreeType type)
{
    depth++;
    printAbove(os, depth, depths, type);
    os << token->intValue << std::endl;
    printBelow(os, depth, depths, type);
}

IntConstNode::IntConstNode(Token *token): ConstNode(token)
{
    if (token->type != TokenType::NUM_INT) throw "";
}

void FloatConstNode::Print(std::ostream &os, int depth, std::vector<int> &depths, SubtreeType type)
{
    depth++;
    printAbove(os, depth, depths, type);
    os << token->floatValue << std::endl;
    printBelow(os, depth, depths, type);
}

FloatConstNode::FloatConstNode(Token *token): ConstNode(token)
{
    if (token->type != TokenType::NUM_FLOAT) throw "";
}

void IdNode::Print(std::ostream &os, int depth, std::vector<int> &depths, SubtreeType type)
{
    depth++;
    printAbove(os, depth, depths, type);
    os << token->stringValue << std::endl;
    printBelow(os, depth, depths, type);
}

IdNode::IdNode(Token *token): token(token)
{

}

void StringLiteralNode::Print(std::ostream &os, int depth, std::vector<int> &depths, SubtreeType type)
{
    depth++;
    printAbove(os, depth, depths, type);
    os << token->stringValue << std::endl;
    printBelow(os, depth, depths, type);
}

StringLiteralNode::StringLiteralNode(Token *token): token(token)
{
    if (token->type != TokenType::STRING) throw "";
}
