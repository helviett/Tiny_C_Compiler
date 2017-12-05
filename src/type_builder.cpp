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

            if (!isTypeQualifier(simple) && (kind == TypeKind::STRUCT)) throw ManyDataTypesError(simple->Value());
            if (simple->Value()->keyword == Keyword::VOID)
            {
                if (kind != TypeKind::NONE) throw ManyDataTypesError(simple->Value());
                kind = TypeKind::VOID;
                if (longTimes) throw UnsupportedTypeError(simple->Value());
                if (isSinged != Singed::DEFAULT) throw UnsupportedTypeError(simple->Value());
                continue;
            }

            if (!isTypeQualifier(simple) && (kind != TypeKind::SCALAR && kind != TypeKind::NONE))
                throw ManyDataTypesError(simple->Value());

            switch (simple->Value()->keyword)
            {
                case Keyword::LONG:
                    ++longTimes;
                    if (longTimes > 1) throw TooLongError(simple->Value(), longTimes);
                    if (scalarKind != ScalaraKind::INTEGER && scalarKind != ScalaraKind::UNKNOWN)
                        throw UnsupportedTypeError(simple->Value());
                    kind = TypeKind::SCALAR;
                    scalarKind = ScalaraKind::INTEGER;
                    break;
                case Keyword::UNSIGNED:
                    if (isSinged == Singed::SINGED)
                        throw IncompatibleDeclarationSpecifiersError(simple->Value(), "signed");
                    if (isSinged == Singed::UNSIGNED) throw DuplicateError(simple->Value());
                    isSinged = Singed::UNSIGNED;
                    kind = TypeKind::SCALAR;
                break;
                case Keyword::SIGNED:
                    if (isSinged == Singed::SINGED) DuplicateError(simple->Value());
                    if (isSinged == Singed::UNSIGNED)
                        throw IncompatibleDeclarationSpecifiersError(simple->Value(), "unsigned");
                    isSinged = Singed::SINGED;
                    kind = TypeKind::SCALAR;
                    break;
                case Keyword::FLOAT:
                    if (scalarKind != ScalaraKind::UNKNOWN) throw ManyDataTypesError(simple->Value());
                    scalarKind = ScalaraKind::FLOAT;
                    if (isSinged != Singed::DEFAULT) throw UnsupportedTypeError(simple->Value());
                    kind = TypeKind::SCALAR;
                    break;
                case Keyword::DOUBLE:
                    if (scalarKind != ScalaraKind::UNKNOWN) throw ManyDataTypesError(simple->Value());
                    scalarKind = ScalaraKind::DOUBLE;
                    if (isSinged != Singed::DEFAULT) throw UnsupportedTypeError(simple->Value());
                    kind = TypeKind::SCALAR;
                    break;
                case Keyword::INT:
                    if (scalarKind != ScalaraKind::UNKNOWN) throw ManyDataTypesError(simple->Value());
                    scalarKind = ScalaraKind::INTEGER;
                    kind = TypeKind::SCALAR;
                    break;
                case Keyword::CHAR:
                    if (scalarKind != ScalaraKind::UNKNOWN) throw ManyDataTypesError(simple->Value());
                    scalarKind = ScalaraKind::CHAR;
                    kind = TypeKind::SCALAR;
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
            if (kind != TypeKind ::NONE) throw ManyDataTypesError(((StructSpecifierNode *)it)->GetToken());
            kind = TypeKind::STRUCT;
            type = ((StructSpecifierNode *)it)->GetRecordType();
            // TODO struct and enum
        }
    }
    if (kind == TypeKind::NONE) kind = TypeKind::SCALAR;
    if (isSinged == Singed::DEFAULT) isSinged = Singed::SINGED;
    if (scalarKind == ScalaraKind::UNKNOWN) scalarKind = ScalaraKind::INTEGER;
    switch (kind)
    {
        case TypeKind::SCALAR:
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
        case TypeKind::VOID:
            return new SymQualifiedType(new SymBuiltInType(BuiltInTypeKind::VOID), typeQuals);
        case TypeKind::STRUCT:
            if (typeQuals) return new SymQualifiedType(type, typeQuals);
            return type;
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
