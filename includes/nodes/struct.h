//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_STRUCT_H
#define TINY_C_COMPILER_STRUCT_H

#include "node.h"
#include "decls.h"

class StructDeclaratorNode: public DeclaratorNode
{
public:
    StructDeclaratorNode(DeclaratorNode *declarator, ExprNode *constantExpr);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    ExprNode *constantExpr;
};

class StructDeclaratorListNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(StructDeclaratorNode *initDeclarator);
    uint64_t Size();
    std::list<StructDeclaratorNode *> &List();
protected:
    std::list<StructDeclaratorNode *> list;
};

class StructDeclarationNode: public Node
{
public:
    explicit StructDeclarationNode(StructDeclaratorListNode *structDeclaratorList):
            structDeclaratorList(structDeclaratorList) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    std::list<StructDeclaratorNode *>  &List() const;
private:
    StructDeclaratorListNode *structDeclaratorList;
};

class StructDeclarationListNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(StructDeclarationNode *initDeclarator);
    uint64_t Size();
    std::list<StructDeclarationNode *> &List();
protected:
    std::list<StructDeclarationNode *> list;
};

class StructSpecifierNode: public DeclarationSpecifierNode
{
public:
    explicit StructSpecifierNode(IdNode *id): id(id) { kind = SpecifierKind::COMPLEX; }
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void SetId(IdNode *id);
    IdNode *GetId() const;
    RecordType *GetRecordType() const;
    void SetRecordType(RecordType *type);
private:
    IdNode *id{nullptr};
    RecordType *type{nullptr};
};

#endif //TINY_C_COMPILER_STRUCT_H
