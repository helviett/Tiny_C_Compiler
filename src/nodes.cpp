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
        os << (*it)->Value()->text << " ";
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
        os << (*it)->Value()->text << " ";
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

void WhileStatementNode::Print(std::ostream &os, int depth)
{
    condition->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << "while" << std::endl;
    body->Print(os, depth + 1);
}

void DoWhileStatementNode::Print(std::ostream &os, int depth)
{
    os << std::string(depth * 4, ' ') << "do" << std::endl;
    body->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << "while" <<  std::endl;
    condition->Print(os, depth + 1);
}

void ForStatementNode::Print(std::ostream &os, int depth)
{
    os << std::string(depth * 4, ' ') << "for" << std::endl;
    init->Print(os, depth + 1);
    condition->Print(os, depth + 1);
    if (iteration) iteration->Print(os, depth + 1);
    body->Print(os, depth + 1);
}

void LabelStatement::Print(std::ostream &os, int depth)
{
    labelName->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << ":" << std::endl;
    statement->Print(os, depth + 1);
}

void TypeNameNode::Print(std::ostream &os, int depth)
{
    specifierQualifierList->Print(os, depth + 1);
    if (abstractDeclarator) abstractDeclarator->Print(os, depth + 1);
}

void DeclaratorNode::Print(std::ostream &os, int depth)
{
    if (pointer) pointer->Print(os, depth + 1);
    if (directDeclarator) directDeclarator->Print(os, depth + 2);
}

void ArrayDeclaratorNode::Print(std::ostream &os, int depth)
{
    if (directDeclarator) directDeclarator->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << "[" << std::endl;
    if (size) size->Print(os, depth + 1);
    os << std::string(depth * 4, ' ') << "]" << std::endl;
}

void ArgumentExprListNode::Print(std::ostream &os, int depth)
{
    for (auto it = list.begin(); it != list.end(); it++)
        (*it)->Print(os, depth + 1);
}

void ArgumentExprListNode::Add(AssignmentExprNode *assignmentExpr)
{
    list.push_back(assignmentExpr);
}

uint64_t ArgumentExprListNode::Size()
{
    return list.size();
}

void FunctionCallNode::Print(std::ostream &os, int depth)
{
    functionName->Print(os, depth + 1);
    os << std::string((depth + 1) * 4, ' ') << "(" << std::endl;
    arguments->Print(os, depth + 2);
    os << std::string((depth + 1) * 4, ' ') << ")" << std::endl;
}

void DeclarationSpecifiersNode::Print(std::ostream &os, int depth)
{
    os << std::string(depth * 4, ' ');
    for (auto it = list.begin(); it != list.end(); it++)
        os << (*it)->Value()->text << " ";
    os << std::endl;
}

void DeclarationSpecifiersNode::Add(DeclarationSpecifier *specifier)
{
    list.push_back(specifier);
}

uint64_t DeclarationSpecifiersNode::Size()
{
    return list.size();
}

void ParameterList::Print(std::ostream &os, int depth)
{
    for (auto it = list.begin(); it != list.end(); it++)
        (*it)->Print(os, depth + 1);
    os << std::endl;
}

void ParameterList::Add(ParameterDeclarationNode *parameterDeclaration)
{
    list.push_back(parameterDeclaration);
}

uint64_t ParameterList::Size()
{
    return list.size();
}

void ParameterDeclarationNode::Print(std::ostream &os, int depth)
{
    specifiers->Print(os, depth + 1);
    declarator->Print(os, depth + 2);
}

void FunctionDeclaratorNode::Print(std::ostream &os, int depth)
{
    if (directDeclarator) directDeclarator->Print(os, depth + 1);
    os << std::string((depth + 1) * 4, ' ') << "(" << std::endl;
    params->Print(os, depth + 2);
    os << std::string((depth + 1) * 4, ' ') << ")" << std::endl;
}

void DeclarationNode::Print(std::ostream &os, int depth)
{
    declarationSpecifiers->Print(os, depth + 1);
    list->Print(os, depth + 2);
}

uint64_t InitDeclaratorListNode::Size()
{
    return list.size();
}

void InitDeclaratorListNode::Add(InitDeclaratorNode *initDeclarator)
{
    list.push_back(initDeclarator);
}

void InitDeclaratorListNode::Print(std::ostream &os, int depth)
{
    for (auto it = list.begin(); it != list.end(); it++)
        (*it)->Print(os, depth + 1);
    os << std::endl;
}

void InitDeclaratorNode::Print(std::ostream &os, int depth)
{
    declarator->Print(os, depth + 1);
    if (initializer) initializer->Print(os, depth + 1);
}
