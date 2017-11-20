//
// Created by keltar on 11/13/17.
//

#ifndef TINY_C_COMPILER_TYPE_H
#define TINY_C_COMPILER_TYPE_H

#include <nodes/declaration_specifier_nodes.h>
#include <iostream>

enum class BuiltInTypeKind
{
    VOID, INT8, INT16, INT32, INT64, FLOAT, DOUBLE,
    UINT8, UINT16, UINT32, UINT64, NONE
};

enum class TypeKind
{
    ENUM, STRUCT, POINTER, BUILTIN, ARRAY, FUNCTION
};

enum class TypeQualifier
{
    CONST = 1, RESTRICT = 2, VOLATILE = 4
};

class Type
{
public:
    TypeKind GetTypeKind() const;
    void SetTypeKind(TypeKind typeKind);
    virtual void Print(std::ostream &os, std::string indent, bool isTail) = 0;
    ~Type() { std::cout << "I am fucking dead" << std::endl; }
protected:
    TypeKind kind;
};

class BuiltInType: public Type
{
public:
    explicit BuiltInType (BuiltInTypeKind builtInTypeKind);
    BuiltInTypeKind GetBuiltIntTypeKind() const;
    void SetBuiltIntTypeKind(BuiltInTypeKind typeKind);
    void Print(std::ostream &os, std::string indent, bool isTail) override;
    ~BuiltInType() { std::cout << "I am fucking dead" << std::endl; }
private:
    BuiltInTypeKind builtInTypeKind;
};

class RecordType: public Type
{
public:
private:
//    vector<Declaration *> decls;
//    SymbolTable fields;
};

class ExprNode;

class ArrayType: public Type
{
public:
    explicit ArrayType(Type **valueType, ExprNode *size);
    void Print(std::ostream &os, std::string indent, bool isTail) override;
    Type **GetValueType() const;
    void SetValueType(Type **valueType);
private:
    Type **valueType;
    ExprNode *size;
};

class FunctionType: public Type
{
public:
    explicit FunctionType(Type **returnType);
    void Print(std::ostream &os, std::string indent, bool isTail) override;
    Type **GetReturnType() const;
    void SetReturnType(Type **returnType);
private:
    Type **returnType;
    // TODO SymTable *params;
};

class PointerType: public Type
{
public:
    // double pointer mean that target of a pointer may be unconstructed yet e.g. in complex decls
    explicit PointerType(Type **target);
    void Print(std::ostream &os, std::string indent, bool isTail) override;
    Type **GetTarget() const;
    void SetTarget(Type **target);
private:
    Type **target;
    // TODO TypeQualifiers or so;
};

#endif //TINY_C_COMPILER_TYPE_H
