
#include "../includes/semantic_analyzer.h"

IdNode *SemanticAnalyzer::BuildIdNode(std::shared_ptr<Token> token, Symbol *symbol)
{
    if (!symbol) throw "";
    if (symbol->GetSymbolClass() == SymbolClass::UNDEFINED) throw "";
    if (symbol->GetSymbolClass() == SymbolClass::VARIABLE) return new IdNode(token, ((SymVariable *)symbol)->GetType());
    throw "";
    return nullptr;
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
