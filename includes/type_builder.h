//
// Created by keltar on 11/16/17.
//

#ifndef TINY_C_COMPILER_TYPE_BUILDER_H
#define TINY_C_COMPILER_TYPE_BUILDER_H

#include "symbols.h"
#include "errors/semantic_errors.h"

class StructDeclarationListNode;

class DeclarationSpecifiersNode;

class TypeBuilder
{
public:
    static SymType *Build(DeclarationSpecifiersNode *declarationSpecifiers, bool &isTypedef);
    static SymType *Build(DeclarationSpecifiersNode *declarationSpecifiers);
    static SymRecord *Build(StructDeclarationListNode *structDeclarationList, IdNode *tag);
private:
    enum class Singed { SINGED, UNSIGNED, DEFAULT};
    enum class ScalaraKind { INTEGER, FLOAT, DOUBLE, UNKNOWN, CHAR };
    enum class TypeKind { SCALAR, STRUCT, ENUM, NONE, VOID, TYPEDEF};
    static bool isTypeQualifier(SimpleSpecifier *simpleSpecifier);

//    static bool isTypeSpecifier(SimpleSpecifier *simpleSpecifier);
};
#endif //TINY_C_COMPILER_TYPE_BUILDER_H
