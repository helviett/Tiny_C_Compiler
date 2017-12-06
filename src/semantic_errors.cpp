#include "../includes/errors/semantic_errors.h"
#include "../includes/symbols/sym_type.h"

InvalidOperandError::InvalidOperandError(std::shared_ptr<Token> op, SymType *ltype, SymType *rtype)
{
    msg = "(" + std::to_string(op->col) + ", " + std::to_string(op->row) +
          "): Invalid iperands for '" + op->text + "'";
}

const char *InvalidOperandError::what() const throw()
{
    return msg.c_str();
}

InvalidOperandError::InvalidOperandError(std::shared_ptr<Token> op, SymType *type)
{
    msg =  "Invalid iperands for '" + op->text + "'";
}

BadIndexingError::BadIndexingError()
{
    msg =  "Subscripted value is neither array nor pointer nor vector.";
}

BadIndexingError::BadIndexingError(SymType *type)
{
    msg =  "Array subscript is not an integer.";
}

NonexistentMemberError::NonexistentMemberError(SymRecord *record, IdNode *field)
{
    auto pos = field->GetPosition();
    msg = "(" + std::to_string(pos.first) + ", " + std::to_string(pos.second) +
          "): nonexistent member '" + field->GetName() + "'.";
}

const char *NonexistentMemberError::what() const throw()
{
    return msg.c_str();
}

RequiredModifiableLvalueError::RequiredModifiableLvalueError()
{
    msg =  "Required modifiable lvalue";
}

const char *RequiredModifiableLvalueError::what() const throw()
{
    return msg.c_str();
}

const char *IncompatibleDeclarationSpecifiersError::what() const throw()
{
    return msg.c_str();
}

IncompatibleDeclarationSpecifiersError::IncompatibleDeclarationSpecifiersError(std::shared_ptr<Token> token,
                                                                               std::string spec)
{
    msg = "(" + std::to_string(token->row) + ", " + std::to_string(token->col) +
          "): both " + token->text + " and " + spec + " presented.";
}

const char *ManyDataTypesError::what() const throw()
{
    return msg.c_str();
}

ManyDataTypesError::ManyDataTypesError(std::shared_ptr<Token> token)
{
    msg = "(" + std::to_string(token->row) + ", " + std::to_string(token->col) +
          "): two or more data types in declaration specifiers. ";
}

const char *DuplicateError::what() const throw()
{
    return msg.c_str();
}

DuplicateError::DuplicateError(std::shared_ptr<Token> token)
{
    msg = "(" + std::to_string(token->row) + ", " + std::to_string(token->col) +
          "): duplicate " + token->text + ".";
}

const char *UnsupportedTypeError::what() const throw()
{
    return msg.c_str();
}

UnsupportedTypeError::UnsupportedTypeError(std::shared_ptr<Token> token)
{
    msg = "(" + std::to_string(token->row) + ", " + std::to_string(token->col) +
          "): Unsupported combination of declaration specifiers. ";
}

const char *TooLongError::what() const throw()
{
    return msg.c_str();
}

TooLongError::TooLongError(std::shared_ptr<Token> token, int longtimes)
{
    msg = "(" + std::to_string(token->row) + ", " + std::to_string(token->col) +
          "): " + std::to_string(longtimes) + "is too long for tcc.";
}

UndeclaredIdentifierError::UndeclaredIdentifierError(std::shared_ptr<Token> token)
{
    msg = "(" + std::to_string(token->row) + ", " + std::to_string(token->col) +
          ") UndeclaredIdentifierError: " + token->stringValue + ".";
}

const char *UndeclaredIdentifierError::what()  const throw()
{
    return msg.c_str();
}

const char *BadMemberAccessError::what() const throw()
{
    return msg.c_str();
}

BadMemberAccessError::BadMemberAccessError(SymType *notrecord, IdNode *field)
{
    auto pos = field->GetPosition();
    msg = "(" + std::to_string(pos.first) + ", " + std::to_string(pos.second) +
          "): request for member '" + field->GetName() + "' in something not a structure or union.";
}

BadMemberAccessError::BadMemberAccessError(SymType *record)
{
    auto rec = (SymRecord *) record;
    auto pos = rec->GetTag()->GetPosition();
    msg = "(" + std::to_string(pos.first) + ", " + std::to_string(pos.second) +
          "): invalid use of undefined type: '" + rec->GetName() + "'";
}

InvalidUseOfIncompleteType::InvalidUseOfIncompleteType(std::shared_ptr<Token> token, SymType *type)
{
    msg = "(" + std::to_string(token->row) + ", " + std::to_string(token->col) +
          ") InvalidUseOfIncompleteType in '" + token->stringValue + "'.";
}

const char *InvalidUseOfIncompleteType::what() const throw()
{
    return msg.c_str();
}

