//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_FUNCTION_DEFINITION_H
#define TINY_C_COMPILER_FUNCTION_DEFINITION_H

//function-definition ::= declaration-specifier declarator compound-statement

#include "node.h"
#include "declaration_specifier_nodes.h"
#include "decls.h"
#include "statements.h"

class FunctionDefinitionNode: public Node
{
public:
    FunctionDefinitionNode(DeclarationSpecifiersNode *declarationSpecifiers,
                           DeclaratorNode *declarator, CompoundStatement *compoundStatement):
            declarationSpecifiers{declarationSpecifiers}, declarator(declarator), compoundStatement(compoundStatement) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    DeclarationSpecifiersNode *declarationSpecifiers;
    DeclaratorNode *declarator;
    CompoundStatement *compoundStatement;
};

#endif //TINY_C_COMPILER_FUNCTION_DEFINITION_H
