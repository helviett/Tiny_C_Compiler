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
    DeclaratorNode ();
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void SetType(SymType *type);
    SymType *GetType() const;
    void SetId(IdNode *name);
    IdNode *GetId() const;
    void Generate(Asm::Assembly *assembly) override;
private:
    SymType *type;
    IdNode *id{nullptr};
};

class DirectDeclaratorNode: public DeclaratorNode
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override = 0;
    void Generate(Asm::Assembly *assembly) override = 0;
};

class ParameterTypeList;

class ParameterDeclarationNode: public DeclaratorNode
{
public:
    explicit ParameterDeclarationNode(DeclaratorNode *declarator);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Generate(Asm::Assembly *assembly) override;
private:
};

class ParameterTypeList: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override = 0;
    void Generate(Asm::Assembly *assembly) override = 0;
};

class ParameterList: public ParameterTypeList
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(ParameterDeclarationNode *specifier);
    uint64_t Size();
    std::list<ParameterDeclarationNode *> &List();
    void Generate(Asm::Assembly *assembly) override;
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
    void Generate(Asm::Assembly *assembly) override;
private:
    DeclarationSpecifiersNode *declarationSpecifiers;
    InitDeclaratorListNode    *list;
};


#endif //TINY_C_COMPILER_DECLS_H
