//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_DECLARATION_SPECIFIERS_NODES_H
#define TINY_C_COMPILER_DECLARATION_SPECIFIERS_NODES_H

#include "node.h"
#include "../token.h"
#include <list>

enum class SpecifierKind
{
    SIMPLE, COMPLEX
};

class TypeSpecifiers;
class TypeQualifierNode;

class DeclarationSpecifierNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override = 0;
    SpecifierKind Kind();
protected:
    SpecifierKind kind;
};

class SimpleSpecifier: public DeclarationSpecifierNode
{
public:
    explicit SimpleSpecifier(std::shared_ptr<Token> specifier): value(specifier) { kind = SpecifierKind::SIMPLE; }
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    std::shared_ptr<Token> Value();
protected:
    std::shared_ptr<Token> value;
};

class TypeSpecifierQualifierNode: public SimpleSpecifier
{
public:
    TypeSpecifierQualifierNode() = default;
    explicit TypeSpecifierQualifierNode(std::shared_ptr<Token> value): SimpleSpecifier(value) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
};

class TypeSpecifierNode: public TypeSpecifierQualifierNode
{
public:
    explicit TypeSpecifierNode(std::shared_ptr<Token> specifier): TypeSpecifierQualifierNode(specifier) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
};

class TypeQualifierNode: public TypeSpecifierQualifierNode
{
public:
    explicit TypeQualifierNode(std::shared_ptr<Token> qualifier): TypeSpecifierQualifierNode(qualifier) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
};

class StorageClassSpecifierNode: public SimpleSpecifier
{
public:
    explicit StorageClassSpecifierNode(std::shared_ptr<Token> specifier): SimpleSpecifier(specifier) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
};

class FunctionSpecifierNode: public SimpleSpecifier
{
public:
    explicit FunctionSpecifierNode(std::shared_ptr<Token> specifier): SimpleSpecifier(specifier) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
};

class SpecifierQualifierListNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(TypeSpecifierQualifierNode *typeSpecifierQualifier);
    uint64_t Size();
private:
    std::list<TypeSpecifierQualifierNode *> list;
};

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
    DeclarationSpecifiersNode() = default;
    DeclarationSpecifiersNode(std::initializer_list<DeclarationSpecifierNode *> initializerList);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(DeclarationSpecifierNode *specifier);
    std::list<DeclarationSpecifierNode *> &List();
    uint64_t Size();
private:
    std::list<DeclarationSpecifierNode *> list;
};


#endif //TINY_C_COMPILER_DECLARATION_SPECIFIERS_NODES_H
