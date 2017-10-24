//
// Created by keltar on 10/14/17.
//

#include "../includes/nodes.h"

void IntConstNode::Print(std::ostream &os, int depth)
{
    os << std::string(depth * 4, ' ') << token->intValue << std::endl;
}

IntConstNode::IntConstNode(Token *token): ConstNode(token)
{
    if (token->type != TokenType::NUM_INT) throw "";
}

void FloatConstNode::Print(std::ostream &os, int depth)
{
    os << std::string(depth * 4, ' ') << token->floatValue << std::endl;
}

FloatConstNode::FloatConstNode(Token *token): ConstNode(token)
{
    if (token->type != TokenType::NUM_FLOAT) throw "";
}

void IdNode::Print(std::ostream &os, int depth)
{
    os << std::string(depth * 4, ' ') << token->stringValue << std::endl;
}

IdNode::IdNode(Token *token): token(token)
{
    if (token->type != TokenType::ID) throw "";
}

void StringLiteralNode::Print(std::ostream &os, int depth)
{
    os << std::string(depth * 4, ' ') << token->stringValue << std::endl;
}

StringLiteralNode::StringLiteralNode(Token *token): token(token)
{
    if (token->type != TokenType::STRING) throw "";
}

void PostfixIncrementNode::Print(std::ostream &os, int depth)
{
    node->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << "`++" << std::endl;
}

void PostfixDecrementNode::Print(std::ostream &os, int depth)
{
    node->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << "`--" << std::endl;
}

void StructureOrUnionMemberAccessNode::Print(std::ostream &os, int depth)
{
    structureOrUnion->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << "." << std::endl;
    member->Print(os, depth + 1);
}

void StructureOrUnionMemberAccessByPointerNode::Print(std::ostream &os, int depth)
{
    structureOrUnion->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << "->" << std::endl;
    member->Print(os, depth + 1);
}

void PrefixIncrementNode::Print(std::ostream &os, int depth)
{
    os << std::string(depth * 4, ' ') << "++`" << std::endl;
    node->Print(os, depth + 1);
}

void PrefixDecrementNode::Print(std::ostream &os, int depth)
{
    os << std::string(depth * 4, ' ') << "--`" << std::endl;
    node->Print(os, depth + 1);
}

void BinOpNode::Print(std::ostream &os, int depth)
{
    left->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << op->stringValue << std::endl;
    right->Print(os, depth + 1);
}

void ArrayAccess::Print(std::ostream &os, int depth)
{
    left->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << "[]" << std::endl;
    inBrackets->Print(os, depth + 1);
}

void TernaryOperator::Print(std::ostream &os, int depth)
{
    condition->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << "?" << std::endl;
    iftrue->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << ":" << std::endl;
    iffalse->Print(os, depth + 1);
}
