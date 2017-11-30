#include "../includes/type_builder.h"
#include "../includes/nodes/struct.h"
#include "../includes/symbol_table.h"

SymType *TypeBuilder::Build(DeclarationSpecifiersNode *declarationSpecifiers)
{
    Singed isSinged = Singed::DEFAULT;
    TypeKind kind = TypeKind::NONE;
    ScalaraKind scalarKind = ScalaraKind::UNKNOWN;
    int longTimes = 0;
    SymType *type = nullptr;
    uint32_t typeQuals = 0;
    for (auto it: declarationSpecifiers->List())
    {
        if (it->Kind() == SpecifierKind::SIMPLE)
        {
            auto simple = (SimpleSpecifier *)it;

            if (!isTypeQualifier(simple) && kind == TypeKind::STRUCT) throw "";

            switch (simple->Value()->keyword)
            {
                case Keyword::LONG:
                    ++longTimes;
                    if (longTimes > 1) throw "";
                    if (kind != TypeKind::SCALAR && kind != TypeKind::NONE) throw "";
                    if (scalarKind != ScalaraKind::INTEGER && scalarKind != ScalaraKind::UNKNOWN) throw "";
                    kind = TypeKind::SCALAR; // TODO move functions like isTypeSpecifier to TypeBuilder
                    break;
                case Keyword::UNSIGNED:
                    if (isSinged == Singed::SINGED) throw "";
                    if (isSinged == Singed::UNSIGNED) throw "";
                    isSinged = Singed::UNSIGNED;
                    if (kind != TypeKind::SCALAR && kind != TypeKind::NONE) throw "";
                    kind = TypeKind::SCALAR;
                break;
                case Keyword::SIGNED:
                    if (isSinged == Singed::SINGED) throw "";
                    if (isSinged == Singed::UNSIGNED) throw "";
                    if (kind != TypeKind::SCALAR && kind != TypeKind::NONE) throw "";
                    isSinged = Singed::SINGED;
                    kind = TypeKind::SCALAR;
                    break;
                case Keyword::FLOAT:
                    if (scalarKind != ScalaraKind::UNKNOWN) throw "";
                    scalarKind = ScalaraKind::FLOAT;
                    if (isSinged != Singed::DEFAULT) throw "";
                    if (kind != TypeKind::SCALAR && kind != TypeKind::NONE) throw "";
                    kind = TypeKind::SCALAR;
                    break;
                case Keyword::DOUBLE:
                    if (scalarKind != ScalaraKind::UNKNOWN) throw "";
                    scalarKind = ScalaraKind::DOUBLE;
                    if (kind != TypeKind::SCALAR && kind != TypeKind::NONE) throw "";
                    if (isSinged != Singed::DEFAULT) throw "";
                    kind = TypeKind::SCALAR;
                    break;
                case Keyword::INT:
                    if (scalarKind != ScalaraKind::UNKNOWN) throw "";
                    scalarKind = ScalaraKind::INTEGER;
                    if (kind != TypeKind::SCALAR && kind != TypeKind::NONE) throw "";
                    kind = TypeKind::SCALAR;
                    break;
                case Keyword::VOID:
                    if (kind != TypeKind::NONE) throw "";
                    kind = TypeKind::VOID;
                    if (longTimes) throw "";
                    if (isSinged != Singed::DEFAULT) throw "";
                    break;
                case Keyword::CHAR:
                    if (scalarKind != ScalaraKind::UNKNOWN) throw "";
                    scalarKind = ScalaraKind::CHAR;
                    if (kind != TypeKind::SCALAR && kind != TypeKind::NONE) throw "";
                    kind = TypeKind::SCALAR;
                // TODO static, auto, extern
                case Keyword::CONST:
                    typeQuals |= (uint32_t)TypeQualifier::CONST;
                    break;
                case Keyword::VOLATILE:
                    typeQuals |= (uint32_t)TypeQualifier::VOLATILE;
                    break;
            }
        }
        else
        {
            if (kind != TypeKind ::NONE) throw "";
            kind = TypeKind::STRUCT;
            type = ((StructSpecifierNode *)it)->GetRecordType();
            // TODO struct and enum
        }
    }
    switch (kind)
    {
        case TypeKind::SCALAR:
            switch (scalarKind)
            {
                case ScalaraKind::INTEGER:
                    switch (isSinged)
                    {
                        case Singed::SINGED:
                            if (longTimes) return new SymBuiltInType(BuiltInTypeKind::INT64, typeQuals);
                            return new SymBuiltInType(BuiltInTypeKind::INT32, typeQuals);
                        case Singed::UNSIGNED:
                            if (longTimes) return new SymBuiltInType(BuiltInTypeKind::UINT64, typeQuals);
                            return new SymBuiltInType(BuiltInTypeKind::UINT32, typeQuals);
                        case Singed::DEFAULT:
                            if (longTimes) return new SymBuiltInType(BuiltInTypeKind::INT64, typeQuals);
                            return new SymBuiltInType(BuiltInTypeKind::INT32, typeQuals);
                    }
                    break;
                case ScalaraKind::DOUBLE:
                    return new SymBuiltInType(BuiltInTypeKind::DOUBLE, typeQuals);
                case ScalaraKind::FLOAT:
                    return new SymBuiltInType(BuiltInTypeKind::FLOAT, typeQuals);
                case ScalaraKind::CHAR:
                    switch (isSinged)
                    {
                        case Singed::SINGED:
                            return new SymBuiltInType(BuiltInTypeKind::INT8, typeQuals);
                        case Singed::UNSIGNED:
                            return new SymBuiltInType(BuiltInTypeKind::UINT8, typeQuals);
                        case Singed::DEFAULT:
                            return new SymBuiltInType(BuiltInTypeKind::INT8, typeQuals);
                    }
                case ScalaraKind::UNKNOWN:
                    switch (isSinged)
                    {
                        case Singed::SINGED:
                            if (longTimes) return new SymBuiltInType(BuiltInTypeKind::INT64, typeQuals);
                            throw "";
                        case Singed::UNSIGNED:
                            if (longTimes) return new SymBuiltInType(BuiltInTypeKind::UINT64, typeQuals);
                            throw "";
                        case Singed::DEFAULT:
                            if (longTimes) return new SymBuiltInType(BuiltInTypeKind::INT64, typeQuals);
                            throw "";
                    }
            }
            break;
        case TypeKind::VOID:
            return new SymBuiltInType(BuiltInTypeKind::VOID, typeQuals);
        case TypeKind::STRUCT:
            ((SymRecord *)type)->SetTypeQualifiers(typeQuals);
            return type;
    }
    throw "";
}

SymRecord *TypeBuilder::Build(StructDeclarationListNode *structDeclarationList, IdNode *tag = nullptr)
{
    std::vector<SymVariable *> orderedFields;
    auto fields = new SymbolTable();
    for (auto declarationList: structDeclarationList->List())
    {
        for (auto declarator: declarationList->List())
        {
            std::string name = declarator->GetId() ? declarator->GetId()->GetName() :
                               "#" + std::to_string(orderedFields.size());
            if (fields->Find(name)) throw "";
            auto var = new SymVariable(name, (*declarator).GetType());
            orderedFields.push_back(var);
            fields->Insert(name, var);
        }
    }
    return new SymRecord(fields, orderedFields, tag);
}

bool TypeBuilder::isTypeQualifier(SimpleSpecifier *simpleSpecifier)
{
    auto k = simpleSpecifier->Value()->keyword;
    return k == Keyword::CONST || k == Keyword::VOLATILE || k == Keyword::REGISTER;
}
