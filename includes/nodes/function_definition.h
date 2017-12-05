//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_FUNCTION_DEFINITION_H
#define TINY_C_COMPILER_FUNCTION_DEFINITION_H

#include "node.h"
#include "declaration_specifier_nodes.h"
#include "decls.h"
#include "statements.h"

class ExternalDeclarationNode;

class FunctionDefinitionNode: public ExternalDeclarationNode
{
public:
    FunctionDefinitionNode(DeclaratorNode *declarator, CompoundStatement *compoundStatement):
            declarator(declarator), body(compoundStatement) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void SetBody(CompoundStatement *body);
    SymType *GetType() const;
private:
    DeclaratorNode *declarator;
    CompoundStatement *body;
};

#endif //TINY_C_COMPILER_FUNCTION_DEFINITION_H
