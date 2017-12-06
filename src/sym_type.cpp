#include <utility>

#include "symbols/sym_type.h"
#include "symbol_table.h"
#include "../includes/symbols/sym_variable.h"

TypeKind SymType::GetTypeKind() const
{
    return kind;
}

void SymType::SetTypeKind(TypeKind typeKind)
{
    kind = typeKind;
}

bool SymType::IsQualified() const
{
    return isQualified;
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
    symbolClass = SymbolClass::TYPE;
}

void SymBuiltInType::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << BuiltInTypeKindToString[builtInTypeKind] << std::endl;
}

bool SymBuiltInType::Equal(SymType *other)
{
    if (other->IsQualified()) other = ((SymQualifiedType *)other)->GetType();
    return kind == other->GetTypeKind() && builtInTypeKind == ((SymBuiltInType *)other)->GetBuiltIntTypeKind();
}

SymBuiltInType::SymBuiltInType(BuiltInTypeKind builtInTypeKind, uint32_t typeQualifiers): SymBuiltInType(builtInTypeKind)
{

}

bool SymBuiltInType::IsComplete()
{
    return true;
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
    if (other->IsQualified()) other = ((SymQualifiedType *)other)->GetType();
    return kind == other->GetTypeKind() && target->Equal(((SymPointer *)other)->GetTarget());
}

bool SymPointer::IsComplete()
{
    return target->IsComplete();
}

SymArray::SymArray(SymType *valueType, ExprNode *size): SymType(), valueType(valueType), size(size)
{
    kind = TypeKind::ARRAY;
    symbolClass = SymbolClass::TYPE;
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
    if (other->IsQualified()) other = ((SymQualifiedType *)other)->GetType();
    return kind == other->GetTypeKind() && valueType->Equal(((SymArray *)other)->GetValueType());
}

SymPointer *SymArray::ToPointer()
{
    return new SymPointer(valueType);
}

bool SymArray::IsComplete()
{
    return valueType->IsComplete();
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

    (returnType)->Print(os, indent, orderedParams.empty());
    os << indent << ("└── ") << "Params" << std::endl;
    for (size_t i = 0; i < orderedParams.size() - 1; ++i)
        params->Find(orderedParams[i]->GetName())->Print(os, indent + "    ", false);
    params->Find(orderedParams.back()->GetName())->Print(os, indent + "    ", true);
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

SymFunction::SymFunction(SymType *returnType, SymbolTable *params, const std::vector<SymVariable *> &orderedParamTypes):
    returnType(returnType), params(params), orderedParams(orderedParamTypes)
{
    symbolClass = SymbolClass::TYPE;
    kind = TypeKind::FUNCTION;
}

SymbolTable *SymFunction::GetParamsTable() const
{
    return params;
}

bool SymFunction::Equal(SymType *other)
{
    if (other->IsQualified()) other = ((SymQualifiedType *)other)->GetType();
    auto f = (SymFunction *)other;
    if (kind == other->GetTypeKind() && (f->GetReturnType()->Equal(returnType)))
    {
        for (int i = 0;i < orderedParams.size(); ++i)
        {
            // TODO bad comparison.
            auto selfparam = (SymVariable *)params->Find(orderedParams[i]->GetName()),
                    otherparam = (SymVariable *)f->params->Find(f->orderedParams[i]->GetName());
            if (!selfparam->GetType()->Equal(otherparam->GetType())) return false;
        }
        return true;
    }
    return false;
}

std::vector<SymVariable *> &SymFunction::GetOderedParams()
{
    return orderedParams;
}

bool SymFunction::IsComplete()
{
    for (auto it: orderedParams)
        if (it->GetName()[0] == '#') return false;
    return defined;
}

bool SymFunction::Defined() const
{
    return defined;
}

void SymFunction::Define()
{
    defined = true;
}

void SymFunction::SetParamsTable(SymbolTable *params)
{
    this->params = params;
}

void SymFunction::SetOrderedParams(std::vector<SymVariable *> &orderedParams)
{
    this->orderedParams = orderedParams;
}

SymAlias::SymAlias(std::string name, SymType *type): type(type)
{
    this->name = std::move(name);
    this->symbolClass = SymbolClass::TYPE;
    this->kind = TypeKind::TYPEDEF;
}

SymType *SymAlias::GetType()
{
    return type;
}

void SymAlias::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << name << std::endl;
    indent.append(isTail ? "    " : "│   ");
    type->Print(os, indent, true);
}

