#include <utility>

#include "../includes/semantic_analyzer.h"

IdNode *SemanticAnalyzer::BuildIdNode(std::shared_ptr<Token> token)
{
    auto symbol = scopeTree.Find(token->text);
    if (!symbol) throw UndeclaredIdentifierError(token);
    if (symbol->GetSymbolClass() == SymbolClass::UNDEFINED) throw UnknownError(); // Unreachable
    if (symbol->GetSymbolClass() == SymbolClass::VARIABLE)
    {

        auto id = new IdNode(token, ((SymVariable *)symbol)->GetType());
        switch (id->GetType()->GetTypeKind())
        {
            case TypeKind::ARRAY: case TypeKind::FUNCTION ://case TypeKind::STRUCT:
                id->SetValueCategory(ValueCategory::RVALUE);
                break;
            default:
                id->SetValueCategory(ValueCategory::LVAVLUE);
        }
        return id;
    }
    if (symbol->GetSymbolClass() == SymbolClass::TYPE)
    {
        auto t = (SymType *)symbol;
        switch (t->GetTypeKind())
        {
            case TypeKind::FUNCTION:
                return new IdNode(token, t);
            case TypeKind::TYPEDEF:
                throw BadTypedefUsageError((SymAlias *)symbol);
            case TypeKind::ENUMERATOR:
                return (IdNode *)((SymEnumerator *)symbol)->GetValue();
        }
    }
    throw UnknownError(); // Unreachable
}

StructSpecifierNode *SemanticAnalyzer::BuildStructSpecifierNode(IdNode *tag,
                                                                StructDeclarationListNode *structDeclarationList,
                                                                std::shared_ptr<Token> structToken)
{
    if (!tag && !structDeclarationList) throw UnknownError();
    SymRecord *rt = nullptr;
    if (structDeclarationList)
    {
        rt = TypeBuilder::Build(structDeclarationList, tag);
        rt->SetTag(tag);
    }
    Symbol *s = nullptr;
    if (tag)
    {
        s = scopeTree.GetActiveScope()->Find("struct " + tag->GetName());
        if (s)
        {
            if (s->GetSymbolClass() != SymbolClass::TYPE) throw UnknownError(); // Unreachable
            if (((SymType *)s)->GetTypeKind() != TypeKind::STRUCT) throw UnknownError(); // Unreachable
            auto record = (SymRecord *)s;
            if (structDeclarationList)
            {
                if (!((SymRecord *)unqualify(record))->GetOrderedFields().empty())
                    throw RedifinitionError(tag);
            }
            if (rt)
                *record = *rt;
            return new StructSpecifierNode(record, structToken);
        }
        if (!rt) rt = new SymRecord(tag);
        rt->SetName("struct " + tag->GetName());
        scopeTree.GetActiveScope()->Insert(rt->GetName(), rt);
    }
    return new StructSpecifierNode(rt, structToken);
}

ScopeTree *SemanticAnalyzer::GetScopeTree()
{
    return &scopeTree;
}

PostfixDecrementNode *SemanticAnalyzer::BuildPostfixDecrementNode(ExprNode *expr, const std::shared_ptr<Token> &op)
{
    CheckIncDecRules(expr, op);
    auto res = new PostfixDecrementNode(expr);
    res->SetPosition(op);
    return new PostfixDecrementNode(expr);
}

PostfixIncrementNode *SemanticAnalyzer::BuildPostfixIncrementNode(ExprNode *expr, const std::shared_ptr<Token> &op)
{
    CheckIncDecRules(expr, op);
    auto res = new PostfixIncrementNode(expr);
    res->SetPosition(op);
    return res;
}

void SemanticAnalyzer::CheckIncDecRules(ExprNode *expr, std::shared_ptr<Token> op)
{
    if (!isModifiableLvalue(expr)) throw RequiredModifiableLvalueError(expr);
    auto type = unqualify(expr->GetType());
    if (!isArithmeticType(type) && !isPointerType(type) || isVoidPointer(type))
        throw InvalidOperandError(std::move(op), expr->GetType());
}

bool SemanticAnalyzer::isArithmeticType(SymType *type)
{
    type = unqualify(type);
    if (type->GetTypeKind() != TypeKind::BUILTIN) return false;
    auto bitk = ((SymBuiltInType *)type)->GetBuiltIntTypeKind();
    return bitk != BuiltInTypeKind::VOID;
}

bool SemanticAnalyzer::isPointerType(SymType *type)
{
    return type->GetTypeKind() == TypeKind::POINTER;
}

