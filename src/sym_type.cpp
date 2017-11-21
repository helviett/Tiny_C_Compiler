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

bool SymBuiltInType::Equal(SymType *other)
{
    return kind == other->GetTypeKind() && builtInTypeKind == ((SymBuiltInType *)other)->GetBuiltIntTypeKind();
}

SymPointer::SymPointer(SymType *target) : SymType(), target(target)
{
    kind = TypeKind::POINTER;
}

void SymPointer::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "Pointer to" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    (target)->Print(os, indent, true);
}

SymType *SymPointer::GetTarget() const
{
    return target;
}

void SymPointer::SetTarget(SymType *target)
{
    this->target = target;
}

bool SymPointer::Equal(SymType *other)
{
    return kind == other->GetTypeKind() && target == ((SymPointer *)other)->GetTarget();
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

bool SymArray::Equal(SymType *other)
{
    return kind == other->GetTypeKind() && valueType == ((SymArray *)other)->GetValueType();
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
    kind = TypeKind::FUNCTION;
    this->returnType = returnType;
}

SymFunction::SymFunction(SymType *returnType, SymbolTable *params, const std::vector<std::string> &orderedParamTypes):
    returnType(returnType), params(params), orderedParamNames(orderedParamTypes)
{
    kind = TypeKind::FUNCTION;
}

SymFunction::SymFunction(SymType *returnType, SymbolTable *params, const std::vector<std::string> &orderedParamTypes,
                         SymbolTable *body): SymFunction(returnType, params, orderedParamTypes)
{
    this->body = body;
}

SymbolTable *SymFunction::GetParamsTable() const
{
    return params;
}

bool SymFunction::Equal(SymType *other)
{
    auto f = (SymFunction *)other;
    if (kind == other->GetTypeKind() && (f->GetReturnType()->Equal(returnType)))
    {
        for (int i = 0;i < orderedParamNames.size(); ++i)
        {
            auto selfparam = (SymVariable *)params->Find(orderedParamNames[i]),
                    otherparam = (SymVariable *)f->params->Find(f->orderedParamNames[i]);
            if (!selfparam->GetType()->Equal(otherparam->GetType())) return false;
        }
        return true;
    }
    return false;
}

SymAlias::SymAlias(std::string name, SymType *type): type(type)
{
    this->name = std::move(name);
}
