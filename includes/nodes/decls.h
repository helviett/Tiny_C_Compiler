//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_DECLS_H
#define TINY_C_COMPILER_DECLS_H

#include <symbols/sym_type.h>
#include "node.h"
#include "pointer.h"
#include "expressions.h"
#include "translation_unit.h"

class DirectDeclaratorNode;

class DeclaratorNode: public Node
{
public:
    DeclaratorNode () { type = nullptr; }
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void SetType(SymType *type);
    SymType *GetType() const;
    void SetId(IdNode *name);
    IdNode *GetId() const;
private:
    SymType *type;
    IdNode *id{nullptr};
};

class DirectDeclaratorNode: public DeclaratorNode
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override = 0;
};

class ParameterTypeList;

class ParameterDeclarationNode: public DeclaratorNode
{
public:
    ParameterDeclarationNode(DeclaratorNode *declarator);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
};

class ParameterTypeList: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override = 0;
};

class ParameterList: public ParameterTypeList
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(ParameterDeclarationNode *specifier);
    uint64_t Size();
    std::list<ParameterDeclarationNode *> &List();
protected:
    std::list<ParameterDeclarationNode *> list;
};

class InitDeclaratorListNode;

class DeclarationNode: public ExternalDeclarationNode
{
public:
    DeclarationNode(DeclarationSpecifiersNode *declarationSpecifiers, InitDeclaratorListNode *list):
            declarationSpecifiers(declarationSpecifiers), list(list) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    DeclarationSpecifiersNode *declarationSpecifiers;
    InitDeclaratorListNode    *list;
};


#endif //TINY_C_COMPILER_DECLS_H
