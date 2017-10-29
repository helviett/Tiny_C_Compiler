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

void TernaryOperatorNode::Print(std::ostream &os, int depth)
{
    condition->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << "?" << std::endl;
    iftrue->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << ":" << std::endl;
    iffalse->Print(os, depth + 1);
}


void AssignmentNode::Print(std::ostream &os, int depth)
{
    left->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << assignmentOp->stringValue << std::endl;
    right->Print(os, depth + 1);
}

void TypeCastNode::Print(std::ostream &os, int depth)
{
    castExpr->Print(os, depth + 1);
    typeName->Print(os, depth);
}

void UnaryOpNode::Print(std::ostream &os, int depth)
{
    expr->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << unaryOp->stringValue << std::endl;
}

void SizeofExprNode::Print(std::ostream &os, int depth)
{
    expr->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << "sizeof" << std::endl;
}

void SizeofTypeNameNode::Print(std::ostream &os, int depth)
{
    typeName->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << "sizeof" << std::endl;
}

void CommaSeparatedExprs::Print(std::ostream &os, int depth)
{
    left->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << "," << std::endl;
    right->Print(os, depth + 1);
}

void SpecifierQualifierListNode::Print(std::ostream &os, int depth)
{
    os << std::string(depth * 4, ' ');
    for (auto it = specifierQualifierList.begin(); it != specifierQualifierList.end(); it++)
        os << (*it)->SpecOrQual()->text << " ";
    os << std::endl;
}

void SpecifierQualifierListNode::Add(TypeSpecifierQualifier *typeSpecifierQualifier)
{
    specifierQualifierList.push_back(typeSpecifierQualifier);
}

uint64_t SpecifierQualifierListNode::Size()
{
    return specifierQualifierList.size();
}

void TypeQualifierListNode::Print(std::ostream &os, int depth)
{
    os << std::string(depth * 4, ' ');
    for (auto it = qualifierList.begin(); it != qualifierList.end(); it++)
        os << (*it)->SpecOrQual()->text << " ";
    os << std::endl;
}

void TypeQualifierListNode::Add(TypeQualifier *typeSpecifierQualifier)
{
    qualifierList.push_back(typeSpecifierQualifier);
}

uint64_t TypeQualifierListNode::Size()
{
    return qualifierList.size();
}

void PointerNode::Print(std::ostream &os, int depth)
{
    os << std::string(depth * 4, ' ') << "*" << std::endl;
    typeQualifierList->Print(os, depth + 1);
    if (pointer) pointer->Print(os, depth + 2);
}

void ExprStatmentNode::Print(std::ostream &os, int depth)
{
    if (expr) expr->Print(os, depth + 1);
}

void IfStatementNode::Print(std::ostream &os, int depth)
{
    expr->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << "if" << std::endl;
    then->Print(os, depth + 1);
}

void IfElseStatementNode::Print(std::ostream &os, int depth)
{
    expr->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << "if" << std::endl;
    then->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << "else" <<  std::endl;
    _else->Print(os, depth + 1);
}

void GotoStatementNode::Print(std::ostream &os, int depth)
{
    id->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << "goto" << std::endl;
}

void ContinueStatementNode::Print(std::ostream &os, int depth)
{
    os << std::string(depth * 4, ' ') << "continue" << std::endl;
}

void BreakStatementNode::Print(std::ostream &os, int depth)
{
    os << std::string(depth * 4, ' ') << "break" << std::endl;
}

void ReturnStatementNode::Print(std::ostream &os, int depth)
{
    if (expr) expr->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << "return" << std::endl;
}