InitDeclaratorNode *SemanticAnalyzer::BuildInitDeclaratorNode(DeclaratorNode *declarator,
                                                              InitializerNode *initializer,
                                                              bool isTypedef)
{
    auto prev = scopeTree.GetActiveScope()->Find(declarator->GetId()->GetName()); // TODO FUNCTIONS
    if (prev) throw RedeclarationError(declarator->GetId(), prev);
    auto name = declarator->GetId()->GetName();
    auto t = declarator->GetType();
    if (t->GetTypeKind() == TypeKind::FUNCTION)
    {
        if (isTypedef)
            scopeTree.GetActiveScope()->Insert(name, new SymAlias(name, t));
        else
        {
            ((SymFunction *)t)->SetName(declarator->GetId()->GetName());
            scopeTree.GetActiveScope()->Insert(declarator->GetId()->GetName(), t);
        }
    }
    else
    {
        if (isVoidType(t)) throw UnknownVariableStorageError(new SymVariable(name, t, declarator->GetId()));
        if (isTypedef)
            scopeTree.GetActiveScope()->Insert(name, new SymAlias(name, t));
        else
            scopeTree.GetActiveScope()->Insert(name, new SymVariable(name, t, declarator->GetId()));
    }
    if (initializer)
        analyseInitializerList(declarator->GetType(), initializer, nullptr);
    return new InitDeclaratorNode(declarator, initializer);
}

bool SemanticAnalyzer::isVoidPointer(SymType *type)
{
    type = unqualify(type);
    if (type->GetTypeKind() != TypeKind::POINTER) return false;
    auto target = unqualify(((SymPointer *)type)->GetTarget());
    return target->GetTypeKind() == TypeKind::BUILTIN &&
            ((SymBuiltInType *)target)->GetBuiltIntTypeKind() == BuiltInTypeKind::VOID;
}

StructureOrUnionMemberAccessNode *
SemanticAnalyzer::BuildStructureOrUnionMemberAccessNode(ExprNode *structure, IdNode *field, std::shared_ptr<Token> dot)
{
    auto type = structure->GetType();
    if (type->GetTypeKind() != TypeKind::STRUCT) throw BadMemberAccessError(type, field);
    auto stype = (SymRecord *)unqualify(type);
    if (!stype->IsComplete()) throw BadMemberAccessError(stype);
    SymVariable *sfield;
    if (!(sfield = (SymVariable *)stype->GetFieldsTable()->Find(field->GetName())))
        throw NonexistentMemberError(stype, field);
    auto res = new StructureOrUnionMemberAccessNode(structure, field);
    res->SetPosition(dot);
    uint32_t squals = type->IsQualified() ? ((SymQualifiedType *)type)->GetQualifiers() : 0;
    auto rest = sfield->GetType();
    if (rest->IsQualified())
        ((SymQualifiedType *)rest)->SetQualifiers(((SymQualifiedType *)rest)->GetQualifiers() | squals);
    else
        rest = new SymQualifiedType(rest, squals);
    res->SetType(rest);
    res->SetValueCategory(structure->GetValueCategory());
    return res;
}

StructureOrUnionMemberAccessByPointerNode *
SemanticAnalyzer::BuildStructureOrUnionMemberAccessByPointerNode(ExprNode *ptr, IdNode *field, std::shared_ptr<Token> arrow)
{
    if (isConstQualified(ptr)) throw InvalidOperandError(arrow, nullptr);
    if (ptr->GetType()->GetTypeKind() == TypeKind::ARRAY)
        ptr->SetType(((SymArray *)unqualify(ptr->GetType()))->ToPointer());
    if (!isPointerType(ptr->GetType())) throw InvalidOperandError(std::move(arrow), ptr->GetType());
    auto ptype = (SymPointer *)unqualify(ptr->GetType());
    if (ptype->GetTarget()->GetTypeKind() != TypeKind::STRUCT) throw BadMemberAccessError(ptype, field);
    auto stype = (SymRecord *)unqualify(ptype->GetTarget());
    if (!stype->IsComplete()) throw BadMemberAccessError(stype); // TODO InvalidUseOfIncompleteTypeError
    SymVariable *sfield;
    if (!(sfield = (SymVariable *)stype->GetFieldsTable()->Find(field->GetName())))
        throw NonexistentMemberError(stype, field);
    auto res = new StructureOrUnionMemberAccessByPointerNode(ptr, field);
    res->SetPosition(arrow);
    res->SetValueCategory(ValueCategory::LVAVLUE);
    auto rest = sfield->GetType();
    uint32_t squals = ptype->GetTarget()->IsQualified() ? ((SymQualifiedType *)ptype->GetTarget())->GetQualifiers() : 0;
    if (rest->IsQualified())
        ((SymQualifiedType *)rest)->SetQualifiers(((SymQualifiedType *)rest)->GetQualifiers() | squals);
    else
        rest = new SymQualifiedType(rest, squals);
    res->SetType(rest);
    return res;
}

