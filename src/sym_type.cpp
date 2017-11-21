#include "symbols/sym_type.h"

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
    os << (int)builtInTypeKind << std::endl;
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

FunctionType::FunctionType(SymType *returnType): SymType(), returnType(returnType)
{
    kind = TypeKind::FUNCTION;
}

void FunctionType::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "Function returning" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    (returnType)->Print(os, indent, true);
}

SymType *FunctionType::GetReturnType() const
{
    return returnType;
}

void FunctionType::SetReturnType(SymType *returnType)
{
    this->returnType = returnType;
}
