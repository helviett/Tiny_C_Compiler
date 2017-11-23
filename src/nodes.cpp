//
// Created by keltar on 10/14/17.
//

#include "../includes/nodes.h"

void IntConstNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << token->intValue << std::endl;
}

IntConstNode::IntConstNode(std::shared_ptr<Token> token): ConstNode(token)
{
    if (token->type != TokenType::NUM_INT) throw "";
}

void FloatConstNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << token->floatValue << std::endl;
}

FloatConstNode::FloatConstNode(std::shared_ptr<Token> token): ConstNode(token)
{
    if (token->type != TokenType::NUM_FLOAT) throw "";
}

void IdNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << token->text << std::endl;
}

IdNode::IdNode(std::shared_ptr<Token> token): token(token)
{
    if (token->type != TokenType::ID) throw "";
}

std::string IdNode::GetName() const
{
    return token->stringValue;
}

void StringLiteralNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << token->text << std::endl;
}

StringLiteralNode::StringLiteralNode(std::shared_ptr<Token> token): token(token)
{
    if (token->type != TokenType::STRING) throw "";
}

void PostfixIncrementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "`++" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    node->Print(os, indent, true);
}

void PostfixDecrementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "`--" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    node->Print(os, indent, true);
}

void StructureOrUnionMemberAccessNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "." << std::endl;
    indent.append(isTail ? "    " : "│   ");
    structureOrUnion->Print(os, indent, false);
    member->Print(os, indent, true);
}

void StructureOrUnionMemberAccessByPointerNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "->" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    structureOrUnion->Print(os, indent, false);
    member->Print(os, indent, true);
}

void PrefixIncrementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "++'" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    node->Print(os, indent, true);
}

void PrefixDecrementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "--`" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    node->Print(os, indent, true);
}

void BinOpNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << op->text << std::endl;
    indent.append(isTail ? "    " : "│   ");
    left->Print(os, indent, false);
    right->Print(os, indent, true);
}

void ArrayAccess::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "[]" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    left->Print(os, indent, false);
    inBrackets->Print(os, indent, true);
}

void TernaryOperatorNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "?:" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    condition->Print(os, indent, false);
    iftrue->Print(os, indent, false);
    iffalse->Print(os, indent, true);
}


void AssignmentNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << assignmentOp->stringValue << std::endl;
    indent.append(isTail ? "    " : "│   ");
    left->Print(os, indent, false);
    right->Print(os, indent, true);
}

void TypeCastNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "typcast" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    typeName->Print(os, indent, false);
    castExpr->Print(os, indent, true);
}

void UnaryOpNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << unaryOp->stringValue << std::endl;
    indent.append(isTail ? "    " : "│   ");
    expr->Print(os, indent, true);
}

void SizeofExprNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "sizeof" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    expr->Print(os, indent, true);
}

void SizeofTypeNameNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "sizeof()" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    typeName->Print(os, indent, true);
}

void CommaSeparatedExprs::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "," << std::endl;
    indent.append(isTail ? "    " : "│   ");
    left->Print(os, indent, false);
    right->Print(os, indent, true);
}

void PointerNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "*" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (pointer)
    {
        typeQualifierList->Print(os, indent, false);
        pointer->Print(os, indent, true);
    }
    else
        typeQualifierList->Print(os, indent, true);
}

void ExprStatmentNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << ";" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (expr) expr->Print(os, indent, true);
}

void IfStatementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "if" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    expr->Print(os, indent, false);
    then->Print(os, indent, true);
}

void IfElseStatementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "if else" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    expr->Print(os, indent, false);
    then->Print(os, indent, false);
    _else->Print(os, indent, true);
}

void GotoStatementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "goto" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    id->Print(os, indent, true);
}

void ContinueStatementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "continue" << std::endl;
}

void BreakStatementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "break" << std::endl;
}

void ReturnStatementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "return" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (expr) expr->Print(os, indent, true);
}

void WhileStatementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "while" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    condition->Print(os, indent, false);
    body->Print(os, indent, true);
}

void DoWhileStatementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "do" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    body->Print(os, indent, false);
    condition->Print(os, indent, true);
}

void ForStatementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "for" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    init->Print(os, indent, false);
    condition->Print(os, indent, false);

    if (iteration)
        iteration->Print(os, indent, false);
    else
        os << indent << "├── " << std::endl;
    body->Print(os, indent, true);

}

void LabelStatementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "label" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    labelName->Print(os, indent, false);
    statement->Print(os, indent, true);
}

void TypeNameNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "TypeName" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    type->Print(os, indent, true);
}

void DeclaratorNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "Declarator" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (id) id->Print(os, indent, false);
    type->Print(os, indent, true);
}

void DeclaratorNode::SetType(SymType *type)
{
    this->type = type;
}

SymType *DeclaratorNode::GetType() const
{
    return type;
}

void DeclaratorNode::SetId(IdNode *name)
{
    this->id = name;
}

IdNode *DeclaratorNode::GetId() const
{
    return id;
}

void ArrayDeclaratorNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "[]" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (directDeclarator)
    {
        if (size)
        {
            directDeclarator->Print(os, indent, false);
            size->Print(os, indent, true);
            return;
        }
        directDeclarator->Print(os, indent, true);
        return;
    }
    else
    {
        if (size)
            size->Print(os, indent, true);
    }
}

void ArgumentExprListNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    if (list.empty()) return;
    os << indent << (isTail ? "└── " : "├── ");
    os << "ArgumentExprList" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    auto it = list.begin();
    if (list.size() > 1)
        for (; it != --list.end(); it++)
            (*it)->Print(os, indent, false);
    (*it)->Print(os, indent, true);
}

void ArgumentExprListNode::Add(AssignmentExprNode *assignmentExpr)
{
    list.push_back(assignmentExpr);
}

uint64_t ArgumentExprListNode::Size()
{
    return list.size();
}

void FunctionCallNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "FuncCall" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (arguments->Size())
    {
        functionName->Print(os, indent, false);
        arguments->Print(os, indent, true);
        return;
    }
    functionName->Print(os, indent, true);
}

void DeclarationSpecifiersNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    if (list.empty()) return;
    os << indent << (isTail ? "└── " : "├── ");
    os << "DeclarationSpecifiers" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    auto it = list.begin();
    if (list.size() > 1)
        for (; it != --list.end(); it++)
            (*it)->Print(os, indent, false);
    (*it)->Print(os, indent, true);
}

void DeclarationSpecifiersNode::Add(DeclarationSpecifierNode *specifier)
{
    list.push_back(specifier);
}

uint64_t DeclarationSpecifiersNode::Size()
{
    return list.size();
}

DeclarationSpecifiersNode::DeclarationSpecifiersNode(std::initializer_list<DeclarationSpecifierNode *> initializerList)
{
    for (auto it : initializerList)
        Add(it);
}

std::list<DeclarationSpecifierNode *> &DeclarationSpecifiersNode::List()
{
    return list;
}

void ParameterList::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "ParameterList" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    auto it = list.begin();
    if (list.size() > 1)
        for (; it != --list.end(); it++)
            (*it)->Print(os, indent, false);
    (*it)->Print(os, indent, true);
}

void ParameterList::Add(ParameterDeclarationNode *parameterDeclaration)
{
    list.push_back(parameterDeclaration);
}

uint64_t ParameterList::Size()
{
    return list.size();
}

std::list<ParameterDeclarationNode *> &ParameterList::List()
{
    return list;
}

void ParameterDeclarationNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "param" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (GetId()) GetId()->Print(os, indent, false);
    GetType()->Print(os, indent, true);
}

ParameterDeclarationNode::ParameterDeclarationNode(DeclaratorNode *declarator)
{
    SetId(declarator->GetId());
    SetType(declarator->GetType());
}

void FunctionDeclaratorNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "Func Decl" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (directDeclarator) directDeclarator->Print(os, indent, false);
    params->Print(os, indent, true);
}

void DeclarationNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "Decl" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (list) list->Print(os, indent, true);
}

uint64_t InitDeclaratorListNode::Size()
{
    return list.size();
}

void InitDeclaratorListNode::Add(InitDeclaratorNode *initDeclarator)
{
    list.push_back(initDeclarator);
}

void InitDeclaratorListNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    if (list.empty()) return;
    os << indent << (isTail ? "└── " : "├── ");
    os << "InitDeclaratorList" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    auto it = list.begin();
    if (list.size() > 1)
        for (; it != --list.end(); it++)
            (*it)->Print(os, indent, false);
    (*it)->Print(os, indent, true);
}

void InitDeclaratorNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "InitDeclarator" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    GetId()->Print(os, indent, false);
    GetType()->Print(os, indent, !initializer);
    if (initializer) initializer->Print(os, indent, true);
}

InitDeclaratorNode::InitDeclaratorNode(DeclaratorNode *declarator, InitializerNode *initializer): initializer(initializer)
{
    SetType(declarator->GetType());
    SetId(declarator->GetId());
}

InitializerNode *InitDeclaratorNode::GetInitializer() const
{
    return initializer;
}

void CompoundStatement::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "{}" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (blockItemList) blockItemList->Print(os, indent, true);
}

void BlockItemNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << std::endl;
    indent.append(isTail ? "    " : "│   ");
    declOrStatement->Print(os, indent, true);
}

uint64_t BlockItemListNode::Size()
{
    return list.size();
}

void BlockItemListNode::Add(BlockItemNode *blockItem)
{
    list.push_back(blockItem);
}

void BlockItemListNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    if (list.empty()) return;
    os << indent << (isTail ? "└── " : "├── ");
    os << "BlockItemList" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    auto it = list.begin();
    if (list.size() > 1)
        for (; it != --list.end(); it++)
            (*it)->Print(os, indent, false);
    (*it)->Print(os, indent, true);
}

uint64_t EnumeratorList::Size()
{
    return list.size();
}

void EnumeratorList::Add(EnumeratorNode *initDeclarator)
{
    list.push_back(initDeclarator);
}

void EnumeratorList::Print(std::ostream &os, std::string indent, bool isTail)
{
    if (list.empty()) return;
    os << indent << (isTail ? "└── " : "├── ");
    os << "EnumeratorList" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    auto it = list.begin();
    if (list.size() > 1)
        for (; it != --list.end(); it++)
            (*it)->Print(os, indent, false);
    (*it)->Print(os, indent, true);
}

void EnumSpecifierNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "enum" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (id)
    {
        if (enumeratorList)
        {
            id->Print(os, indent, false);
            enumeratorList->Print(os, indent, true);
            return;
        }
        id->Print(os, indent, true);
        return;
    }
    enumeratorList->Print(os, indent, true);
}

void EnumeratorNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "Enumerator" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (value)
    {
        enumerationConstant->Print(os, indent, false);
        value->Print(os, indent, true);
        return;
    }
    enumerationConstant->Print(os, indent, true);
}

void TypeSpecifierQualifierNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << value->text << std::endl;
}

void TypeSpecifierNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << value->text << std::endl;
}

void TypeQualifierNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << value->text << std::endl;
}

void StorageClassSpecifierNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << value->text << std::endl;
}

void FunctionSpecifierNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << value->text << std::endl;
}

void SimpleSpecifier::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << value->text << std::endl;
}

std::shared_ptr<Token> SimpleSpecifier::Value()
{
    return value;
}

void StructDeclaratorListNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    if (list.empty()) return;
    os << indent << (isTail ? "└── " : "├── ");
    os << "StructDeclaratorList" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    auto it = list.begin();
    if (list.size() > 1)
        for (; it != --list.end(); it++)
            (*it)->Print(os, indent, false);
    (*it)->Print(os, indent, true);
}

