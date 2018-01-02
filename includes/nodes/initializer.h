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
    void Generate(Asm::Assembly *assembly) override;
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
    void Generate(Asm::Assembly *assembly) override;
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
    void SetValue(InitializerNode *value);
    void Generate(Asm::Assembly *assembly) override = 0;
protected:
    InitializerNode *value{nullptr};
};

class ArrayDesignator: public DesignatorNode
{
public:
    explicit ArrayDesignator(ExprNode *index);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    ExprNode *GetIndex() const;
    void Generate(Asm::Assembly *assembly) override;
private:
    ExprNode *index{};
};

class StructMemberDesignator: public DesignatorNode
{
public:
    explicit StructMemberDesignator(IdNode *id);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    IdNode *GetMemberId() const;
    void Generate(Asm::Assembly *assembly) override;
private:
    IdNode *id{nullptr};
};

class DesignatorListNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(DesignatorNode *designator);
    uint64_t Size();
    std::list<DesignatorNode *> &List();
    void Generate(Asm::Assembly *assembly) override;
protected:
    std::list<DesignatorNode *> list;
};

class DesignationNode: public Node
{
public:
    explicit DesignationNode(DesignatorListNode *designatorList);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    std::list<DesignatorNode *> &List();
    void Generate(Asm::Assembly *assembly) override;
private:
    DesignatorListNode *designatorList;
};

class DesignatedInitializerNode: public InitializerNode
{
public:
    DesignatedInitializerNode(DesignationNode *designation, InitializerNode *initializer);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    DesignationNode *GetDesignation() const;
    InitializerNode *GetInitializer() const;
    void Generate(Asm::Assembly *assembly) override;
private:
    DesignationNode *designation;
    InitializerNode *initializer;
};

class InitializerListNode: public InitializerNode
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(InitializerNode *initializer);
    uint64_t Size();
    std::list<InitializerNode *> &List();
    void Generate(Asm::Assembly *assembly) override;
protected:
    std::list<InitializerNode *> list;
};

class SimpleInitializer: public InitializerNode
{
public:
    explicit SimpleInitializer(ExprNode *expr);
    void Print(std::ostream &os, std::string indent, bool isTail) override;
    ExprNode *GetValue() const;
    void SetValue(ExprNode *value);
    void Generate(Asm::Assembly *assembly) override;
private:
    ExprNode *value;
};

#endif //TINY_C_COMPILER_INITIALIZER_H
