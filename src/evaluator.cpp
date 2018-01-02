#include <errors/tcc_exceptions.h>
#include "../includes/evaluator.h"

ExprNode *Evaluator::Eval(ExprNode *node)
{
    return node->Eval(this);
}

ExprNode *Evaluator::Eval(PostfixDecrementNode *node)
{
    return nullptr;
}

ExprNode *Evaluator::Eval(PrefixDecrementNode *node)
{
    return nullptr;
}

ExprNode *Evaluator::Eval(PostfixIncrementNode *node)
{
    return nullptr;
}

ExprNode *Evaluator::Eval(PrefixIncrementNode *node)
{
    return nullptr;
}

ExprNode *Evaluator::Eval(ArrayAccessNode *node)
{
    return nullptr;
}

ExprNode *Evaluator::Eval(BinOpNode *node)
{
    auto left = Eval(node->Left()), right = Eval(node->Right());
    if (!left || !right) return nullptr;
    auto ileft = dynamic_cast<IntConstNode *>(left), iright = dynamic_cast<IntConstNode *>(right);
    auto fleft = dynamic_cast<FloatConstNode *>(left), fright = dynamic_cast<FloatConstNode *>(right);
    std::shared_ptr<Token> t;
    double value = 0;
#define EVAL(OP)\
    if (ileft && iright)\
    {\
        return new IntConstNode(ileft->GetValue() OP iright->GetValue());\
    }

    switch (node->GetOperation()->type)
    {
        case TokenType::PLUS:
            if (ileft && iright)
                return new IntConstNode(ileft->GetValue() + iright->GetValue());
        case TokenType::MINUS:
            if (ileft && iright)
                return new IntConstNode(ileft->GetValue() - iright->GetValue());
        case TokenType::ASTERIX:
            if (ileft && iright)
                return new IntConstNode(ileft->GetValue() * iright->GetValue());
        case TokenType::BITWISE_AND:
            if (ileft && iright)
                return new IntConstNode(ileft->GetValue() * iright->GetValue());
        case TokenType::BITWISE_OR:
            if (ileft && iright)
                return new IntConstNode(ileft->GetValue() | iright->GetValue());
        case TokenType::BITWISE_XOR:
            if (ileft && iright)
                return new IntConstNode(ileft->GetValue() ^ iright->GetValue());
        case TokenType::BITWISE_LSHIFT:
            if (ileft && iright)
                return new IntConstNode(ileft->GetValue() | iright->GetValue());
        case TokenType::BITWISE_RSHIFT:
            if (ileft && iright)
                return new IntConstNode(ileft->GetValue() | iright->GetValue());


    }
    return nullptr;
}

ExprNode *Evaluator::Eval(UnaryOpNode *node)
{
    return nullptr;
}

ExprNode *Evaluator::Eval(SizeofExprNode *node)
{
    return nullptr;
}

ExprNode *Evaluator::Eval(SizeofTypeNameNode *node)
{
    return nullptr;
}

ExprNode *Evaluator::Eval(AssignmentNode *node)
{
    return nullptr;
}

ExprNode *Evaluator::Eval(IntConstNode *node)
{
    return node;
}

ExprNode *Evaluator::Eval(FloatConstNode *node)
{
    return node;
}

ExprNode *Evaluator::Eval(TypeCastNode *node)
{
    return nullptr;
}

ExprNode *Evaluator::Eval(EnumeratorNode *node)
{
    return node->GetValue();
}
