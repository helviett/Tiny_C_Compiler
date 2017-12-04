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
    msg =  "Required lvalue";
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
