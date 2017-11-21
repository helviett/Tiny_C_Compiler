//
// Created by keltar on 11/13/17.
//

#ifndef TINY_C_COMPILER_TYPE_H
#define TINY_C_COMPILER_TYPE_H

#include <nodes/declaration_specifier_nodes.h>
#include <nodes/expressions.h>
#include <iostream>
#include "symbol.h"
#include <unordered_map>
#include <vector>

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

static std::unordered_map<BuiltInTypeKind, std::string> BuiltInTypeKindToString
{
        {BuiltInTypeKind::VOID, "VOID"},     {BuiltInTypeKind::INT8, "INT8"},
        {BuiltInTypeKind::UINT8, "UINT8"},   {BuiltInTypeKind::INT32, "INT32"},
        {BuiltInTypeKind::UINT32, "UINT32"}, {BuiltInTypeKind::INT64, "INT64"},
        {BuiltInTypeKind::UINT64, "UINT64"}, {BuiltInTypeKind::FLOAT, "FLOAT"},
        {BuiltInTypeKind::DOUBLE, "DOUBLE"}, {BuiltInTypeKind::INT16, "INT16"},
        {BuiltInTypeKind::UINT16, "INT16"}
};

class SymType: public Symbol
{
public:
    TypeKind GetTypeKind() const;
    void SetTypeKind(TypeKind typeKind);
    virtual void Print(std::ostream &os, std::string indent, bool isTail) = 0;
protected:
    TypeKind kind;
};

class SymBuiltInType: public SymType
{
public:
    explicit SymBuiltInType (BuiltInTypeKind builtInTypeKind);
    BuiltInTypeKind GetBuiltIntTypeKind() const;
    void SetBuiltIntTypeKind(BuiltInTypeKind typeKind);
    void Print(std::ostream &os, std::string indent, bool isTail) override;
private:
    BuiltInTypeKind builtInTypeKind;
};

class RecordType: public SymType
{
public:
private:
//    vector<Declaration *> decls;
//    SymbolTable fields;
};

class ExprNode;

class SymArray: public SymType
{
public:
    explicit SymArray(SymType *valueType, ExprNode *size);
    void Print(std::ostream &os, std::string indent, bool isTail) override;
    SymType *GetValueType() const;
    void SetValueType(SymType *valueType);
private:
    SymType *valueType;
    ExprNode *size;
};

class SymbolTable;

class SymFunction: public SymType
{
public:
    explicit SymFunction(SymType *returnType);
    SymFunction(SymType *returnType, SymbolTable *params, const std::vector<std::string> &orderedParamTypes);
    SymFunction(SymType *returnType, SymbolTable *params,  const std::vector<std::string> &orderedParamTypes,
                SymbolTable *body);
    void Print(std::ostream &os, std::string indent, bool isTail) override;
    SymType *GetReturnType() const;
    void SetReturnType(SymType *returnType);
private:
    SymType *returnType{nullptr};
    SymbolTable *params{nullptr}, *body{nullptr};
    std::vector<std::string> orderedParamNames;
};

class PointerType: public SymType
{
public:
    explicit PointerType(SymType *target);
    void Print(std::ostream &os, std::string indent, bool isTail) override;
    SymType *GetTarget() const;
    void SetTarget(SymType *target);
private:
    SymType *target;
    // TODO TypeQualifiers or so;
};

class SymAlias: public SymType
{
public:
    SymAlias(std::string name, SymType *type);
private:
    SymType *type;
};

#endif //TINY_C_COMPILER_TYPE_H
