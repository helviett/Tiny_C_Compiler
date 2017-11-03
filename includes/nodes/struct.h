//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_STRUCT_H
#define TINY_C_COMPILER_STRUCT_H

#include "node.h"
#include "decls.h"

//struct-declarator ::= declarator | `declarator : constant-expr

class StructDeclaratorNode: public Node
{
public:
    StructDeclaratorNode(DeclaratorNode *declarator, ConstantExprNode *constantExpr):
            declarator(declarator), constantExpr(constantExpr) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    DeclaratorNode *declarator;
    ConstantExprNode *constantExpr;
};

//struct-declarator-list ::= struct-declarator | struct-declarator-list , struct-declarator

class StructDeclaratorListNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(StructDeclaratorNode *initDeclarator);
    uint64_t Size();
protected:
    std::list<StructDeclaratorNode *> list;
};

//struct-declaration ::= specifier-qualifier-list struct-declarator-list ;

class StructDeclarationNode: public Node
{
public:
    StructDeclarationNode(SpecifierQualifierListNode *specifierQualifierList,
                          StructDeclaratorListNode *structDeclaratorList):
            specifierQualifierList(specifierQualifierList), structDeclaratorList(structDeclaratorList){}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    SpecifierQualifierListNode *specifierQualifierList;
    StructDeclaratorListNode   *structDeclaratorList;
};

//struct-declaration-list ::= struct-declaration | struct-declaration-list struct declaration

class StructDeclarationListNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(StructDeclarationNode *initDeclarator);
    uint64_t Size();
protected:
    std::list<StructDeclarationNode *> list;
};

//struct-specifier ::= struct `id {struct-declaration-list}
//                     | struct id

class StructSpecifierNode: public DeclarationSpecifierNode
{
public:
    StructSpecifierNode(IdNode *id, StructDeclarationListNode *structDeclaratorList):
            id(id), structDeclaratorList(structDeclaratorList) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    IdNode *id;
    StructDeclarationListNode *structDeclaratorList;
};

#endif //TINY_C_COMPILER_STRUCT_H
