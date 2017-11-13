//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_DECLS_H
#define TINY_C_COMPILER_DECLS_H

//direct-declarator ::= id | direct-declarator [constant-expr]
//                      | direct-declarator (parameter-type-list)

#include "node.h"
#include "pointer.h"
#include "expressions.h"

class DirectDeclaratorNode;

class DeclaratorNode: public Node
{
public:
    DeclaratorNode () = default;
    DeclaratorNode(PointerNode *pointer, DirectDeclaratorNode *directDeclarator):
            pointer(pointer), directDeclarator(directDeclarator) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    DirectDeclaratorNode *directDeclarator;
    PointerNode *pointer;
};

class DirectDeclaratorNode: public DeclaratorNode
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override = 0;
};

class ArrayDeclaratorNode: public DirectDeclaratorNode
{
public:
    ArrayDeclaratorNode(DirectDeclaratorNode *directDeclarator, ExprNode *size):
            directDeclarator(directDeclarator), size(size) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    DirectDeclaratorNode *directDeclarator;
    ExprNode  *size;
};

class ParameterTypeList;

class FunctionDeclaratorNode: public DirectDeclaratorNode
{
public:
    FunctionDeclaratorNode(DirectDeclaratorNode *directDeclarator, ParameterTypeList *params):
            params(params), directDeclarator(directDeclarator) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    DirectDeclaratorNode *directDeclarator;
    ParameterTypeList    *params;
};

//parameter-declaration ::= declaration-specifiers declarator | declaration-specifiers `abstract-declarator

class ParameterDeclarationNode: public Node
{
public:
    ParameterDeclarationNode(DeclarationSpecifiersNode *specifiers, DeclaratorNode *declarator):
            specifiers(specifiers), declarator(declarator) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    DeclarationSpecifiersNode *specifiers;
    DeclaratorNode *declarator;
};

//parameter-type-list ::= parameter-list | parameter-list , ...

class ParameterTypeList: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override = 0;
};

//parameter-list ::= parameter-declaration | parameter-list , parameter-declaration

class ParameterList: public ParameterTypeList
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(ParameterDeclarationNode *specifier);
    uint64_t Size();
protected:
    std::list<ParameterDeclarationNode *> list;
};

//declaration ::= declaration-specifiers `init-declarator-list ;
class InitDeclaratorListNode;

class DeclarationNode: public Node
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
