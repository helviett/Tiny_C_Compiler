
#include "../includes/converter.h"

void Converter::ImplicityConvert(ExprNode **left, ExprNode **right)
{
    auto ltype = (*left)->GetType(), rtype = (*right)->GetType();
    if (ltype->Equal(rtype)) return;
    if (ltype->GetTypeKind() == TypeKind::BUILTIN)
    {
        auto lbt = (SymBuiltInType *)ltype;
        if (rtype->GetTypeKind() == TypeKind::BUILTIN)
        {
            auto rbt = (SymBuiltInType *)rtype;
            if (lbt->GetBuiltIntTypeKind() > rbt->GetBuiltIntTypeKind())
                *right = new TypeCastNode(new TypeNameNode(lbt), *right);
            else if (lbt->GetBuiltIntTypeKind() < rbt->GetBuiltIntTypeKind())
                *left = new TypeCastNode(new TypeNameNode(lbt), *left);

        }
    }
}

void Converter::Convert(ExprNode **expr, SymType *type)
{
    auto etype = (*expr)->GetType();
    if (etype->GetTypeKind() == TypeKind::BUILTIN)
    {
        auto ebt = (SymBuiltInType *)etype;
        if (type->GetTypeKind() == TypeKind::BUILTIN)
        {
            *expr = new TypeCastNode(new TypeNameNode(type), *expr);
            return;
        }
    }
    throw "";
}
