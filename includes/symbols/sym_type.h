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
    VOID = 0, INT8 = 1, INT16 = 3, INT32 = 5, INT64 = 7,
    UINT8 = 2, UINT16 = 4, UINT32 = 6, UINT64 = 8, FLOAT = 9, DOUBLE = 10, NONE
};

enum class TypeKind
{
    ENUMERATOR, STRUCT, POINTER, BUILTIN, ARRAY, FUNCTION, TYPEDEF
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
    virtual bool IsComplete() = 0;
    bool IsQualified() const;
protected:
    TypeKind kind;
    bool isQualified{false};
};

class SymQualifiedType: public SymType
{
public:
    SymQualifiedType(SymType *type, uint32_t qualifiers);
    void Print(std::ostream &os, std::string indent, bool isTail) override;
    bool Equal(SymType *other) override;
    bool IsComplete() override;
    SymType *GetType() const;
    void SetType(SymType *type);
    uint32_t GetQualifiers() const;
    void SetQualifiers(uint32_t qualifiers);
private:
    SymType *type;
    uint32_t qualfiers{0};
};

class SymBuiltInType: public SymType
{
public:
    explicit SymBuiltInType (BuiltInTypeKind builtInTypeKind);
    SymBuiltInType (BuiltInTypeKind builtInTypeKind, uint32_t typeQualifiers);
    BuiltInTypeKind GetBuiltIntTypeKind() const;
    void SetBuiltIntTypeKind(BuiltInTypeKind typeKind);
    void Print(std::ostream &os, std::string indent, bool isTail) override;
    bool Equal(SymType *other) override;
    bool IsComplete() override;
private:
    BuiltInTypeKind builtInTypeKind;
};

class SymPointer: public SymType
{
public:
    explicit SymPointer(SymType *target);
    void Print(std::ostream &os, std::string indent, bool isTail) override;
    SymType *GetTarget() const;
    void SetTarget(SymType *target);
    bool Equal(SymType *other) override;
    bool IsComplete() override;
private:
    SymType *target;
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
    SymPointer *ToPointer();
    bool IsComplete() override;
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
    void Print(std::ostream &os, std::string indent, bool isTail) override;
    SymType *GetReturnType() const;
    void SetReturnType(SymType *returnType);
    SymbolTable *GetParamsTable() const;
    void SetParamsTable(SymbolTable *params);
    void SetOrderedParams(std::vector<SymVariable *> &orderedParams);
    bool Equal(SymType *other) override;
    std::vector<SymVariable *> &GetOderedParams();
    bool IsComplete() override;
    bool Defined() const;
    void Define();
private:
    SymType *returnType{nullptr};
    SymbolTable *params{nullptr};
    bool defined{false};
    std::vector<SymVariable *> orderedParams;
};

class SymAlias: public SymType
{
public:
    SymAlias(std::string name, SymType *type);
    SymType *GetType();
    void Print(std::ostream &os, std::string indent, bool isTail) override;
    bool Equal(SymType *other) override;
    bool IsComplete() override;
private:
    SymType *type;
};

class SymRecord: public SymType
{
public:
    SymRecord();
    SymRecord(IdNode *tag);
    SymRecord(SymbolTable *fields,  std::vector<SymVariable *> orderedFields);
    SymRecord(SymbolTable *fields,  std::vector<SymVariable *> orderedFields, IdNode *tag);
    void Print(std::ostream &os, std::string indent, bool isTail) override;
    SymbolTable *GetFieldsTable() const;
    bool Equal(SymType *other) override;
    std::vector<SymVariable *> &GetOrderedFields();
    IdNode *GetTag() const;
    void SetTag(IdNode *tag);
    bool IsComplete() override;
private:
    IdNode *tag{nullptr};
    SymbolTable *fields{nullptr};
    std::vector<SymVariable *> orderedFields;
};

class SymEnumerator: public SymType
{
public:
    SymEnumerator(std::string name, ExprNode *value);
    ExprNode *GetValue() const;
    void SetValue(ExprNode *value);
    void Print(std::ostream &os, std::string indent, bool isTail) override;
    bool Equal(SymType *other) override;
    bool IsComplete() override;
private:
    ExprNode *value{nullptr};
};

#endif //TINY_C_COMPILER_TYPE_H