void StructDeclaratorListNode::Add(StructDeclaratorNode *initDeclarator)
{
    list.push_back(initDeclarator);
}

uint64_t StructDeclaratorListNode::Size()
{
    return list.size();
}

void StructDeclarationNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "StructDeclaratorList" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    structDeclaratorList->Print(os, indent, true);
}

uint64_t StructDeclarationListNode::Size()
{
    return list.size();
}

void StructDeclarationListNode::Add(StructDeclarationNode *initDeclarator)
{
    list.push_back(initDeclarator);
}

void StructDeclarationListNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    if (list.empty()) return;
    os << indent << (isTail ? "└── " : "├── ");
    os << "StructDeclarationList" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    auto it = list.begin();
    if (list.size() > 1)
        for (; it != --list.end(); it++)
            (*it)->Print(os, indent, false);
    (*it)->Print(os, indent, true);
}

void StructSpecifierNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "struct" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (id)
    {
        if (structDeclaratorList)
        {
            id->Print(os, indent, false);
            structDeclaratorList->Print(os, indent, true);
            return;
        }
        id->Print(os, indent, true);
        return;
    }
    structDeclaratorList->Print(os, indent, true);
}

void StructDeclaratorNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "StructDeclarator" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (declarator)
    {
        if (constantExpr)
        {
            declarator->Print(os, indent, false);
            constantExpr->Print(os, indent, true);
            return;
        }
        declarator->Print(os, indent, true);
        return;
    }
    constantExpr->Print(os, indent, true);
}

uint64_t InitializerListNode::Size()
{
    return list.size();
}

void InitializerListNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    if (list.empty()) return;
    os << indent << (isTail ? "└── " : "├── ");
    os << "InitializerList" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    auto it = list.begin();
    if (list.size() > 1)
        for (; it != --list.end(); it++)
            (*it)->Print(os, indent, false);
    (*it)->Print(os, indent, true);
}

void InitializerListNode::Add(DesignatedInitializerNode *initializer)
{
    list.push_back(initializer);
}

void DesignatorListNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    if (list.empty()) return;
    os << indent << (isTail ? "└── " : "├── ");
    os << "DesignatorList" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    auto it = list.begin();
    if (list.size() > 1)
        for (; it != --list.end(); it++)
            (*it)->Print(os, indent, false);
    (*it)->Print(os, indent, true);
}

void DesignatorListNode::Add(DesignatorNode *designator)
{
    list.push_back(designator);
}

uint64_t DesignatorListNode::Size()
{
    return list.size();
}

void ArrayDesignator::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "[]" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    constantExpr->Print(os, indent, true);
}

void DesignationNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    designatorList->Print(os, indent, true);
}

void StructMemberDesignator::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "." << std::endl;
    indent.append(isTail ? "    " : "│   ");
    id->Print(os, indent, true);
}

void DesignatedInitializerNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "DesignatedInitializer" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (designation) designation->Print(os, indent, false);
    initializer->Print(os, indent, true);
}

void FunctionDefinitionNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "FuncDef" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    declarator->Print(os, indent, false);
    compoundStatement->Print(os, indent, true);
}

void TranslationUnitNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    if (list.empty()) return;
    os << indent << (isTail ? "└── " : "├── ");
    os << "Unit" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    auto it = list.begin();
    if (list.size() > 1)
        for (; it != --list.end(); it++)
            (*it)->Print(os, indent, false);
    (*it)->Print(os, indent, true);
}

void TranslationUnitNode::Add(ExternalDeclarationNode *initDeclarator)
{
    list.push_back(initDeclarator);
}

uint64_t TranslationUnitNode::Size()
{
    return list.size();
}

SpecifierKind DeclarationSpecifierNode::Kind()
{
    return kind;
}
