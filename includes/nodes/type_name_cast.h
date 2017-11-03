//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_TYPE_NAME_CAST_H
#define TINY_C_COMPILER_TYPE_NAME_CAST_H

#include "node.h"
#include "declaration_specifiers.h"
#include "decls.h"

class TypeNameNode: public Node
{
public:
    TypeNameNode(SpecifierQualifierListNode *specifierQualifierList, DeclaratorNode *abstractDeclarator):
            specifierQualifierList(specifierQualifierList), abstractDeclarator(abstractDeclarator) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    SpecifierQualifierListNode *specifierQualifierList;
    DeclaratorNode *abstractDeclarator;
};

class TypeCastNode: public CastExprNode
{
public:
    TypeCastNode(TypeNameNode *typeName, PostfixExprNode *castExpr): typeName(typeName), castExpr(castExpr) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    TypeNameNode *typeName;
    PostfixExprNode *castExpr;
};


#endif //TINY_C_COMPILER_TYPE_NAME_CAST_H