bool SymAlias::Equal(SymType *other)
{
    return type->Equal(other);
}

bool SymAlias::IsComplete()
{
    return type->IsComplete();
}

void SymRecord::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "struct " + (tag ? tag->GetName() : "") << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (!orderedFields.empty())
    {
        for (size_t i = 0; i < orderedFields.size() - 1; ++i)
            orderedFields[i]->Print(os, indent, false);
        orderedFields.back()->Print(os, indent, true);
    }
}

bool SymRecord::Equal(SymType *other)
{
    if (other->IsQualified()) other = ((SymQualifiedType *)other)->GetType();
    auto r = (SymRecord *)other;
    if (kind == other->GetTypeKind())
    {
        for (int i = 0;i < orderedFields.size(); ++i)
        {
            auto s1 = orderedFields[i];
            SymVariable *s2 = r->GetOrderedFields()[i];
            if (s1->GetName() != s2->GetName()) return false;
            if (!s1->GetType()->Equal(s2->GetType())) return false;
        }
        return true;
    }
    return false;
}

SymbolTable *SymRecord::GetFieldsTable() const
{
    return fields;
}

SymRecord::SymRecord()
{
    kind = TypeKind::STRUCT;
    fields = nullptr;
}

SymRecord::SymRecord(SymbolTable *fields, std::vector<SymVariable *> orderedFields):
        fields(fields), orderedFields(std::move(orderedFields))
{
    kind = TypeKind::STRUCT;
    symbolClass = SymbolClass::TYPE;
}

std::vector<SymVariable *> &SymRecord::GetOrderedFields()
{
    return orderedFields;
}

void SymRecord::SetTag(IdNode *tag)
{
    this->tag = tag;
}

IdNode *SymRecord::GetTag() const
{
    return tag;
}

SymRecord::SymRecord(SymbolTable *fields, std::vector<SymVariable *> orderedFields, IdNode *tag):
        SymRecord(fields, std::move(orderedFields))
{
    this->tag = tag;
}

SymRecord::SymRecord(IdNode *tag): tag(tag)
{
    name = "struct " + tag->GetName();
    symbolClass = SymbolClass::TYPE;
    kind = TypeKind::STRUCT;
}

bool SymRecord::IsComplete()
{
    return fields;
}

void SymQualifiedType::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "Qualified " + std::to_string(qualfiers) << std::endl;
    indent.append(isTail ? "    " : "│   ");
    type->Print(os, indent, true);
}

bool SymQualifiedType::Equal(SymType *other)
{
    return type->Equal(other);
}

bool SymQualifiedType::IsComplete()
{
    return type->IsComplete();
}

SymQualifiedType::SymQualifiedType(SymType *type, uint32_t qualifiers): type(type), qualfiers(qualifiers)
{
    this->isQualified = true;
    kind = type->GetTypeKind();
}

SymType *SymQualifiedType::GetType() const
{
    return type;
}

void SymQualifiedType::SetType(SymType *type1)
{
    this->type = type;
}

void SymQualifiedType::SetQualifiers(uint32_t qualifiers)
{
    this->qualfiers = qualifiers;
}

uint32_t SymQualifiedType::GetQualifiers() const
{
    return qualfiers;
}

SymEnumerator::SymEnumerator(std::string name, ExprNode *value): value(value)
{
    this->name = std::move(name);
    kind = TypeKind::ENUMERATOR;
    symbolClass = SymbolClass::TYPE;
}

ExprNode *SymEnumerator::GetValue() const
{
    return value;
}

void SymEnumerator::SetValue(ExprNode *value)
{
    this->value = value;
}

bool SymEnumerator::IsComplete()
{
    return true;
}

bool SymEnumerator::Equal(SymType *other)
{
    return value->GetType()->Equal(other);
}

void SymEnumerator::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "Enumerator" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    value->Print(os, indent, true);
}

bool SymEnum::Defined() const
{
    return defined;
}

void SymEnum::Define()
{
    defined = true;
}

SymEnum::SymEnum(IdNode *tag): tag(tag) {}

void SymEnum::Print(std::ostream &os, std::string indent, bool isTail)
{

}

bool SymEnum::Equal(SymType *other)
{
    return false;
}

bool SymEnum::IsComplete()
{
    return defined;
}
