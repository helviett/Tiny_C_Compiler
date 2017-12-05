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
    IntConstNode *ileft = dynamic_cast<IntConstNode *>(left), *iright = dynamic_cast<IntConstNode *>(right);
    FloatConstNode *fleft = dynamic_cast<FloatConstNode *>(left), *fright = dynamic_cast<FloatConstNode *>(right);
    std::shared_ptr<Token> t;
    double value = 0;
    switch (node->GetOperation()->type)
    {
        case TokenType::PLUS:
            if (ileft && iright)
            {
                value = ileft->GetValue()->intValue + iright->GetValue()->intValue;
                t = std::make_shared<Token>(TokenType::NUM_INT, -1, -1, std::to_string((int)value));
                t->intValue = value;
                return new IntConstNode(t);
            }

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
