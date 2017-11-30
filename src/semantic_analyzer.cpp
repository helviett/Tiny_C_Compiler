#include "../includes/semantic_analyzer.h"

IdNode *SemanticAnalyzer::BuildIdNode(std::shared_ptr<Token> token)
{
    auto symbol = scopeTree.Find(token->stringValue);
    if (!symbol) throw "";
    if (symbol->GetSymbolClass() == SymbolClass::UNDEFINED) throw "";
    if (symbol->GetSymbolClass() == SymbolClass::VARIABLE)
    {

        auto id = new IdNode(token, ((SymVariable *)symbol)->GetType());
        switch (id->GetType()->GetTypeKind())
        {
            case TypeKind::ARRAY: case TypeKind::FUNCTION :case TypeKind::STRUCT:
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
        }
    }
    throw "";
}

StructSpecifierNode *SemanticAnalyzer::BuildStructSpecifierNode(IdNode *tag,
                                                                StructDeclarationListNode *structDeclarationList)
{
    auto rt = TypeBuilder::Build(structDeclarationList, tag);
    rt->SetTag(tag);
    Symbol *s = nullptr;
    if (tag)
    {
        s = scopeTree.GetActiveScope()->Find("struct " + tag->GetName());
        if (s)
        {
            if (s->GetSymbolClass() != SymbolClass::TYPE) throw "";
            if (((SymType *)s)->GetTypeKind() != TypeKind::STRUCT) throw "";
            auto record = (SymRecord *)s;
            if (!record->GetOrderedFields().empty()) throw "";
            delete record;
        }
        rt->SetName("struct " + tag->GetName());
        scopeTree.GetActiveScope()->Insert(rt->GetName(), rt);
    }
    return new StructSpecifierNode(rt);
}

ScopeTree *SemanticAnalyzer::GetScopeTree()
{
    return &scopeTree;
}

PostfixDecrementNode *SemanticAnalyzer::BuildPostfixDecrementNode(ExprNode *expr)
{
    CheckIncDecRules(expr);
    return new PostfixDecrementNode(expr);
}

PostfixIncrementNode *SemanticAnalyzer::BuildPostfixIncrementNode(ExprNode *expr)
{
    CheckIncDecRules(expr);
    return new PostfixIncrementNode(expr);
}

void SemanticAnalyzer::CheckIncDecRules(ExprNode *expr)
{
    static std::vector<TypeKind> improperKinds = {};
    if (expr->GetValueCategory() == ValueCategory::RVALUE) throw "";
    auto type = expr->GetType();
    if (!isArithmeticType(type) && !isPointerType(type) || isVoidPointer(type)) throw "";
}

bool SemanticAnalyzer::isArithmeticType(SymType *type)
{
    if (type->GetTypeKind() != TypeKind::BUILTIN) return false;
    auto bitk = ((SymBuiltInType *)type)->GetBuiltIntTypeKind();
    return bitk != BuiltInTypeKind::VOID;
}

bool SemanticAnalyzer::isPointerType(SymType *type)
{
    if (type->GetTypeKind() != TypeKind::POINTER) return false;
    auto bitk = ((SymPointer *)type)->GetTarget();
    return true;
}

InitDeclaratorNode *SemanticAnalyzer::BuildInitDeclaratorNode(DeclaratorNode *declarator, InitializerNode *initializer)
{
    if (scopeTree.GetActiveScope()->Find(declarator->GetId()->GetName())) throw "";
    auto t = declarator->GetType();
    if (t->GetTypeKind() == TypeKind::FUNCTION)
        scopeTree.GetActiveScope()->Insert(declarator->GetId()->GetName(), t);
    else
        scopeTree.GetActiveScope()->Insert(declarator->GetId()->GetName(),
                                           new SymVariable(declarator->GetId()->GetName(), declarator->GetType()));
    // TODO initializer type check
    return new InitDeclaratorNode(declarator, initializer);
}

bool SemanticAnalyzer::isVoidPointer(SymType *type)
{
    if (type->GetTypeKind() != TypeKind::POINTER) return false;
    auto target = ((SymPointer *)type)->GetTarget();
    return target->GetTypeKind() == TypeKind::BUILTIN &&
            ((SymBuiltInType *)target)->GetBuiltIntTypeKind() == BuiltInTypeKind::VOID;
}

