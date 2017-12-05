//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_INITIALIZER_H
#define TINY_C_COMPILER_INITIALIZER_H

#include "node.h"
#include "decls.h"

class InitializerNode;

class InitDeclaratorNode: public DeclaratorNode
{
public:
    InitDeclaratorNode(DeclaratorNode *declarator, InitializerNode *initializer);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    InitializerNode *GetInitializer() const;
private:
    InitializerNode *initializer;
};

class InitDeclaratorListNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(InitDeclaratorNode *initDeclarator);
    std::list<InitDeclaratorNode *> &List();
    uint64_t Size();
protected:
    std::list<InitDeclaratorNode *> list;
};

class InitializerNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override = 0;
};

class DesignatorNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override = 0;
};

class ArrayDesignator: public DesignatorNode
{
public:
    explicit ArrayDesignator(ExprNode *constantExpr): constantExpr(constantExpr) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    ExprNode *constantExpr;
};

class StructMemberDesignator: public DesignatorNode
{
public:
    explicit StructMemberDesignator(IdNode *id): id(id) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    IdNode *id;
};

class DesignatorListNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(DesignatorNode *designator);
    uint64_t Size();
protected:
    std::list<DesignatorNode *> list;
};

class DesignationNode: public Node
{
public:
    DesignationNode(DesignatorListNode *designatorList): designatorList(designatorList) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    DesignatorListNode *designatorList;
};

class DesignatedInitializerNode: public Node
{
public:
    DesignatedInitializerNode(DesignationNode *designation, InitializerNode *initializer):
            designation(designation), initializer(initializer) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    DesignationNode *designation;
    InitializerNode *initializer;
};

class InitializerListNode: public InitializerNode
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(DesignatedInitializerNode *initializer);
    uint64_t Size();
protected:
    std::list<DesignatedInitializerNode *> list;
};

class SimpleInitializer: public InitializerNode
{
public:
    explicit SimpleInitializer(ExprNode *expr);
    void Print(std::ostream &os, std::string indent, bool isTail) override;
    ExprNode *GetValue() const;
    void SetValue(ExprNode *value);
private:
    ExprNode *value;
};

#endif //TINY_C_COMPILER_INITIALIZER_H
