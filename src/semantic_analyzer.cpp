
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

PostfixIncrementNode *SemanticAnalyzer::BuildPostfixDecrementNode(ExprNode *expr)
{
    CheckPostfixIncDecRules(expr);
    return nullptr;
}

PostfixIncrementNode *SemanticAnalyzer::BuildPostfixIncrementNode(ExprNode *node)
{
    return nullptr;
}

void SemanticAnalyzer::CheckPostfixIncDecRules(ExprNode *expr)
{
    static std::vector<TypeKind> improperKinds = {};
    if (expr->GetValueCategory() == ValueCategory::RVALUE) throw "";
    auto type = expr->GetType();
    if (!isArithmeticType(type) && !isPointerType(type)) throw "";
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
//    return bitk != BuiltInTypeKind::VOID;
    return false;
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
