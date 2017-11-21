#include <utility>

#include "symbols/sym_type.h"
#include "symbol_table.h"

TypeKind SymType::GetTypeKind() const
{
    return kind;
}

void SymType::SetTypeKind(TypeKind typeKind)
{
    kind = typeKind;
}

BuiltInTypeKind SymBuiltInType::GetBuiltIntTypeKind() const
{
    return builtInTypeKind;
}

void SymBuiltInType::SetBuiltIntTypeKind(BuiltInTypeKind typeKind)
{
    builtInTypeKind = typeKind;
}

SymBuiltInType::SymBuiltInType(BuiltInTypeKind builtInTypeKind): SymType(), builtInTypeKind(builtInTypeKind)
{
    this->kind = TypeKind::BUILTIN;
}

void SymBuiltInType::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << BuiltInTypeKindToString[builtInTypeKind] << std::endl;
}

PointerType::PointerType(SymType *target) : SymType(), target(target)
{
    kind = TypeKind::POINTER;
}

void PointerType::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "Pointer to" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    (target)->Print(os, indent, true);
}

SymType *PointerType::GetTarget() const
{
    return target;
}

void PointerType::SetTarget(SymType *target)
{
    this->target = target;
}

SymArray::SymArray(SymType *valueType, ExprNode *size): SymType(), valueType(valueType), size(size)
{
    kind = TypeKind::ARRAY;
}

void SymArray::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "Array of" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    (valueType)->Print(os, indent, !size);
    if (size) size->Print(os, indent, true);
}

SymType *SymArray::GetValueType() const
{
    return valueType;
}

void SymArray::SetValueType(SymType *valueType)
{
    this->valueType = valueType;
}

SymFunction::SymFunction(SymType *returnType): SymType(), returnType(returnType)
{
    kind = TypeKind::FUNCTION;
}

void SymFunction::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "Function returning" << std::endl;
    indent.append(isTail ? "    " : "│   ");

    (returnType)->Print(os, indent, orderedParamNames.empty());
    os << indent << ("└── ") << "Params" << std::endl;
    for (size_t i = 0; i < orderedParamNames.size() - 1; ++i)
        params->Find(orderedParamNames[i])->Print(os, indent + "    ", false);
    params->Find(orderedParamNames.back())->Print(os, indent + "    ", true);
}

SymType *SymFunction::GetReturnType() const
{
    return returnType;
}

void SymFunction::SetReturnType(SymType *returnType)
{
    this->returnType = returnType;
}

SymFunction::SymFunction(SymType *returnType, SymbolTable *params, const std::vector<std::string> &orderedParamTypes):
    returnType(returnType), params(params), orderedParamNames(orderedParamTypes) {}

SymFunction::SymFunction(SymType *returnType, SymbolTable *params, const std::vector<std::string> &orderedParamTypes,
                         SymbolTable *body): SymFunction(returnType, params, orderedParamTypes)
{
    this->body = body;
}

SymAlias::SymAlias(std::string name, SymType *type): type(type)
{
    this->name = std::move(name);
}
