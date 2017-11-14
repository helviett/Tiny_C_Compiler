//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_STRUCT_H
#define TINY_C_COMPILER_STRUCT_H

#include "node.h"
#include "decls.h"

class StructDeclaratorNode: public Node
{
public:
    StructDeclaratorNode(DeclaratorNode *declarator, ExprNode *constantExpr):
            declarator(declarator), constantExpr(constantExpr) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    DeclaratorNode *declarator;
    ExprNode *constantExpr;
};

class StructDeclaratorListNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(StructDeclaratorNode *initDeclarator);
    uint64_t Size();
protected:
    std::list<StructDeclaratorNode *> list;
};

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

class StructDeclarationListNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(StructDeclarationNode *initDeclarator);
    uint64_t Size();
protected:
    std::list<StructDeclarationNode *> list;
};

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
