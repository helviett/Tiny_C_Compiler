//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_TYPE_NAME_CAST_H
#define TINY_C_COMPILER_TYPE_NAME_CAST_H

#include "node.h"
#include "declaration_specifier_nodes.h"
#include "decls.h"

class TypeCastNode: public ExprNode
{
public:
    TypeCastNode(SymType *typeName, ExprNode *castExpr);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    ExprNode * Eval(Evaluator *evaluator) override;
    void Generate(Asm::Assembly *assembly) override;
private:
    SymType *castType;
    ExprNode *castExpr;
};


#endif //TINY_C_COMPILER_TYPE_NAME_CAST_H