ArrayAccessNode *SemanticAnalyzer::BuildArrayAccessNode(ExprNode *array, ExprNode *index)
{
    auto itypeKind = index->GetType()->GetTypeKind();
    if (itypeKind == TypeKind::POINTER || itypeKind == TypeKind::ARRAY)
    {
        auto tmp = array;
        array = index;
        index = tmp;
    }
    if (array->GetType()->GetTypeKind() == TypeKind::ARRAY)
        array->SetType(((SymArray *)array->GetType())->ToPointer());
    if (array->GetType()->GetTypeKind() != TypeKind::POINTER) throw BadIndexingError();
    array->SetValueCategory(ValueCategory::LVAVLUE);
    if (!isIntegerType(index->GetType())) throw BadIndexingError(index);
    auto res = new ArrayAccessNode(array, index);
    res->SetValueCategory(ValueCategory::LVAVLUE);
    res->SetType(((SymPointer *)array->GetType())->GetTarget());
    return res;
}

bool SemanticAnalyzer::isIntegerType(SymType *type)
{
    type = unqualify(type);
    if (type->GetTypeKind() != TypeKind::BUILTIN) return false;
    auto btk = ((SymBuiltInType *)type)->GetBuiltIntTypeKind();
    return btk == BuiltInTypeKind::INT8 || btk == BuiltInTypeKind::UINT8 || btk == BuiltInTypeKind::INT32
           || btk == BuiltInTypeKind::UINT32 || btk == BuiltInTypeKind::INT64 || btk == BuiltInTypeKind::UINT64;
}

FunctionCallNode *SemanticAnalyzer::BuildFunctionCallNode(ExprNode *func, ArgumentExprListNode *args)
{
    if (func->GetType()->GetTypeKind() != TypeKind::FUNCTION) throw BadCalledObjectError();
    auto ftype = (SymFunction *)unqualify(func->GetType());
    size_t i = 0;
    if (args->List().size() != ftype->GetOderedParams().size())
    {
        if (ftype->GetOderedParams().size() != 1 || !isVoidType(ftype->GetOderedParams()[0]->GetType())
            || !args->List().empty())
                throw MismatchNumberOfArguments(func);
    }
    for (auto &arg : args->List())
    {
        if (!arg->GetType()->Equal(ftype->GetOderedParams()[i]->GetType()))
        {
            Convert(&arg, ftype->GetOderedParams()[i]->GetType());
        }
        i++;
    }
    auto res = new FunctionCallNode(func, args);
    res->SetType(ftype->GetReturnType());
    return res;
}

PrefixIncrementNode *SemanticAnalyzer::BuildPrefixIncrementNode(ExprNode *expr, const std::shared_ptr<Token> &op)
{
    CheckIncDecRules(expr, op);
    return new PrefixIncrementNode(expr);
}

void SemanticAnalyzer::performLvalueConversion(ExprNode *expr)
{
    expr->SetValueCategory(ValueCategory::RVALUE);
    if (expr->GetType()->IsQualified())
        ((SymQualifiedType *)expr->GetType())->SetQualifiers(0);
}

PrefixDecrementNode *SemanticAnalyzer::BuildPrefixDecrementNode(ExprNode *expr, const std::shared_ptr<Token> &op)
{
    CheckIncDecRules(expr, op);
    return new PrefixDecrementNode(expr);
}

