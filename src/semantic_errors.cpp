#include "../includes/errors/semantic_errors.h"
#include "../includes/symbols/sym_type.h"
#include "../includes/nodes/initializer.h"

InvalidOperandError::InvalidOperandError(std::shared_ptr<Token> op, SymType *ltype, SymType *rtype)
{
    auto pos = op->position;
    msg = "(" + std::to_string(pos.col) + ", " + std::to_string(pos.row) +
          "): Invalid operands for '" + op->text + "'";
}

const char *InvalidOperandError::what() const throw()
{
    return msg.c_str();
}

InvalidOperandError::InvalidOperandError(std::shared_ptr<Token> op, SymType *type)
{
    msg =  "Invalid operands for '" + op->text + "'";
}

BadIndexingError::BadIndexingError()
{
    msg =  "Subscripted value is neither array nor pointer nor vector.";
}

BadIndexingError::BadIndexingError(ExprNode *index)
{
    auto pos = index->GetPosition();
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
          "): Array subscript is not an integer.";
}

NonexistentMemberError::NonexistentMemberError(SymRecord *record, IdNode *field)
{
    auto pos = field->GetPosition();
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
          "): nonexistent member '" + field->GetName() + "'.";
}

const char *NonexistentMemberError::what() const throw()
{
    return msg.c_str();
}

RequiredModifiableLvalueError::RequiredModifiableLvalueError(ExprNode *expr)
{
    auto pos = expr->GetPosition();
    msg =  "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
           "): Required modifiable lvalue";
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
    auto pos = token->position;
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
          "): both " + token->text + " and " + spec + " presented.";
}

const char *ManyDataTypesError::what() const throw()
{
    return msg.c_str();
}

ManyDataTypesError::ManyDataTypesError(std::shared_ptr<Token> token)
{
    auto pos = token->position;
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
          "): two or more data types in declaration specifiers. ";
}

const char *DuplicateError::what() const throw()
{
    return msg.c_str();
}

DuplicateError::DuplicateError(std::shared_ptr<Token> token)
{
    auto pos = token->position;
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
          "): duplicate " + token->text + ".";
}

const char *UnsupportedTypeError::what() const throw()
{
    return msg.c_str();
}

UnsupportedTypeError::UnsupportedTypeError(std::shared_ptr<Token> token)
{
    auto pos = token->position;
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
          "): Unsupported combination of declaration specifiers. ";
}

const char *TooLongError::what() const throw()
{
    return msg.c_str();
}

TooLongError::TooLongError(std::shared_ptr<Token> token, int longtimes)
{
    auto pos = token->position;
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
          "): " + std::to_string(longtimes) + "is too long for tcc.";
}

UndeclaredIdentifierError::UndeclaredIdentifierError(std::shared_ptr<Token> token)
{
    auto pos = token->position;
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
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
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
          "): request for member '" + field->GetName() + "' in something not a structure or union.";
}

BadMemberAccessError::BadMemberAccessError(SymType *record)
{
    auto rec = (SymRecord *) record;
    auto pos = rec->GetTag()->GetPosition();
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
          "): invalid use of undefined type: '" + rec->GetName() + "'";
}

InvalidUseOfIncompleteType::InvalidUseOfIncompleteType(std::shared_ptr<Token> token, SymType *type)
{
    auto pos = token->position;
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
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
    auto pos = token->position;
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
          ") Requaired scalar type in '" + token->stringValue + "'.";
}

const char *BadTypeConversionError::what() const throw()
{
    return msg.c_str();
}

BadTypeConversionError::BadTypeConversionError(ExprNode *expr, SymType *castType)
{
    auto pos = expr->GetPosition();
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
          "): Bad type conversion";
}

const char *EnumeratorConstantTypeError::what() const throw()
{
    return msg.c_str();
}

EnumeratorConstantTypeError::EnumeratorConstantTypeError(IdNode *enumerator, SymType *exprType)
{
    auto pos = enumerator->GetPosition();
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
          "): enumerator value for '" + enumerator->GetName() + "' is not an integer constant.";
}

const char *RedeclarationError::what() const throw()
{
    return msg.c_str();
}

RedeclarationError::RedeclarationError(IdNode *id, Symbol *symbol)
{
    auto pos = id->GetPosition();
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
          "): redeclaration of '" + id->GetName() + "'.\n";
    IdNode *prev = nullptr;
    switch (symbol->GetSymbolClass())
    {
        case SymbolClass::VARIABLE:
            if ((prev = ((SymVariable *) symbol)->GetId()))
            {
                auto pos = prev->GetPosition();
                msg += "Previous declaration of '" + id->GetName() + "' was at " +
                        "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) + ")";
            }
    }
}

const char *MismatchNumberOfArguments::what() const throw()
{
    return msg.c_str();
}

MismatchNumberOfArguments::MismatchNumberOfArguments(ExprNode *function)
{
    auto pos = function->GetPosition();
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
          "): Mismatch of number of arguments in function call of '" + function->GetType()->GetName() + "'.";
}

BadCalledObjectError::BadCalledObjectError(IdNode *obj)
{
    auto pos = obj->GetPosition();
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
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
    auto pos = statement->position;
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
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
    auto pos = statement->position;
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
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
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
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

const char *RequiredConstantExpressionError::what() const throw()
{
    return msg.c_str();
}

RequiredConstantExpressionError::RequiredConstantExpressionError(IdNode *id)
{
    auto pos = id->GetPosition();
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
          "): value of '" + id->GetName() + "' is not constant.";
}

RequiredConstantExpressionError::RequiredConstantExpressionError(ExprNode *expr)
{
    auto pos = expr->GetPosition();
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
          "): value of expression is not constant.";
}

const char *ConfclitingTypesError::what() const throw()
{
    return msg.c_str();
}

ConfclitingTypesError::ConfclitingTypesError(SymFunction *func)
{
    msg = "Confclicting types for '" + func->GetName() + "'.";
}

const char *RequiredConstantIntegerExpressionError::what() const throw()
{
    return msg.c_str();
}

RequiredConstantIntegerExpressionError::RequiredConstantIntegerExpressionError(ExprNode *expr)
{
    auto pos = expr->GetPosition();
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
          "): value of expression is not integer constant.";
}

RequiredConstantIntegerExpressionError::RequiredConstantIntegerExpressionError(IdNode *id)
{
    auto pos = id->GetPosition();
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
          "): value of '" + id->GetName() + "' is not integer constant.";
}

const char *ExcessElementsInStructInitializerError::what() const throw()
{
    return msg.c_str();
}

ExcessElementsInStructInitializerError::ExcessElementsInStructInitializerError()
{
    msg = "Excess elements in struct initializer.";
}

const char *BadDesignatorError::what() const throw()
{
    return msg.c_str();
}

BadDesignatorError::BadDesignatorError(StructMemberDesignator *designator)
{
    auto pos = designator->GetMemberId()->GetPosition();
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
          "): Field name not in record or union initializer.";
}

BadDesignatorError::BadDesignatorError(ArrayDesignator *designator)
{
    auto pos = designator->GetIndex()->GetPosition();
    msg = "(" + std::to_string(pos.row) + ", " + std::to_string(pos.col) +
            "): Array index in non-array initializer.";
}
