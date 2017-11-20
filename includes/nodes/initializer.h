//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_INITIALIZER_H
#define TINY_C_COMPILER_INITIALIZER_H

#include "node.h"
#include "decls.h"

class InitializerNode;

class InitDeclaratorNode: public Node
{
public:
    InitDeclaratorNode(DeclaratorNode *declarator, InitializerNode *initializer):
            declarator(declarator), initializer(initializer) {
        auto decl = this->declarator;
        auto decl1 = decl;
    }
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    DeclaratorNode *declarator;
    InitializerNode *initializer;
};

class InitDeclaratorListNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(InitDeclaratorNode *initDeclarator);
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

class InitializerListNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(DesignatedInitializerNode *initializer);
    uint64_t Size();
protected:
    std::list<DesignatedInitializerNode *> list;
};

#endif //TINY_C_COMPILER_INITIALIZER_H
