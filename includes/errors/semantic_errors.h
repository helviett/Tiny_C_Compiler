//
// Created by keltar on 12/3/17.
//

#ifndef TINY_C_COMPILER_SEMANTIC_ERRORS_H
#define TINY_C_COMPILER_SEMANTIC_ERRORS_H

#include "compilation_error.h"

class SemanticError: public CompilationError
{
public:
    const char *what() const throw() override = 0;
};

class UndeclaredIdentifierError: public SemanticError
{
public:
    explicit UndeclaredIdentifierError(std::shared_ptr<Token> token);
    const char *what() const throw() override;
};

class TooLongError: public SemanticError
{
public:
    explicit TooLongError(std::shared_ptr<Token> token, int longtimes);
    const char *what() const throw() override;
};

class UnsupportedTypeError: public SemanticError
{
public:
    explicit UnsupportedTypeError(std::shared_ptr<Token> token);
    const char *what() const throw() override;
};

class DuplicateError: public SemanticError
{
public:
    explicit DuplicateError(std::shared_ptr<Token> token);
    const char *what() const throw() override;
};

class ManyDataTypesError: public SemanticError
{
public:
    explicit ManyDataTypesError(std::shared_ptr<Token> token);
    const char *what() const throw() override;
};

class IncompatibleDeclarationSpecifiersError: public SemanticError
{
public:
    explicit IncompatibleDeclarationSpecifiersError(std::shared_ptr<Token> token, std::string spec);
    const char *what() const throw() override;
};

class RequiredModifiableLvalueError: public SemanticError
{
public:
    explicit RequiredModifiableLvalueError();
    const char *what() const throw() override;
};

class Symbol;
class SymType;
class SymRecord;
class IdNode;

class InvalidOperandError: public SemanticError
{
public:
    explicit InvalidOperandError(std::shared_ptr<Token> op, SymType *ltype, SymType *rtype);
    explicit InvalidOperandError(std::shared_ptr<Token> op, SymType *type);

    const char *what() const throw() override;
};

class BadIndexingError: public SemanticError
{
public:
    BadIndexingError();
    explicit BadIndexingError(SymType *type);

    const char *what() const throw() override
    {
        return msg.c_str();
    }
};

class NonexistentMemberError: public SemanticError
{
public:
    NonexistentMemberError(SymRecord *record, IdNode *field);
    const char *what() const throw() override;
};

class BadMemberAccessError: public SemanticError
{
public:
    BadMemberAccessError(SymType *notrecord, IdNode *field);
    BadMemberAccessError(SymType *record);
    const char *what() const throw() override;
};

class InvalidUseOfIncompleteType: public SemanticError
{
public:
    explicit InvalidUseOfIncompleteType(std::shared_ptr<Token> token, SymType *type);
    const char *what() const throw() override;
};

class RequiredScalarTypeError: public SemanticError
{
public:
    explicit RequiredScalarTypeError(std::shared_ptr<Token> token, SymType *got);
    const char *what() const throw() override;
};

class BadTypeConversionError: public SemanticError
{
public:
    explicit BadTypeConversionError(SymType *type, SymType *castType);
    const char *what() const throw() override;
};

class EnumeratorConstantTypeError: public SemanticError
{
public:
    EnumeratorConstantTypeError(IdNode *enumerator, SymType *exprType);
    const char *what() const throw() override;
};

class RedeclarationError: public SemanticError
{
public:
    RedeclarationError(IdNode *id, Symbol *symbol);
    const char *what() const throw() override;
};

#endif //TINY_C_COMPILER_SEMANTIC_ERRORS_H