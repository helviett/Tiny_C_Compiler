//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_TYPE_NAME_CAST_H
#define TINY_C_COMPILER_TYPE_NAME_CAST_H

#include "node.h"
#include "declaration_specifier_nodes.h"
#include "decls.h"

class TypeNameNode: public Node
{
public:
    TypeNameNode(DeclarationSpecifiersNode *specifierQualifierList, DeclaratorNode *abstractDeclarator):
            specifierQualifierList(specifierQualifierList), abstractDeclarator(abstractDeclarator) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    DeclarationSpecifiersNode *specifierQualifierList;
    DeclaratorNode *abstractDeclarator;
};

class TypeCastNode: public ExprNode
{
public:
    TypeCastNode(TypeNameNode *typeName, ExprNode *castExpr): typeName(typeName), castExpr(castExpr) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    TypeNameNode *typeName;
    ExprNode *castExpr;
};


#endif //TINY_C_COMPILER_TYPE_NAME_CAST_H