UnaryOpNode *SemanticAnalyzer::BuildUnaryOpNode(std::shared_ptr<Token> unaryOp, ExprNode *expr)
{
    UnaryOpNode *res = nullptr;
    SymType *t = unqualify(expr->GetType());
    switch (unaryOp->type)
    {
        case TokenType::BITWISE_AND:
            if (expr->GetValueCategory() != ValueCategory::LVAVLUE) throw InvalidOperandError(unaryOp, expr->GetType());
            res = new UnaryOpNode(unaryOp, expr);
            res->SetType(new SymPointer(expr->GetType()));
            return res;
        case TokenType::ASTERIX:
            if (expr->GetType()->GetTypeKind() != TypeKind::POINTER) throw InvalidOperandError(unaryOp, expr->GetType());
            res = new UnaryOpNode(unaryOp, expr);
            res->SetValueCategory(ValueCategory::LVAVLUE);
            res->SetType(((SymPointer *)expr->GetType())->GetTarget());
            return res;
        case TokenType::MINUS:
            if (!isArithmeticType(expr->GetType())) throw InvalidOperandError(unaryOp, expr->GetType());
            if (isUnsignedIntegerType(expr->GetType()))
            {
                // TODO this is wrong conversion, because I probably won't support int64
                expr = new TypeCastNode(new SymBuiltInType(BuiltInTypeKind::INT32), expr);
            }
            res = new UnaryOpNode(unaryOp, expr);
            res->SetType(expr->GetType());
            return res;
        case TokenType::PLUS:
            if (!isArithmeticType(expr->GetType())) throw InvalidOperandError(unaryOp, expr->GetType());
            res = new UnaryOpNode(unaryOp, expr);
            res->SetType(expr->GetType());
            return res;
        case TokenType::BITWISE_NOT:
            if (!isIntegerType(expr->GetType())) throw InvalidOperandError(unaryOp, expr->GetType());
            res = new UnaryOpNode(unaryOp, expr);
            res->SetType(expr->GetType());
            return res;
        case TokenType::LOGIC_NO:
            if (!isScalarType(expr->GetType())) throw InvalidOperandError(unaryOp, expr->GetType());
            res = new UnaryOpNode(unaryOp, expr);
            res->SetType(new SymBuiltInType(BuiltInTypeKind::INT32));
            return res;
    }
}

bool SemanticAnalyzer::isUnsignedIntegerType(SymType *type)
{
    type = unqualify(type);
    if (type->GetTypeKind() != TypeKind::BUILTIN) return false;
    auto btk = ((SymBuiltInType *)type)->GetBuiltIntTypeKind();
    return btk == BuiltInTypeKind::UINT8 || btk == BuiltInTypeKind::UINT16 || btk == BuiltInTypeKind::UINT32 ||
            btk == BuiltInTypeKind::UINT64;
}

bool SemanticAnalyzer::isScalarType(SymType *type)
{
    type = unqualify(type);
    return type->GetTypeKind() == TypeKind::BUILTIN || type->GetTypeKind() == TypeKind::POINTER;
}

BinOpNode *SemanticAnalyzer::BuildBinOpNode(ExprNode *left, ExprNode *right, std::shared_ptr<Token> binOp)
{
    BinOpNode *res = nullptr;
    auto ltype = left->GetType(), rtype = right->GetType();
    switch (binOp->type)
    {
        case TokenType::REMINDER:
            if (!isIntegerType(ltype) || !isIntegerType(rtype)) throw InvalidOperandError(binOp, ltype, rtype);
            ImplicitlyConvert(&left, &right);
            return new BinOpNode(left, right, binOp);
        case TokenType::ASTERIX: case TokenType::FORWARD_SLASH:
            if (!isArithmeticType(ltype) || !isArithmeticType(rtype)) throw InvalidOperandError(binOp, ltype, rtype);
            ImplicitlyConvert(&left, &right);
            return new BinOpNode(left, right, binOp);
        case TokenType::PLUS:
            if (isArithmeticType(ltype) && isArithmeticType(rtype))
            {
                ImplicitlyConvert(&left, &right);
                return new BinOpNode(left, right, binOp);
            }
            if (isPointerType(rtype))
                std::swap(left, right);
            if (!isPointerType(left->GetType()) || !isArithmeticType(right->GetType()))
                throw InvalidOperandError(binOp, ltype, rtype);
            return new BinOpNode(left, right, binOp);
        case TokenType::MINUS:
            if (isArithmeticType(ltype) && isArithmeticType(rtype))
            {
                ImplicitlyConvert(&left, &right);
                return new BinOpNode(left, right, binOp);
            }
            if (isPointerType(ltype) && isPointerType(rtype) && unqualify(rtype)->Equal(unqualify(ltype)))
            {
                res = new BinOpNode(left, right, binOp);
                res->SetType(new SymBuiltInType(BuiltInTypeKind::INT32, 0));
                return res;
            }
            if (isPointerType(ltype) && isIntegerType(rtype))
                return new BinOpNode(left, right, binOp);
            throw InvalidOperandError(binOp, ltype, rtype);
        case TokenType::BITWISE_LSHIFT: case TokenType::BITWISE_RSHIFT:
        case TokenType::BITWISE_AND: case TokenType::BITWISE_XOR: case TokenType::BITWISE_OR:
            if (!isIntegerType(ltype) || !isIntegerType(rtype)) throw InvalidOperandError(binOp, ltype, rtype);
            ImplicitlyConvert(&left, &right);
            return new BinOpNode(left, right, binOp);
        case TokenType::RELOP_LE: case TokenType::RELOP_LT:
        case TokenType::RELOP_GE: case TokenType::RELOP_GT:
            if (isArithmeticType(ltype) && isArithmeticType(rtype))
            {
                ImplicitlyConvert(&left, &right);
                return new BinOpNode(left, right, binOp, new SymBuiltInType(BuiltInTypeKind::INT32, 0));
            }
            if (isPointerType(ltype) && isPointerType(rtype) && ltype->Equal(rtype))
                return new BinOpNode(left, right, binOp, new SymBuiltInType(BuiltInTypeKind::INT32, 0));
            throw InvalidOperandError(binOp, ltype, rtype);
        case TokenType::RELOP_EQ: case TokenType::RELOP_NE:
            if (isArithmeticType(ltype) && isArithmeticType(rtype))
            {
                ImplicitlyConvert(&left, &right);
                return new BinOpNode(left, right, binOp, new SymBuiltInType(BuiltInTypeKind::INT32, 0));
            }
            if (isPointerType(ltype) && isPointerType(rtype))
            {
                 if (ltype->Equal(rtype) || isVoidPointer(ltype) || isVoidPointer(rtype)) // TODO isNullPointerConstant
                    return new BinOpNode(left, right, binOp, new SymBuiltInType(BuiltInTypeKind::INT32, 0));
            }
            throw InvalidOperandError(binOp, ltype, rtype);
        case TokenType::LOGIC_OR: case TokenType::LOGIC_AND:
            if (!isScalarType(ltype) || !isScalarType(rtype)) throw InvalidOperandError(binOp, ltype, rtype);
            return new BinOpNode(left, right, binOp, new SymBuiltInType(BuiltInTypeKind::INT32, 0)); // TODO typepool
    }
    return nullptr;
}

