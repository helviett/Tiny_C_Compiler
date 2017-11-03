//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_ENUM_H
#define TINY_C_COMPILER_ENUM_H

#include "node.h"
#include "expressions.h"
#include <list>

//enumerator ::= enumeration-constant, enumeration-constant = constant-expr

class EnumeratorNode: public Node
{
public:
    EnumeratorNode(IdNode *enumerationConstant, ConstantExprNode *value):
            enumerationConstant(enumerationConstant), value(value) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    IdNode *enumerationConstant;
    ConstantExprNode *value;
};

//enumerator-list ::= enumerator | enumerator-list , enumerator


class EnumeratorList: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(EnumeratorNode *initDeclarator);
    uint64_t Size();
protected:
    std::list<EnumeratorNode *> list;
};

//enum-specifier ::= enum `id {enumerator-list}
//                  | enum `id {enumerator-list , }
//                  | enum id

class EnumSpecifierNode: public Node
{
public:
    EnumSpecifierNode(IdNode *id, EnumeratorList *enumeratorList): id(id), enumeratorList(enumeratorList) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    IdNode *id;
    EnumeratorList *enumeratorList;
};

#endif //TINY_C_COMPILER_ENUM_H
