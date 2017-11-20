#include "../includes/data_type.h"

TypeKind Type::GetTypeKind() const
{
    return kind;
}

void Type::SetTypeKind(TypeKind typeKind)
{
    kind = typeKind;
}

BuiltInTypeKind BuiltInType::GetBuiltIntTypeKind() const
{
    return builtInTypeKind;
}

void BuiltInType::SetBuiltIntTypeKind(BuiltInTypeKind typeKind)
{
    builtInTypeKind = typeKind;
}

BuiltInType::BuiltInType(BuiltInTypeKind builtInTypeKind): Type(), builtInTypeKind(builtInTypeKind)
{
    this->kind = TypeKind::BUILTIN;
}

void BuiltInType::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << (int)builtInTypeKind << std::endl;
}

PointerType::PointerType(Type *target) : Type(), target(target)
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

Type *PointerType::GetTarget() const
{
    return target;
}

void PointerType::SetTarget(Type *target)
{
    this->target = target;
}

ArrayType::ArrayType(Type *valueType, ExprNode *size): Type(), valueType(valueType), size(size)
{
    kind = TypeKind::ARRAY;
}

void ArrayType::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "Array of" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    (valueType)->Print(os, indent, true);
//    if (size) size->Print(os, indent, true);
}

Type *ArrayType::GetValueType() const
{
    return valueType;
}

void ArrayType::SetValueType(Type *valueType)
{
    this->valueType = valueType;
}

FunctionType::FunctionType(Type *returnType): Type(), returnType(returnType)
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

Type *FunctionType::GetReturnType() const
{
    return returnType;
}

void FunctionType::SetReturnType(Type *returnType)
{
    this->returnType = returnType;
}