TernaryOperatorNode *
SemanticAnalyzer::BuildTernaryOperatorNode(ExprNode *condition, ExprNode *iftrue, ExprNode *iffalse,
                                           const std::shared_ptr<Token> &question, const std::shared_ptr<Token> &colon)
{
    auto ctype = condition->GetType(), ttype = iftrue->GetType(), ftype = iffalse->GetType();
    if (!isScalarType(ctype)) throw RequiredScalarTypeError(question, ctype);
    if (isArithmeticType(ttype) && isArithmeticType(ftype))
    {
        ImplicitlyConvert(&iftrue, &iffalse);
        return new TernaryOperatorNode(condition, iftrue, iffalse);
    }
    if (isPointerType(ttype) && isPointerType(ftype))
    {
        if (ttype->Equal(ftype) || isVoidPointer(ttype) || isVoidPointer(ftype))
            return new TernaryOperatorNode(condition, iftrue, iffalse);
    }
    if (ttype->Equal(ftype))
        return new TernaryOperatorNode(condition, iftrue, iffalse);
    throw InvalidOperandError(colon, ttype, ftype);
}

AssignmentNode *SemanticAnalyzer::BuildAssignmentNode(ExprNode *left, ExprNode *right, std::shared_ptr<Token> assignmentOp)
{
    if (!isModifiableLvalue(left)) throw RequiredModifiableLvalueError(left);
    auto ltype = left->GetType(), rtype = right->GetType();
    if (assignmentOp->type != TokenType::ASSIGNMENT)
        right = BuildBinOpNode(left, right, extractArithmeticOperationFromAssignmentBy(assignmentOp));  // TODO redo
    left->SetType(ltype);
    if (isArithmeticType(ltype) && isArithmeticType(rtype))
    {
        Convert(&right, ltype);
        return new AssignmentNode(left, right, assignmentOp);
    }
    if (isPointerType(ltype) && isPointerType(rtype))
    {
        if (ltype->Equal(rtype) || isVoidPointer(ltype) || isVoidPointer(rtype))
            return new AssignmentNode(left, right, assignmentOp);
    }
    if (isStructType(ltype) && isStructType(rtype))
    {
        if (!rtype->IsComplete()) throw InvalidUseOfIncompleteType(assignmentOp, rtype);
        if (!ltype->Equal(rtype)) throw InvalidOperandError(assignmentOp, ltype, rtype);
        return new AssignmentNode(left, right, assignmentOp);
    }
    return new AssignmentNode(left, right, assignmentOp);
}

