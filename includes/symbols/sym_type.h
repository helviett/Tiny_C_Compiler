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
#include <symbols.h>

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
    virtual bool Equal(SymType *other) = 0;
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
    bool Equal(SymType *other) override;
private:
    BuiltInTypeKind builtInTypeKind;
};

class ExprNode;

class SymArray: public SymType
{
public:
    explicit SymArray(SymType *valueType, ExprNode *size);
    void Print(std::ostream &os, std::string indent, bool isTail) override;
    SymType *GetValueType() const;
    void SetValueType(SymType *valueType);
    bool Equal(SymType *other) override;
private:
    SymType *valueType;
    ExprNode *size;
};

class SymbolTable;
class SymVariable;

class SymFunction: public SymType
{
public:
    explicit SymFunction(SymType *returnType);
    SymFunction(SymType *returnType, SymbolTable *params, const std::vector<SymVariable *> &orderedParamTypes);
    SymFunction(SymType *returnType, SymbolTable *params,  const std::vector<SymVariable *> &orderedParamTypes,
                SymbolTable *body);
    void Print(std::ostream &os, std::string indent, bool isTail) override;
    SymType *GetReturnType() const;
    void SetReturnType(SymType *returnType);
    SymbolTable *GetParamsTable() const;
    bool Equal(SymType *other) override;
private:
    SymType *returnType{nullptr};
    SymbolTable *params{nullptr}, *body{nullptr};
    std::vector<SymVariable *> orderedParams;
};

class SymPointer: public SymType
{
public:
    explicit SymPointer(SymType *target);
    void Print(std::ostream &os, std::string indent, bool isTail) override;
    SymType *GetTarget() const;
    void SetTarget(SymType *target);
    bool Equal(SymType *other) override;
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

class SymRecord: public SymType
{
public:
    SymRecord();
    SymRecord(SymbolTable *fields,  std::vector<SymVariable *> orderedFields);
    void Print(std::ostream &os, std::string indent, bool isTail) override;
    SymbolTable *GetFieldsTable() const;
    bool Equal(SymType *other) override;
    std::vector<SymVariable *> &GetOrderedFields();
private:
    SymbolTable *fields;
    std::vector<SymVariable *> orderedFields;
};

#endif //TINY_C_COMPILER_TYPE_H
