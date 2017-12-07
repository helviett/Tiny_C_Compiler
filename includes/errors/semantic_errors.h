//
// Created by keltar on 12/3/17.
//

#ifndef TINY_C_COMPILER_SEMANTIC_ERRORS_H
#define TINY_C_COMPILER_SEMANTIC_ERRORS_H

#include "compilation_error.h"

class Symbol;
class SymType;
class SymRecord;
class IdNode;
class SymAlias;
class ExprNode;

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
    explicit RequiredModifiableLvalueError(ExprNode *expr);
    const char *what() const throw() override;
};


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
    explicit BadIndexingError(ExprNode *index);

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
    explicit BadTypeConversionError(ExprNode *expr, SymType *castType);
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

class SymFunction;

class MismatchNumberOfArguments: public SemanticError
{
public:
    explicit MismatchNumberOfArguments(ExprNode *function);
    const char *what() const throw() override;
};

class BadCalledObjectError: public SemanticError
{

public:
    BadCalledObjectError();
    explicit BadCalledObjectError(IdNode *obj);
    const char *what() const throw() override;
};

class BadJumpStatementError: public SemanticError
{
public:
    explicit BadJumpStatementError(std::shared_ptr<Token> statement);
    const char *what() const throw() override;
};

class VoidFunctionBadReturnError: public SemanticError
{
public:
    explicit VoidFunctionBadReturnError(std::shared_ptr<Token> statement);
    const char *what() const throw() override;
};

class DefinitionDoesntMatchDeclarationError: public SemanticError
{
public:
    explicit DefinitionDoesntMatchDeclarationError();
    const char *what() const throw() override;
};

class RedifinitionError: public SemanticError
{
public:
    explicit RedifinitionError(IdNode *id);
    const char *what() const throw() override;
};

class BadTypedefUsageError: public SemanticError
{
public:
    explicit BadTypedefUsageError(SymAlias *typeDef);
    const char *what() const throw() override;
};

class UnknownError: public SemanticError
{
public:
    UnknownError();
    const char *what() const throw() override;
};

class RequiredConstantExpressionError: public  SemanticError
{
public:
    explicit RequiredConstantExpressionError(IdNode *id);
    explicit RequiredConstantExpressionError(ExprNode *expr);
    const char *what() const throw() override;
};

class RequiredConstantIntegerExpressionError: public  SemanticError
{
public:
    explicit RequiredConstantIntegerExpressionError(IdNode *id);
    explicit RequiredConstantIntegerExpressionError(ExprNode *expr);
    const char *what() const throw() override;
};

class ConfclitingTypesError: public SemanticError
{
public:
    explicit ConfclitingTypesError(SymFunction *func);
    const char *what() const throw() override;
};

class ExcessElementsInStructInitializerError: public SemanticError
{
public:
    explicit ExcessElementsInStructInitializerError();
    const char *what() const throw() override;
};

class StructMemberDesignator;
class ArrayDesignator;

class BadDesignatorError: public SemanticError
{
public:
    explicit BadDesignatorError(StructMemberDesignator *designator);
    explicit BadDesignatorError(ArrayDesignator *designator);
    const char *what() const throw() override;
};

#endif //TINY_C_COMPILER_SEMANTIC_ERRORS_H
