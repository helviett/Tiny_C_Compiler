//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_DECLARATION_SPECIFIERS_H
#define TINY_C_COMPILER_DECLARATION_SPECIFIERS_H

#include "node.h"
#include "../token.h"
#include <list>

class TypeSpecifiers;
class TypeQualifierNode;

class DeclarationSpecifierNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override = 0;
};

class SimpleSpecifier: public DeclarationSpecifierNode
{
public:
    explicit SimpleSpecifier(Token *specifier): value(specifier) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
protected:
    Token *value;
};

class TypeSpecifierQualifierNode: public SimpleSpecifier
{
public:
    TypeSpecifierQualifierNode() = default;
    explicit TypeSpecifierQualifierNode(Token *value): SimpleSpecifier(value) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
};

class TypeSpecifierNode: public TypeSpecifierQualifierNode
{
public:
    explicit TypeSpecifierNode(Token *specifier): TypeSpecifierQualifierNode(specifier) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
};

class TypeQualifierNode: public TypeSpecifierQualifierNode
{
public:
    explicit TypeQualifierNode(Token *qualifier): TypeSpecifierQualifierNode(qualifier) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
};

class StorageClassSpecifierNode: public SimpleSpecifier
{
public:
    explicit StorageClassSpecifierNode(Token *specifier): SimpleSpecifier(specifier) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
};

class FunctionSpecifierNode: public SimpleSpecifier
{
public:
    explicit FunctionSpecifierNode(Token *specifier): SimpleSpecifier(specifier) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
};

//specifier-qualifier-list ::= type-specifier `specifier-qualifier-list
//| type-qualifier `specifier-qualifier-list

class SpecifierQualifierListNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(TypeSpecifierQualifierNode *typeSpecifierQualifier);
    uint64_t Size();
private:
    std::list<TypeSpecifierQualifierNode *> list;
};

//type-qualifier-list ::= type-qualifier | type-qualifier-list type-qualifier

class TypeQualifierListNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(TypeQualifierNode *typeSpecifierQualifier);
    uint64_t Size();
private:
    std::list<TypeQualifierNode *> list;
};

class DeclarationSpecifiersNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(DeclarationSpecifierNode *specifier);
    uint64_t Size();
private:
    std::list<DeclarationSpecifierNode *> list;
};


#endif //TINY_C_COMPILER_DECLARATION_SPECIFIERS_H
