#include "../includes/type_builder.h"

Type *TypeBuilder::Build(DeclarationSpecifiersNode *declarationSpecifiers)
{
    enum {SINGED, UNSIGNED, DEFAULT} isSinged = DEFAULT;
    enum {SCALAR, STRUCT, ENUM, NONE, VOID} kind = NONE;
    enum {INTEGER, FLOAT, DOUBLE, UNKNOWN, CHAR} scalarKind = UNKNOWN;
    int longTimes = 0;
    for (auto it: declarationSpecifiers->List())
    {
        if (it->Kind() == SpecifierKind::SIMPLE)
        {
            auto simple = (SimpleSpecifier *)it;
            switch (simple->Value()->keyword)
            {
                case Keyword::LONG:
                    ++longTimes;
                    if (longTimes > 1) throw "";
                    if (kind != SCALAR && kind != NONE) throw "";
                    if (scalarKind != INTEGER && scalarKind != UNKNOWN) throw "";
                    kind = SCALAR; // TODO move functions like isTypeSpecifier to TypeBuilder
                    break;
                case Keyword::UNSIGNED:
                    if (isSinged == SINGED) throw "";
                    if (isSinged == UNSIGNED) throw "";
                    isSinged = UNSIGNED;
                    if (kind != SCALAR && kind != NONE) throw "";
                    kind = SCALAR;
                break;
                case Keyword::SIGNED:
                    if (isSinged == SINGED) throw "";
                    if (isSinged == UNSIGNED) throw "";
                    if (kind != SCALAR && kind != NONE) throw "";
                    isSinged = SINGED;
                    kind = SCALAR;
                    break;
                case Keyword::FLOAT:
                    if (scalarKind != UNKNOWN) throw "";
                    scalarKind = FLOAT;
                    if (isSinged != DEFAULT) throw "";
                    if (kind != SCALAR && kind != NONE) throw "";
                    kind = SCALAR;
                    break;
                case Keyword::DOUBLE:
                    if (scalarKind != UNKNOWN) throw "";
                    scalarKind = DOUBLE;
                    if (kind != SCALAR && kind != NONE) throw "";
                    if (isSinged != DEFAULT) throw "";
                    kind = SCALAR;
                    break;
                case Keyword::INT:
                    if (scalarKind != UNKNOWN) throw "";
                    scalarKind = INTEGER;
                    if (kind != SCALAR && kind != NONE) throw "";
                    kind = SCALAR;
                    break;
                case Keyword::VOID:
                    if (kind != NONE) throw "";
                    kind = VOID;
                    if (!longTimes) throw "";
                    if (isSinged != DEFAULT) throw "";
                    break;
                case Keyword::CHAR:
                    if (scalarKind != UNKNOWN) throw "";
                    scalarKind = INTEGER;
                    if (kind != SCALAR && kind != NONE) throw "";
                    kind = SCALAR;
                // TODO static, auto, extern
            }
        }
        else
        {
            // TODO struct and enum
        }
    }

    switch (kind)
    {
        case SCALAR:
            switch (scalarKind)
            {
                case INTEGER:
                    switch (isSinged)
                    {
                        case SINGED:
                            if (longTimes) return new BuiltInType(BuiltInTypeKind::INT64);
                            return new BuiltInType(BuiltInTypeKind::INT32);
                        case UNSIGNED:
                            if (longTimes) return new BuiltInType(BuiltInTypeKind::UINT64);
                            return new BuiltInType(BuiltInTypeKind::UINT32);
                        case DEFAULT:
                            if (longTimes) return new BuiltInType(BuiltInTypeKind::INT64);
                            return new BuiltInType(BuiltInTypeKind::INT32);
                    }
                    break;
                case DOUBLE:
                    return new BuiltInType(BuiltInTypeKind::DOUBLE);
                case FLOAT:
                    return new BuiltInType(BuiltInTypeKind::FLOAT);
                case CHAR:
                    switch (isSinged)
                    {
                        case SINGED:
                            return new BuiltInType(BuiltInTypeKind::INT8);
                        case UNSIGNED:
                            return new BuiltInType(BuiltInTypeKind::UINT8);
                        case DEFAULT:
                            return new BuiltInType(BuiltInTypeKind::INT8);
                    }
                    break;
                case UNKNOWN:
                    switch (isSinged)
                    {
                        case SINGED:
                            if (longTimes) return new BuiltInType(BuiltInTypeKind::INT64);
                            throw "";
                        case UNSIGNED:
                            if (longTimes) return new BuiltInType(BuiltInTypeKind::UINT64);
                            throw "";
                        case DEFAULT:
                            if (longTimes) return new BuiltInType(BuiltInTypeKind::INT64);
                            throw "";
                    }
            }
            break;
        case VOID:
            return new BuiltInType(BuiltInTypeKind::VOID);
    }
    return nullptr;
}