bool SemanticAnalyzer::isModifiableLvalue(ExprNode *expr)
{
    return expr->GetValueCategory() == ValueCategory::LVAVLUE &&
            !isConstQualified(expr) && expr->GetType()->IsComplete() && expr->GetType()->GetTypeKind() != TypeKind::ARRAY;
}

bool SemanticAnalyzer::isConstQualified(ExprNode *expr)
{
    return expr->GetType()->IsQualified() && ((SymQualifiedType *)expr->GetType())->GetQualifiers() & 1U;
}

std::shared_ptr<Token> SemanticAnalyzer::extractArithmeticOperationFromAssignmentBy(const std::shared_ptr<Token> &assignemtBy)
{
    auto pos = assignemtBy->position;
    switch (assignemtBy->type)
    {
        case TokenType::ASSIGNMENT_BY_REMINDER:
            return std::make_shared<Token>(TokenType::REMINDER, pos.row, pos.col, "%");
        case TokenType::ASSIGNMENT_BY_BITWISE_XOR:
            return std::make_shared<Token>(TokenType::BITWISE_XOR, pos.row, pos.col, "^");
        case TokenType::ASSIGNMENT_BY_BITWISE_AND:
            return std::make_shared<Token>(TokenType::BITWISE_AND, pos.row, pos.col, "&");
        case TokenType::ASSIGNMENT_BY_BITWISE_RSHIFT:
            return std::make_shared<Token>(TokenType::BITWISE_RSHIFT, pos.row, pos.col, ">>");
        case TokenType::ASSIGNMENT_BY_BITWISE_LSHIFT:
            return std::make_shared<Token>(TokenType::BITWISE_LSHIFT, pos.row, pos.col, "<<");
        case TokenType::ASSIGNMENT_BY_DIFFERENCE:
            return std::make_shared<Token>(TokenType::MINUS, pos.row, pos.col, "-");
        case TokenType::ASSIGNMENT_BY_SUM:
            return std::make_shared<Token>(TokenType::PLUS, pos.row, pos.col, "+");
        case TokenType::ASSIGNMENT_BY_QUOTIENT:
            return std::make_shared<Token>(TokenType::FORWARD_SLASH, pos.row, pos.col, "/");
        case TokenType::ASSIGNMENT_BY_PRODUCT:
                return std::make_shared<Token>(TokenType::ASTERIX, pos.row, pos.col, "*");
        case TokenType::ASSIGNMENT_BY_BITWISE_OR:
            return std::make_shared<Token>(TokenType::BITWISE_OR, pos.row, pos.col, "|");
        default:
            throw UnknownError();
    }
}

void SemanticAnalyzer::ImplicitlyConvert(ExprNode **left, ExprNode **right)
{
    auto ltype = unqualify((*left)->GetType()), rtype = unqualify((*right)->GetType());
    if (ltype->Equal(rtype)) return;
    if (ltype->GetTypeKind() == TypeKind::BUILTIN)
    {
        auto lbt = (SymBuiltInType *)ltype;
        if (rtype->GetTypeKind() == TypeKind::BUILTIN)
        {
            auto rbt = (SymBuiltInType *)rtype;
            if (lbt->GetBuiltIntTypeKind() > rbt->GetBuiltIntTypeKind())
                *right = new TypeCastNode(lbt, *right);
            else if (lbt->GetBuiltIntTypeKind() < rbt->GetBuiltIntTypeKind())
                *left = new TypeCastNode(rbt, *left);
        }
    }
}

void SemanticAnalyzer::Convert(ExprNode **expr, SymType *type)
{
    auto etype = (*expr)->GetType();
    if (etype->Equal(type)) return;
    if (isArithmeticType(etype) && isArithmeticType(type) || isIntegerType(etype) && isPointerType(type)
            || isPointerType(etype) && isPointerType(type))
    {
        *expr = new TypeCastNode(type, *expr);
        return;
    }
    throw BadTypeConversionError(*expr, type);
}