StructureOrUnionMemberAccessNode *
SemanticAnalyzer::BuildStructureOrUnionMemberAccessNode(ExprNode *structure, IdNode *field)
{
    auto type = structure->GetType();
    if (type->GetTypeKind() != TypeKind::STRUCT) throw "";
    auto stype = (SymRecord *)type;
    SymVariable *sfield;
    if (!(sfield = (SymVariable *)stype->GetFieldsTable()->Find(field->GetName()))) throw "";
    auto res = new StructureOrUnionMemberAccessNode(structure, field);
    res->SetType(sfield->GetType());
    res->SetValueCategory(structure->GetValueCategory());
    return res;
}

StructureOrUnionMemberAccessByPointerNode *
SemanticAnalyzer::BuildStructureOrUnionMemberAccessByPointerNode(ExprNode *ptr, IdNode *field)
{
    if (ptr->GetType()->GetTypeKind() == TypeKind::ARRAY)
        ptr->SetType(((SymArray *)ptr->GetType())->ToPointer());

    if (!isPointerType(ptr->GetType())) throw "";
    auto ptype = (SymPointer *)ptr->GetType();
    if (ptype->GetTarget()->GetTypeKind() != TypeKind::STRUCT) throw "";
    auto stype = (SymRecord *)ptype->GetTarget();
    SymVariable *sfield;
    if (!(sfield = (SymVariable *)stype->GetFieldsTable()->Find(field->GetName()))) throw "";
    auto res = new StructureOrUnionMemberAccessByPointerNode(ptr, field);
    res->SetValueCategory(ValueCategory::LVAVLUE);
    auto rest = sfield->GetType();
    rest->SetTypeQualifiers(rest->GetTypeQualifiers() | stype->GetTypeQualifiers());
    res->SetType(sfield->GetType());
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
    if (array->GetType()->GetTypeKind() != TypeKind::POINTER) throw "";
    array->SetValueCategory(ValueCategory::LVAVLUE); // ?
    if (!isIntegerType(index->GetType())) throw "";
    auto res = new ArrayAccessNode(array, index);
    res->SetValueCategory(ValueCategory::LVAVLUE);
    res->SetType(((SymPointer *)array->GetType())->GetTarget());
    return res;
}

bool SemanticAnalyzer::isIntegerType(SymType *type)
{
    if (type->GetTypeKind() != TypeKind::BUILTIN) return false;
    auto btk = ((SymBuiltInType *)type)->GetBuiltIntTypeKind();
    return btk == BuiltInTypeKind::INT8 || btk == BuiltInTypeKind::UINT8 || btk == BuiltInTypeKind::INT32
           || btk == BuiltInTypeKind::UINT32 || btk == BuiltInTypeKind::INT64 || btk == BuiltInTypeKind::UINT64;
}

FunctionCallNode *SemanticAnalyzer::BuildFunctionCallNode(ExprNode *func, ArgumentExprListNode *args)
{
    if (func->GetType()->GetTypeKind() != TypeKind::FUNCTION) throw "";
    auto ftype = (SymFunction *)func->GetType();
    size_t i = 0;
    if (args->List().size() != ftype->GetOderedParams().size()) throw "";
    for (auto arg = args->List().begin(); arg != args->List().end(); arg++)
    {
        // TODO TypeConversions
        if (!(*arg)->GetType()->Equal(ftype->GetOderedParams()[i]->GetType()))
        {
            Converter::Convert(&(*arg), ftype->GetOderedParams()[i]->GetType());
        }
        i++;
    }
    auto res = new FunctionCallNode(func, args);
    res->SetType(ftype->GetReturnType());
    return res;
}

PrefixIncrementNode *SemanticAnalyzer::BuildPrefixIncrementNode(ExprNode *expr)
{
    CheckIncDecRules(expr);
    return new PrefixIncrementNode(expr);
}

void SemanticAnalyzer::performLvalueConversion(ExprNode *expr)
{
    expr->SetValueCategory(ValueCategory::RVALUE);
    expr->GetType()->SetTypeQualifiers(0);
}

PrefixDecrementNode *SemanticAnalyzer::BuildPrefixDecrementNode(ExprNode *expr)
{
    CheckIncDecRules(expr);
    return new PrefixDecrementNode(expr);
}