const char *RequiredScalarTypeError::what() const throw()
{
    return msg.c_str();
}

RequiredScalarTypeError::RequiredScalarTypeError(std::shared_ptr<Token> token, SymType *got)
{
    msg = "(" + std::to_string(token->row) + ", " + std::to_string(token->col) +
          ") Requaired scalar type in '" + token->stringValue + "'.";
}

const char *BadTypeConversionError::what() const throw()
{
    return msg.c_str();
}

BadTypeConversionError::BadTypeConversionError(SymType *type, SymType *castType)
{
    msg =  "Bad type conversion";
}

const char *EnumeratorConstantTypeError::what() const throw()
{
    return msg.c_str();
}

EnumeratorConstantTypeError::EnumeratorConstantTypeError(IdNode *enumerator, SymType *exprType)
{
    auto pos = enumerator->GetPosition();
    msg = "(" + std::to_string(pos.first) + ", " + std::to_string(pos.second) +
          "): enumerator value for '" + enumerator->GetName() + "' is not an integer constant.";
}

const char *RedeclarationError::what() const throw()
{
    return msg.c_str();
}

RedeclarationError::RedeclarationError(IdNode *id, Symbol *symbol)
{
    auto pos = id->GetPosition();
    msg = "(" + std::to_string(pos.first) + ", " + std::to_string(pos.second) +
          "): redeclaration of '" + id->GetName() + "'.\n";
    IdNode *prev = nullptr;
    switch (symbol->GetSymbolClass())
    {
        case SymbolClass::VARIABLE:
            if ((prev = ((SymVariable *) symbol)->GetId()))
            {
                auto pos = prev->GetPosition();
                msg += "Previous declaration of '" + id->GetName() + "' was at " +
                        "(" + std::to_string(pos.first) + ", " + std::to_string(pos.second) + ")";
            }
    }
}

const char *MismatchNumberOfArguments::what() const throw()
{
    return msg.c_str();
}

MismatchNumberOfArguments::MismatchNumberOfArguments(SymFunction *function)
{
    msg = "Mismatch of number of arguments in function call of '" + function->GetName() + "'.";
}

BadCalledObjectError::BadCalledObjectError(IdNode *obj)
{
    auto pos = obj->GetPosition();
    msg = "(" + std::to_string(pos.first) + ", " + std::to_string(pos.second) +
          "): called object '" + obj->GetName() + "' is not a function.";
}

const char *BadCalledObjectError::what() const throw()
{
    return msg.c_str();
}

BadCalledObjectError::BadCalledObjectError()
{
    msg = "Called object is not a function";
}

BadJumpStatementError::BadJumpStatementError(std::shared_ptr<Token> statement)
{
    msg = "(" + std::to_string(statement->row) + ", " + std::to_string(statement->col) +
          "): ";
    if (statement->keyword == Keyword::RETURN)
        msg += "return statement is out of function.";
    else
        msg += statement->text + " statement is out of loop.";
}

const char *BadJumpStatementError::what() const throw()
{
    return msg.c_str();
}

const char *VoidFunctionBadReturnError::what() const throw()
{
    return msg.c_str();
}

VoidFunctionBadReturnError::VoidFunctionBadReturnError(std::shared_ptr<Token> statement)
{
    msg = "(" + std::to_string(statement->row) + ", " + std::to_string(statement->col) +
          "): reurn with value if function returning void.";
}

const char *DefinitionDoesntMatchDeclarationError::what() const throw()
{
    return msg.c_str();
}

DefinitionDoesntMatchDeclarationError::DefinitionDoesntMatchDeclarationError()
{
    msg = "Definition doesn't match it's declaration";
}

const char *RedifinitionError::what() const throw()
{
    return msg.c_str();
}

RedifinitionError::RedifinitionError(IdNode *id)
{
    auto pos = id->GetPosition();
    msg = "(" + std::to_string(pos.first) + ", " + std::to_string(pos.second) +
          "): redifinition of '" + id->GetName() + "'.";
}

BadTypedefUsageError::BadTypedefUsageError(SymAlias *typeDef)
{
    msg = "Wrong typedef usage.";
}

const char *BadTypedefUsageError::what() const throw()
{
    return msg.c_str();
}

const char *UnknownError::what() const throw()
{
    return msg.c_str();
}

UnknownError::UnknownError()
{
    msg = "Unknown error";
}

const char *RequiredConstantExpression::what() const throw()
{
    return msg.c_str();
}

RequiredConstantExpression::RequiredConstantExpression(IdNode *id)
{
    auto pos = id->GetPosition();
    msg = "(" + std::to_string(pos.first) + ", " + std::to_string(pos.second) +
          "): value of '" + id->GetName() + "' is not constant.";
}