FunctionDefinitionNode *
SemanticAnalyzer::BuildFunctionDefinitionNode(DeclaratorNode *declarator, CompoundStatement *body)
{
    if (declarator->GetType()->GetTypeKind() != TypeKind::FUNCTION) throw BadCalledObjectError();
    auto f = (SymFunction *)unqualify(declarator->GetType());
    auto sym = scopeTree.Find(declarator->GetId()->GetName());
    SymFunction *fdeclaration = nullptr;
    if (sym)
    {
        if (sym->GetSymbolClass() != SymbolClass::TYPE) throw RedeclarationError(declarator->GetId(), sym);
        fdeclaration = (SymFunction *)unqualify((SymType *)sym);
        if (fdeclaration->GetTypeKind() != TypeKind::FUNCTION) throw RedeclarationError(declarator->GetId(), sym);
        if (!(fdeclaration->Equal(f))) throw DefinitionDoesntMatchDeclarationError();
        if (fdeclaration->Defined()) throw RedifinitionError(declarator->GetId());
        if (!equalQualifiers(f->GetReturnType(), fdeclaration->GetReturnType())) throw ConfclitingTypesError(f);
        fdeclaration->SetOrderedParams(f->GetOderedParams());
        fdeclaration->SetParamsTable(f->GetParamsTable());
        f = fdeclaration; // f = sym? TODO
    }
    f->Define();
    f->SetName(declarator->GetId()->GetName());
    processingFunctions.push(f);
    scopeTree.GetActiveScope()->Insert(declarator->GetId()->GetName(), f);
    scopeTree.SetActiveScope(f->GetParamsTable());
    auto res = new FunctionDefinitionNode(declarator, nullptr);
    return res;
}

SymType *SemanticAnalyzer::unqualify(SymType *type)
{
    return type->IsQualified() ? ((SymQualifiedType *)type)->GetType() : type;
}

bool SemanticAnalyzer::isStructType(SymType *type)
{
    type = unqualify(type);
    return type->GetTypeKind() == TypeKind::STRUCT;
}

TypeCastNode *SemanticAnalyzer::BuildTypeCastNode(SymType *typeName, ExprNode *castExpr)
{
    Convert(&castExpr, typeName);
    return (TypeCastNode *)castExpr;
}

EnumeratorNode *SemanticAnalyzer::BuildEnumeratorNode(IdNode *enumerator, ExprNode *expr)
{
    auto prev = -1;
    Evaluator evaluator;
    if (!expr)
    {
        auto token = std::make_shared<Token>(TokenType::NUM_INT, -1, -1, std::to_string(prev + 1));
        token->intValue = ++prev;
        expr = new IntConstNode(token);
    }
    else
    {
        expr = evaluator.Eval(expr);
        if (!expr) throw RequiredConstantExpressionError(enumerator);
        auto intconst = dynamic_cast<IntConstNode *>(expr);
        if (!intconst) throw RequiredConstantExpressionError(enumerator);
        prev = intconst->GetValue();
    }
    auto symenumerator = scopeTree.GetActiveScope()->Find(enumerator->GetName());
    if (symenumerator) throw RedeclarationError(enumerator, symenumerator);
    scopeTree.GetActiveScope()->Insert(enumerator->GetName(), new SymEnumerator(enumerator->GetName(), expr));
    return new EnumeratorNode(enumerator, expr);
}

EnumSpecifierNode *SemanticAnalyzer::BuildEnumSpecifierNode(IdNode *tag, EnumeratorList *list)
{
    if (!tag) return new EnumSpecifierNode(tag, list);
    auto declaration = scopeTree.GetActiveScope()->Find("enum " + tag->GetName());
    if (declaration)
    {
        auto symenum = dynamic_cast<SymEnum *>(declaration);
        if (!symenum) throw RedeclarationError(tag, declaration);
        if (symenum->Defined() && list) throw RedeclarationError(tag, symenum);
        if (list) symenum->Define();
    }
    else
    {
        auto symenum = new SymEnum(tag);
        if (list) symenum->Define();
        scopeTree.GetActiveScope()->Insert("enum " + tag->GetName(), symenum);
    }
    return new EnumSpecifierNode(tag, list);
}

void SemanticAnalyzer::ProcessFunction(SymType *funcType)
{
    processingFunctions.push(funcType);
}

void SemanticAnalyzer::FinishLastFunctionProcessing()
{
    processingFunctions.pop();
}

ReturnStatementNode *SemanticAnalyzer::BuildReturnStatementNode(std::shared_ptr<Token> statement, ExprNode *expr)
{
    if (processingFunctions.empty()) throw BadJumpStatementError(std::move(statement));
    auto type = processingFunctions.top();
    auto utype = (SymFunction *)unqualify(type);
    if (expr && isVoidType(utype->GetReturnType())) throw VoidFunctionBadReturnError(statement);
    if (expr) Convert(&expr, utype->GetReturnType());
    return new ReturnStatementNode(expr);
}

bool SemanticAnalyzer::isVoidType(SymType *type)
{
    type = unqualify(type);
    return type->GetTypeKind() == TypeKind::BUILTIN &&
            ((SymBuiltInType *)type)->GetBuiltIntTypeKind() == BuiltInTypeKind::VOID;
}

