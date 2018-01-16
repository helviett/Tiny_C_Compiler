#include <nodes.h>
#include "../includes/type_builder.h"
#include "../includes/nodes/struct.h"
#include "../includes/symbol_table.h"

SymType *TypeBuilder::Build(DeclarationSpecifiersNode *declarationSpecifiers, bool &isTypedef)
{
    Singed isSinged = Singed::DEFAULT;
    TypeClass kind = TypeClass::NONE;
    ScalaraKind scalarKind = ScalaraKind::UNKNOWN;
    int longTimes = 0;
    SymType *type = nullptr;
    uint32_t typeQuals = 0;
    isTypedef = false;
    for (auto it: declarationSpecifiers->List())
    {
        if (it->Kind() == SpecifierKind::SIMPLE)
        {
            auto simple = (SimpleSpecifier *)it;

            if (!isTypeQualifier(simple) && (kind == TypeClass::STRUCT)) throw ManyDataTypesError(simple->Value());
            if (simple->Value()->keyword == Keyword::VOID)
            {
                if (kind != TypeClass::NONE) throw ManyDataTypesError(simple->Value());
                kind = TypeClass::VOID;
                if (longTimes) throw UnsupportedTypeError(simple->Value());
                if (isSinged != Singed::DEFAULT) throw UnsupportedTypeError(simple->Value());
                continue;
            }

            if (!isTypeQualifier(simple) && (kind != TypeClass::SCALAR && kind != TypeClass::NONE))
                throw ManyDataTypesError(simple->Value());

            switch (simple->Value()->keyword)
            {
                case Keyword::LONG:
                    ++longTimes;
                    if (longTimes > 1) throw TooLongError(simple->Value(), longTimes);
                    if (scalarKind != ScalaraKind::INTEGER && scalarKind != ScalaraKind::UNKNOWN)
                        throw UnsupportedTypeError(simple->Value());
                    kind = TypeClass::SCALAR;
                    scalarKind = ScalaraKind::INTEGER;
                    break;
                case Keyword::UNSIGNED:
                    if (isSinged == Singed::SINGED)
                        throw IncompatibleDeclarationSpecifiersError(simple->Value(), "signed");
                    if (isSinged == Singed::UNSIGNED) throw DuplicateError(simple->Value());
                    isSinged = Singed::UNSIGNED;
                    kind = TypeClass::SCALAR;
                break;
                case Keyword::SIGNED:
                    if (isSinged == Singed::SINGED) DuplicateError(simple->Value());
                    if (isSinged == Singed::UNSIGNED)
                        throw IncompatibleDeclarationSpecifiersError(simple->Value(), "unsigned");
                    isSinged = Singed::SINGED;
                    kind = TypeClass::SCALAR;
                    break;
                case Keyword::FLOAT:
                    if (scalarKind != ScalaraKind::UNKNOWN) throw ManyDataTypesError(simple->Value());
                    scalarKind = ScalaraKind::FLOAT;
                    if (isSinged != Singed::DEFAULT) throw UnsupportedTypeError(simple->Value());
                    kind = TypeClass::SCALAR;
                    break;
                case Keyword::DOUBLE:
                    if (scalarKind != ScalaraKind::UNKNOWN) throw ManyDataTypesError(simple->Value());
                    scalarKind = ScalaraKind::DOUBLE;
                    if (isSinged != Singed::DEFAULT) throw UnsupportedTypeError(simple->Value());
                    kind = TypeClass::SCALAR;
                    break;
                case Keyword::INT:
                    if (scalarKind != ScalaraKind::UNKNOWN) throw ManyDataTypesError(simple->Value());
                    scalarKind = ScalaraKind::INTEGER;
                    kind = TypeClass::SCALAR;
                    break;
                case Keyword::CHAR:
                    if (scalarKind != ScalaraKind::UNKNOWN) throw ManyDataTypesError(simple->Value());
                    scalarKind = ScalaraKind::CHAR;
                    kind = TypeClass::SCALAR;
                    break;
                case Keyword::CONST:
                    typeQuals |= (uint32_t)TypeQualifier::CONST;
                    break;
                case Keyword::VOLATILE:
                    typeQuals |= (uint32_t)TypeQualifier::VOLATILE;
                    break;
                case Keyword::TYPEDEF:
                    if (isTypedef) throw DuplicateError(simple->Value());
                    isTypedef = true;
                    break;
            }
        }
        else if ((*it).Kind() == SpecifierKind::STRUCT)
        {
            if (kind != TypeClass ::NONE) throw ManyDataTypesError(((StructSpecifierNode *)it)->GetToken());
            kind = TypeClass::STRUCT;
            type = ((StructSpecifierNode *)it)->GetRecordType();
            // TODO struct and enum
        }
        else if ((*it).Kind() == SpecifierKind::TYPEDEF)
        {
            if (kind != TypeClass ::NONE) throw ManyDataTypesError(((TypedefIdentifierNode *)it)->GetToken());
            kind = TypeClass::TYPEDEF;
            type = ((TypedefIdentifierNode *)it)->GetAlias()->GetType();
        }
        else
        {
            if (kind != TypeClass ::NONE) throw ManyDataTypesError(((TypedefIdentifierNode *)it)->GetToken());
            kind = TypeClass::ENUM;
        }
    }
    if (kind == TypeClass::NONE) kind = TypeClass::SCALAR;
    if (isSinged == Singed::DEFAULT) isSinged = Singed::SINGED;
    if (scalarKind == ScalaraKind::UNKNOWN) scalarKind = ScalaraKind::INTEGER;
    switch (kind)
    {
        case TypeClass::SCALAR:
            switch (scalarKind)
            {
                case ScalaraKind::INTEGER:
                    switch (isSinged)
                    {
                        case Singed::SINGED:
                            if (longTimes) return new SymQualifiedType(new SymBuiltInType(BuiltInTypeKind::INT64), typeQuals);
                            return new SymQualifiedType(new SymBuiltInType(BuiltInTypeKind::INT32), typeQuals);
                        case Singed::UNSIGNED:
                            if (longTimes) return new SymQualifiedType(new SymBuiltInType(BuiltInTypeKind::UINT64), typeQuals);
                            return new SymQualifiedType(new SymBuiltInType(BuiltInTypeKind::UINT32), typeQuals);
                    }
                case ScalaraKind::DOUBLE:
                    return new SymQualifiedType(new SymBuiltInType(BuiltInTypeKind::DOUBLE), typeQuals);
                case ScalaraKind::FLOAT:
                    return new SymQualifiedType(new SymBuiltInType(BuiltInTypeKind::FLOAT), typeQuals);
                case ScalaraKind::CHAR:
                    switch (isSinged)
                    {
                        case Singed::SINGED:
                            return new SymQualifiedType(new SymBuiltInType(BuiltInTypeKind::INT8), typeQuals);
                        case Singed::UNSIGNED:
                            return new SymQualifiedType(new SymBuiltInType(BuiltInTypeKind::UINT8), typeQuals);
                    }
                case ScalaraKind::UNKNOWN:
                    switch (isSinged)
                    {
                        case Singed::SINGED:
                            if (longTimes) return new SymQualifiedType(new SymBuiltInType(BuiltInTypeKind::INT64), typeQuals);
                            return new SymQualifiedType(new SymBuiltInType(BuiltInTypeKind::INT32), typeQuals);
                        case Singed::UNSIGNED:
                            if (longTimes) return new SymQualifiedType(new SymBuiltInType(BuiltInTypeKind::UINT64), typeQuals);
                            return new SymQualifiedType(new SymBuiltInType(BuiltInTypeKind::UINT32), typeQuals);
                    }
            }
        case TypeClass::VOID:
            return new SymQualifiedType(new SymBuiltInType(BuiltInTypeKind::VOID), typeQuals);
        case TypeClass::STRUCT:
        case TypeClass::TYPEDEF:
            if (typeQuals) return new SymQualifiedType(type, typeQuals);
            return type;
        case TypeClass::ENUM:
            if (typeQuals) return new SymQualifiedType(new SymBuiltInType(BuiltInTypeKind::INT32), typeQuals);
            return new SymBuiltInType(BuiltInTypeKind::INT32);
    }
    throw ""; // Unreachable
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
            auto dt = declarator->GetType()->GetUnqualified();
            if (!dt->IsComplete()) throw FieldOfIncompleteTypeError(declarator);
            auto var = new SymVariable(name, (*declarator).GetType(), declarator->GetId());
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

SymType *TypeBuilder::Build(DeclarationSpecifiersNode *declarationSpecifiers)
{
    bool fake;
    return TypeBuilder::Build(declarationSpecifiers, fake);
}

uint32_t TypeBuilder::BuildTypeQualifiers(DeclarationSpecifiersNode *declarationSpecifiers)
{
    uint32_t res = 0;
    for (auto it: declarationSpecifiers->List())
    {
        switch (dynamic_cast<SimpleSpecifier *>(it)->Value()->keyword)
        {
            case Keyword::CONST:
                res |= (uint32_t)TypeQualifier::CONST;
                break;
            case Keyword::VOLATILE:
                res |= (uint32_t)TypeQualifier::VOLATILE;
                break;
        }
    }
    return res;
}
