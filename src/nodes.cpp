//
// Created by keltar on 10/14/17.
//

#include "../includes/nodes.h"

void IntConstNode::Print(std::ostream &os)
{
    os << token->intValue;
}

IntConstNode::IntConstNode(Token *token): ConstNode(token)
{
    if (token->type != TokenType::NUM_INT) throw "";
}

void FloatConstNode::Print(std::ostream &os)
{
    os << token->floatValue;
}

FloatConstNode::FloatConstNode(Token *token): ConstNode(token)
{
    if (token->type != TokenType::NUM_FLOAT) throw "";
}

void IdNode::Print(std::ostream &os)
{
    os << token->stringValue;
}

IdNode::IdNode(Token *token): token(token)
{
    if (token->type != TokenType::ID) throw "";
}

void StringLiteralNode::Print(std::ostream &os)
{
    os << token->stringValue;
}

StringLiteralNode::StringLiteralNode(Token *token): token(token)
{
    if (token->type != TokenType::STRING) throw "";
}

void PostfixIncrementNode::Print(std::ostream &os)
{
    node->Print(os);
    os << "++";
}

void PostfixDecrementNode::Print(std::ostream &os)
{
    node->Print(os);
    os << "--";
}

void StructureOrUnionMemberAccessNode::Print(std::ostream &os)
{
    structureOrUnion->Print(os);
    os << ".";
    member->Print(os);
}

void StructureOrUnionMemberAccessByPointerNode::Print(std::ostream &os)
{
    structureOrUnion->Print(os);
    os << "->";
    member->Print(os);
}

void PrefixIncrementNode::Print(std::ostream &os)
{
    os << "++";
    node->Print(os);
}

void PrefixDecrementNode::Print(std::ostream &os)
{
    os << "--";
    node->Print(os);
}