void SemanticAnalyzer::ProcessLoop(IterationStatementNode *loop)
{
    processingLoops.push(loop);
}

void SemanticAnalyzer::FinishLastLoopProcessing()
{
    processingLoops.pop();
}

ContinueStatementNode *SemanticAnalyzer::BuildContinueStatementNode(std::shared_ptr<Token> statement)
{
    if (processingLoops.empty()) throw BadJumpStatementError(std::move(statement));
    return new ContinueStatementNode();
}

BreakStatementNode *SemanticAnalyzer::BuildBreakStatementNode(std::shared_ptr<Token> statement)
{
    if (processingLoops.empty()) throw BadJumpStatementError(std::move(statement));
    return new BreakStatementNode();
}

TypedefIdentifierNode *SemanticAnalyzer::BuildTypedefIdentifierNode(const std::shared_ptr<Token> &id)
{
    auto t = dynamic_cast<SymAlias *>(scopeTree.Find(id->text));
    return new TypedefIdentifierNode(t);
}

bool SemanticAnalyzer::equalQualifiers(SymType *one, SymType *other)
{
    if (one->IsQualified() && other->IsQualified())
    {
        auto q1 = ((SymQualifiedType *)one)->GetQualifiers(), q2 = ((SymQualifiedType *)other)->GetQualifiers();
        return  !(q1 ^ q2);
    }
    return !one->IsQualified() && !other->IsQualified();
}

ExprNode *SemanticAnalyzer::EvaluateArraySizer(ExprNode *expr)
{
    if (!isIntegerType(expr->GetType())) throw RequiredConstantIntegerExpressionError(expr);
    expr = evaluator.Eval(expr);
    auto constIntExpr = dynamic_cast<IntConstNode *>(expr);
    if (!constIntExpr) throw RequiredConstantIntegerExpressionError(expr);
    return expr;
}

void SemanticAnalyzer::analyseInitializerList(SymType *current,
                                              InitializerNode *initializer,
                                              DesignatorNode *designator)
{
    auto simple = dynamic_cast<SimpleInitializer *>(initializer);
    if (simple)
    {
        auto value = simple->GetValue();
        Convert(&value, current);
        if (designator)
            designator->SetValue(new SimpleInitializer(value));
        else
            simple->SetValue(value);
        return;
    }
    int i = 0, size = 0;
    current = unqualify(current);
    auto tp = current->GetTypeKind();
    if (tp != TypeKind::ARRAY && tp != TypeKind::STRUCT) throw "";
    auto array = dynamic_cast<SymArray *>(current);
    auto structure = dynamic_cast<SymRecord *>(current);
    auto list = dynamic_cast<InitializerListNode *>(initializer);
    for (auto value: list->List())
    {
        auto simple = dynamic_cast<SimpleInitializer *>(value);
        if (simple)
        {
            auto expr = simple->GetValue();
            if (array)
            {
                Convert(&expr, array->GetValueType());
                i++;
            }
            else
            {
                structure->GetOrderedFields();
                if (structure->GetOrderedFields().size() <= i) throw ExcessElementsInStructInitializerError();
                Convert(&expr, structure->GetOrderedFields()[i++]->GetType());
            }
            simple->SetValue(expr);
            continue;
        }
        auto il = dynamic_cast<InitializerListNode *>(value);
        if (il)
        {
            if (array)
            {
                analyseInitializerList(array->GetValueType(), il);
                i++;
            }
            else
            {
                if (structure->GetOrderedFields().size() <= i) throw ExcessElementsInStructInitializerError();
                analyseInitializerList(structure->GetOrderedFields()[i++]->GetType(), il);
            }
            continue;
        }
        auto di = dynamic_cast<DesignatedInitializerNode *>(value);
        if (di)
        {
            auto init = di->GetInitializer();
            for (auto designator: di->GetDesignation()->List())
            {
                auto ad = dynamic_cast<ArrayDesignator *>(designator);
                auto sd = dynamic_cast<StructMemberDesignator *>(designator);
                if (sd)
                {
                    if (!structure) throw BadDesignatorError(sd);
                    auto field = (SymVariable *)structure->GetFieldsTable()->Find(sd->GetMemberId()->GetName());
                    if (!field) throw NonexistentMemberError(structure, sd->GetMemberId());
                    analyseInitializerList(unqualify(field->GetType()), init, sd);
                }
                else
                {
                    if (!array) throw BadDesignatorError(ad);
                    analyseInitializerList(array->GetValueType(), init, ad);
                }
            }
        }
    }
}

