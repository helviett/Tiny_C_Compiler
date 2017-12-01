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
    type = new SymBuiltInType(BuiltInTypeKind::INT32, 0);
}

void FloatConstNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << token->floatValue << std::endl;
}

FloatConstNode::FloatConstNode(std::shared_ptr<Token> token): ConstNode(token)
{
    if (token->type != TokenType::NUM_FLOAT) throw "";
    type = new SymBuiltInType(BuiltInTypeKind::FLOAT, 0);
}

void IdNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << token->text << std::endl;
}

IdNode::IdNode(std::shared_ptr<Token> token): token(token)
{
    if (token->type != TokenType::ID) throw "";
    category = ValueCategory::LVAVLUE;
}

std::string IdNode::GetName() const
{
    return token->stringValue;
}

IdNode::IdNode(std::shared_ptr<Token> token, SymType *type): IdNode(token)
{
    this->type = type;
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

PostfixIncrementNode::PostfixIncrementNode(ExprNode *node) : node(node) {}

void PostfixDecrementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "`--" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    node->Print(os, indent, true);
}

PostfixDecrementNode::PostfixDecrementNode(ExprNode *node) : node(node) {}

void StructureOrUnionMemberAccessNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "." << std::endl;
    indent.append(isTail ? "    " : "│   ");
    structureOrUnion->Print(os, indent, false);
    member->Print(os, indent, true);
}

StructureOrUnionMemberAccessNode::StructureOrUnionMemberAccessNode(ExprNode *structureOrUnion, IdNode *member) : member(member),
                                                                                                                 structureOrUnion(structureOrUnion) {}

void StructureOrUnionMemberAccessByPointerNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "->" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    structureOrUnion->Print(os, indent, false);
    member->Print(os, indent, true);
}

StructureOrUnionMemberAccessByPointerNode::StructureOrUnionMemberAccessByPointerNode(ExprNode *structureOrUnion,
                                                                                     IdNode *member) : member(member),
                                                                                                       structureOrUnion(structureOrUnion) {}

void PrefixIncrementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "++'" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    node->Print(os, indent, true);
}

PrefixIncrementNode::PrefixIncrementNode(ExprNode *node) : node(node){}

void PrefixDecrementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "--`" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    node->Print(os, indent, true);
}

PrefixDecrementNode::PrefixDecrementNode(ExprNode *node) : node(node){}

void BinOpNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << op->text << std::endl;
    indent.append(isTail ? "    " : "│   ");
    left->Print(os, indent, false);
    right->Print(os, indent, true);
}

BinOpNode::BinOpNode(ExprNode *left, ExprNode *right, std::shared_ptr<Token> op) : left(left), right(right), op(op)
{
    this->type = left->GetType();
}

BinOpNode::BinOpNode(ExprNode *left, ExprNode *right, std::shared_ptr<Token> op, SymType *resultType):
        BinOpNode(left, right, op)
{
    this->type = resultType;
}

void ArrayAccessNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "[]" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    left->Print(os, indent, false);
    inBrackets->Print(os, indent, true);
}

ArrayAccessNode::ArrayAccessNode(ExprNode *left, ExprNode *inBrackets) : left(left), inBrackets(inBrackets) {}

void TernaryOperatorNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "?:" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    condition->Print(os, indent, false);
    iftrue->Print(os, indent, false);
    iffalse->Print(os, indent, true);
}

TernaryOperatorNode::TernaryOperatorNode(ExprNode *condition, ExprNode *iftrue, ExprNode *iffalse) :
        condition(condition), iftrue(iftrue), iffalse(iffalse)
{
    this->type = iftrue->GetType();
}


void AssignmentNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << assignmentOp->stringValue << std::endl;
    indent.append(isTail ? "    " : "│   ");
    left->Print(os, indent, false);
    right->Print(os, indent, true);
}

AssignmentNode::AssignmentNode(ExprNode *left, ExprNode *right, std::shared_ptr<Token> assignmentOp) : left(left), right(right),
                                                                                                       assignmentOp(assignmentOp) {}

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

UnaryOpNode::UnaryOpNode(std::shared_ptr<Token> unaryOp, ExprNode *expr) : unaryOp(unaryOp), expr(expr) {}

void SizeofExprNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "sizeof" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    expr->Print(os, indent, true);
}

SizeofExprNode::SizeofExprNode(ExprNode *expr) : expr(expr) {}

void SizeofTypeNameNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "sizeof()" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    typeName->Print(os, indent, true);
}

SizeofTypeNameNode::SizeofTypeNameNode(TypeNameNode *typeName) : typeName(typeName) {}

void CommaSeparatedExprs::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "," << std::endl;
    indent.append(isTail ? "    " : "│   ");
    left->Print(os, indent, false);
    right->Print(os, indent, true);
}

CommaSeparatedExprs::CommaSeparatedExprs(ExprNode *left, ExprNode *right) : left(left), right(right) {}

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

void ArgumentExprListNode::Add(ExprNode *assignmentExpr)
{
    list.push_back(assignmentExpr);
}

uint64_t ArgumentExprListNode::Size()
{
    return list.size();
}

std::list<ExprNode *> &ArgumentExprListNode::List()
{
    return list;
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

FunctionCallNode::FunctionCallNode(ExprNode *functionName, ArgumentExprListNode *arguments) :
        functionName(functionName), arguments(arguments) {}

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

std::list<InitDeclaratorNode *> &InitDeclaratorListNode::List()
{
    return list;
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

TypeSpecifierQualifierNode::TypeSpecifierQualifierNode(std::shared_ptr<Token> value) : SimpleSpecifier(value) {}

void TypeSpecifierNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << value->text << std::endl;
}

TypeSpecifierNode::TypeSpecifierNode(std::shared_ptr<Token> specifier) : TypeSpecifierQualifierNode(specifier) {}

void TypeQualifierNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << value->text << std::endl;
}

TypeQualifierNode::TypeQualifierNode(std::shared_ptr<Token> qualifier) : TypeSpecifierQualifierNode(qualifier) {}

void StorageClassSpecifierNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << value->text << std::endl;
}

StorageClassSpecifierNode::StorageClassSpecifierNode(std::shared_ptr<Token> specifier) : SimpleSpecifier(specifier) {}

void FunctionSpecifierNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << value->text << std::endl;
}

FunctionSpecifierNode::FunctionSpecifierNode(std::shared_ptr<Token> specifier) : SimpleSpecifier(specifier) {}

void SimpleSpecifier::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << value->text << std::endl;
}

std::shared_ptr<Token> SimpleSpecifier::Value()
{
    return value;
}

SimpleSpecifier::SimpleSpecifier(std::shared_ptr<Token> specifier) : value(specifier) { kind = SpecifierKind::SIMPLE; }

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

std::list<StructDeclaratorNode *> &StructDeclaratorListNode::List()
{
    return list;
}

void StructDeclarationNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "StructDeclaratorList" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    structDeclaratorList->Print(os, indent, true);
}

std::list<StructDeclaratorNode *> & StructDeclarationNode::List() const
{
    return structDeclaratorList->List();
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

std::list<StructDeclarationNode *> &StructDeclarationListNode::List()
{
    return list;
}

void StructSpecifierNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "struct" << std::endl;
    indent.append(isTail ? "    " : "│   ");
}

void StructSpecifierNode::SetId(IdNode *id)
{
    this->type->SetTag(id);
}

IdNode *StructSpecifierNode::GetId() const
{
    return this->type->GetTag();
}

SymRecord *StructSpecifierNode::GetRecordType() const
{
    return type;
}

void StructSpecifierNode::SetRecordType(SymRecord *type)
{
    this->type = type;
}

StructSpecifierNode::StructSpecifierNode(SymRecord *type) : type(type) { kind = SpecifierKind::COMPLEX; }

void StructDeclaratorNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "StructDeclarator" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (GetId()) GetId()->Print(os, indent, false);
    GetType()->Print(os, indent, constantExpr);
    if (constantExpr) constantExpr->Print(os, indent, true);
}

StructDeclaratorNode::StructDeclaratorNode(DeclaratorNode *declarator, ExprNode *constantExpr): constantExpr(constantExpr)
{
    SetId(declarator->GetId());
    SetType(declarator->GetType());
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

SymType *ExprNode::GetType() const
{
    return type;
}

void ExprNode::SetType(SymType *type)
{
    this->type = type;
}

void ExprNode::SetValueCategory(ValueCategory category)
{
    this->category = category;
}

ValueCategory ExprNode::GetValueCategory() const
{
    return category;
}

ConstNode::ConstNode(std::shared_ptr<Token> token) : token(std::move(token)) {}
