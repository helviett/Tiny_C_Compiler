//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_ENUM_H
#define TINY_C_COMPILER_ENUM_H

#include "node.h"
#include "expressions.h"
#include <list>

class EnumeratorNode: public ExprNode
{
public:
    EnumeratorNode(IdNode *enumerationConstant, ExprNode *value);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    ExprNode *GetValue() const;
    void SetValue(ExprNode *);
    IdNode *GetId();
    ExprNode * Eval(Evaluator *evaluator) override;
private:
    IdNode *enumerationConstant;
    ExprNode *value;
};

class EnumeratorList: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(EnumeratorNode *initDeclarator);
    uint64_t Size();
    std::list<EnumeratorNode *> &List();
protected:
    std::list<EnumeratorNode *> list;
};

class EnumSpecifierNode: public DeclarationSpecifierNode
{
public:
    EnumSpecifierNode(IdNode *id, EnumeratorList *enumeratorList): id(id), enumeratorList(enumeratorList) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    IdNode *id;
    EnumeratorList *enumeratorList;
};

#endif //TINY_C_COMPILER_ENUM_H
