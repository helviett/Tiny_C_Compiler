
#include "../includes/semantic_analyzer.h"

IdNode *SemanticAnalyzer::BuildIdNode(std::shared_ptr<Token> token)
{
    auto symbol = scopeTree.Find(token->stringValue);
    if (!symbol) throw "";
    if (symbol->GetSymbolClass() == SymbolClass::UNDEFINED) throw "";
    if (symbol->GetSymbolClass() == SymbolClass::VARIABLE)
    {

        auto id = new IdNode(token, ((SymVariable *)symbol)->GetType());
        switch (id->GetType()->GetTypeKind())
        {
            case TypeKind::ARRAY: case TypeKind::FUNCTION :case TypeKind::STRUCT:
                id->SetValueCategory(ValueCategory::RVALUE);
                break;
            default:
                id->SetValueCategory(ValueCategory::LVAVLUE);
        }
        return id;
    }
    throw "";
}

StructSpecifierNode *SemanticAnalyzer::BuildStructSpecifierNode(IdNode *tag,
                                                                StructDeclarationListNode *structDeclarationList)
{
    auto rt = TypeBuilder::Build(structDeclarationList, tag);
    rt->SetTag(tag);
    Symbol *s = nullptr;
    if (tag)
    {
        s = scopeTree.GetActiveScope()->Find("struct " + tag->GetName());
        if (s)
        {
            if (s->GetSymbolClass() != SymbolClass::TYPE) throw "";
            if (((SymType *)s)->GetTypeKind() != TypeKind::STRUCT) throw "";
            auto record = (SymRecord *)s;
            if (!record->GetOrderedFields().empty()) throw "";
            delete record;
        }
        rt->SetName("struct " + tag->GetName());
        scopeTree.GetActiveScope()->Insert(rt->GetName(), rt);
    }
    return new StructSpecifierNode(rt);
}

ScopeTree *SemanticAnalyzer::GetScopeTree()
{
    return &scopeTree;
}

PostfixDecrementNode *SemanticAnalyzer::BuildPostfixDecrementNode(ExprNode *expr)
{
    CheckPostfixIncDecRules(expr);
    return new PostfixDecrementNode(expr);
}

PostfixIncrementNode *SemanticAnalyzer::BuildPostfixIncrementNode(ExprNode *expr)
{
    CheckPostfixIncDecRules(expr);
    return new PostfixIncrementNode(expr);
}

void SemanticAnalyzer::CheckPostfixIncDecRules(ExprNode *expr)
{
    static std::vector<TypeKind> improperKinds = {};
    if (expr->GetValueCategory() == ValueCategory::RVALUE) throw "";
    auto type = expr->GetType();
    if (!isArithmeticType(type) && !isPointerType(type) || isVoidPointer(type)) throw "";
}

bool SemanticAnalyzer::isArithmeticType(SymType *type)
{
    if (type->GetTypeKind() != TypeKind::BUILTIN) return false;
    auto bitk = ((SymBuiltInType *)type)->GetBuiltIntTypeKind();
    return bitk != BuiltInTypeKind::VOID;
}

bool SemanticAnalyzer::isPointerType(SymType *type)
{
    if (type->GetTypeKind() != TypeKind::POINTER) return false;
    auto bitk = ((SymPointer *)type)->GetTarget();
    return true;
}

InitDeclaratorNode *SemanticAnalyzer::BuildInitDeclaratorNode(DeclaratorNode *declarator, InitializerNode *initializer)
{
    if (scopeTree.GetActiveScope()->Find(declarator->GetId()->GetName())) throw "";
    auto t = declarator->GetType();
    if (t->GetTypeKind() == TypeKind::FUNCTION)
        scopeTree.GetActiveScope()->Insert(declarator->GetId()->GetName(), t);
    else
        scopeTree.GetActiveScope()->Insert(declarator->GetId()->GetName(),
                                           new SymVariable(declarator->GetId()->GetName(), declarator->GetType()));
    // TODO initializer type check
    return new InitDeclaratorNode(declarator, initializer);
}

bool SemanticAnalyzer::isVoidPointer(SymType *type)
{
    if (type->GetTypeKind() != TypeKind::POINTER) return false;
    auto target = ((SymPointer *)type)->GetTarget();
    return target->GetTypeKind() == TypeKind::BUILTIN &&
            ((SymBuiltInType *)target)->GetBuiltIntTypeKind() == BuiltInTypeKind::VOID;
}

StructureOrUnionMemberAccessNode *
SemanticAnalyzer::BuildStructureOrUnionMemberAccessNode(ExprNode *structure, IdNode *field)
{
    auto type = structure->GetType();
    if (type->GetTypeKind() != TypeKind::STRUCT) throw "";
    auto stype = (SymRecord *)type;
    SymVariable *sfield;
    if (!(sfield = (SymVariable *)stype->GetFieldsTable()->Find(field->GetName()))) throw "";
    auto res = new StructureOrUnionMemberAccessNode(structure, field);
    res->SetType(sfield->GetType());
    res->SetValueCategory(structure->GetValueCategory());
    return res;
}

StructureOrUnionMemberAccessByPointerNode *
SemanticAnalyzer::BuildStructureOrUnionMemberAccessByPointerNode(ExprNode *ptr, IdNode *field)
{
    if (ptr->GetType()->GetTypeKind() == TypeKind::ARRAY)
    {
        auto newt = ((SymArray *)ptr->GetType())->ToPointer();
        delete ptr->GetType();
        ptr->SetType(newt);
    }
    if (!isPointerType(ptr->GetType())) throw "";
    auto ptype = (SymPointer *)ptr->GetType();
    if (ptype->GetTarget()->GetTypeKind() != TypeKind::STRUCT) throw "";
    auto stype = (SymRecord *)ptype->GetTarget();
    SymVariable *sfield;
    if (!(sfield = (SymVariable *)stype->GetFieldsTable()->Find(field->GetName()))) throw "";
    auto res = new StructureOrUnionMemberAccessByPointerNode(ptr, field);
    res->SetValueCategory(ValueCategory::LVAVLUE);
    auto rest = sfield->GetType();
    rest->SetTypeQualifiers(rest->GetTypeQualifiers() | stype->GetTypeQualifiers());
    res->SetType(sfield->GetType());
    return res;
}