UnaryOpNode *SemanticAnalyzer::BuildUnaryOpNode(std::shared_ptr<Token> unaryOp, ExprNode *expr)
{
    UnaryOpNode *res = nullptr;
    switch (unaryOp->type)
    {
        case TokenType::LOGIC_AND:
            if (expr->GetValueCategory() != ValueCategory::LVAVLUE) throw "";
            res = new UnaryOpNode(unaryOp, expr);
            res->SetType(new SymPointer(expr->GetType()));
            return res;
        case TokenType::ASTERIX:
            if (expr->GetType()->GetTypeKind() != TypeKind::POINTER) throw "";
            res = new UnaryOpNode(unaryOp, expr);
            res->SetValueCategory(ValueCategory::LVAVLUE);
            res->SetType(((SymPointer *)expr->GetType())->GetTarget());
            return res;
        case TokenType::MINUS:
            if (!isArithmeticType(expr->GetType())) throw "";
            if (isUnsignedIntegerType(expr->GetType()))
            {
                // TODO this is wrong conversion, because I probably won't support int64
                expr = new TypeCastNode(new TypeNameNode(new SymBuiltInType(BuiltInTypeKind::INT32, 0)), expr);
            }
            res = new UnaryOpNode(unaryOp, expr);
            res->SetType(expr->GetType());
            return res;
        case TokenType::PLUS:
            if (!isArithmeticType(expr->GetType())) throw "";
            res = new UnaryOpNode(unaryOp, expr);
            res->SetType(expr->GetType());
            return res;
        case TokenType::BITWISE_NOT:
            if (!isIntegerType(expr->GetType())) throw "";
            res = new UnaryOpNode(unaryOp, expr);
            res->SetType(expr->GetType());
            return res;
        case TokenType::LOGIC_NO:
            if (!isScalarType(expr->GetType())) throw "";
            res = new UnaryOpNode(unaryOp, expr);
            res->SetType(new SymBuiltInType(BuiltInTypeKind::INT32, 0));
            return res;
    }
}

bool SemanticAnalyzer::isUnsignedIntegerType(SymType *type)
{
    if (type->GetTypeKind() != TypeKind::BUILTIN) throw "";
    auto btk = ((SymBuiltInType *)type)->GetBuiltIntTypeKind();
    return btk == BuiltInTypeKind::UINT8 || btk == BuiltInTypeKind::UINT16 || btk == BuiltInTypeKind::UINT32 ||
            btk == BuiltInTypeKind::UINT64;
}

bool SemanticAnalyzer::isScalarType(SymType *type)
{
    return type->GetTypeKind() == TypeKind::BUILTIN || type->GetTypeKind() == TypeKind::POINTER;
}

BinOpNode *SemanticAnalyzer::BuildBinOpNode(ExprNode *left, ExprNode *right, std::shared_ptr<Token> binOp)
{
    BinOpNode *res = nullptr;
    auto ltype = left->GetType(), rtype = right->GetType();
    switch (binOp->type)
    {
        case TokenType::REMINDER:
            if (!isIntegerType(ltype) || !isIntegerType(rtype)) throw "";
            Converter::ImplicityConvert(&left, &right);
            return new BinOpNode(left, right, binOp);
        case TokenType::ASTERIX: case TokenType::FORWARD_SLASH:
            if (!isArithmeticType(ltype) || !isArithmeticType(rtype)) throw "";
            Converter::ImplicityConvert(&left, &right);
            return new BinOpNode(left, right, binOp);
        case TokenType::PLUS:
            if (isArithmeticType(ltype) || isArithmeticType(rtype))
            {
                Converter::ImplicityConvert(&left, &right);
                return new BinOpNode(left, right, binOp);
            }
            if (isPointerType(rtype))
            {
                left->SetType(rtype); // TODO std::swap ?
                right->SetType(ltype);
            }
            if (!isPointerType(left->GetType()) || !isArithmeticType(right->GetType())) throw "";
            return new BinOpNode(left, right, binOp);
        case TokenType::MINUS:
            if (isArithmeticType(ltype) && isArithmeticType(rtype))
            {
                Converter::ImplicityConvert(&left, &right);
                return new BinOpNode(left, right, binOp);
            }
            if (isPointerType(ltype) && isPointerType(rtype) && rtype->Equal(ltype))
            {
                res = new BinOpNode(left, right, binOp);
                res->SetType(new SymBuiltInType(BuiltInTypeKind::INT32, 0));
                return res;
            }
            if (isPointerType(ltype) && isIntegerType(rtype))
                return new BinOpNode(left, right, binOp);
            throw "";
    }
    return nullptr;
}
