#include "../includes/semantic_analyzer.h"

IdNode *SemanticAnalyzer::BuildIdNode(std::shared_ptr<Token> token, Symbol *symbol)
{
    if (!symbol) return nullptr;
    if (symbol->GetSymbolClass() == SymbolClass::UNDEFINED) throw "";
    if (symbol->GetSymbolClass() == SymbolClass::VARIABLE) return new IdNode(token, ((SymVariable *)symbol)->GetType());
    return nullptr;
}
