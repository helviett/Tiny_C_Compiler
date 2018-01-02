//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_DECLARATION_SPECIFIERS_NODES_H
#define TINY_C_COMPILER_DECLARATION_SPECIFIERS_NODES_H

#include "node.h"
#include "../token.h"
#include <list>
#include <symbols.h>

enum class SpecifierKind
{
    SIMPLE, STRUCT, ENUM, TYPEDEF
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
    explicit SimpleSpecifier(std::shared_ptr<Token> specifier);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    std::shared_ptr<Token> Value();
    void Generate(Asm::Assembly *assembly) override;
protected:
    std::shared_ptr<Token> value;
};

class TypeSpecifierQualifierNode: public SimpleSpecifier
{
public:
    TypeSpecifierQualifierNode() = default;
    explicit TypeSpecifierQualifierNode(std::shared_ptr<Token> value);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Generate(Asm::Assembly *assembly) override;
};

class TypeSpecifierNode: public TypeSpecifierQualifierNode
{
public:
    explicit TypeSpecifierNode(std::shared_ptr<Token> specifier);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Generate(Asm::Assembly *assembly) override;
};

class TypeQualifierNode: public TypeSpecifierQualifierNode
{
public:
    explicit TypeQualifierNode(std::shared_ptr<Token> qualifier);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Generate(Asm::Assembly *assembly) override;
};

class StorageClassSpecifierNode: public SimpleSpecifier
{
public:
    explicit StorageClassSpecifierNode(std::shared_ptr<Token> specifier);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Generate(Asm::Assembly *assembly) override;
};

class FunctionSpecifierNode: public SimpleSpecifier
{
public:
    explicit FunctionSpecifierNode(std::shared_ptr<Token> specifier);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Generate(Asm::Assembly *assembly) override;
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
    void Generate(Asm::Assembly *assembly) override;
private:
    std::list<DeclarationSpecifierNode *> list;
};

class SymAlias;

class TypedefIdentifierNode: public DeclarationSpecifierNode
{
public:
    TypedefIdentifierNode() = default;
    TypedefIdentifierNode(SymAlias *alias);
    void Print(std::ostream &os, std::string indent, bool isTail) override;
    std::shared_ptr<Token> GetToken();
    SymAlias *GetAlias() const;
    void Generate(Asm::Assembly *assembly) override;
private:
    SymAlias *alias{nullptr};
    std::shared_ptr<Token> id;
};

#endif //TINY_C_COMPILER_DECLARATION_SPECIFIERS_NODES_H
