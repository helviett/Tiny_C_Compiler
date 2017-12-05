//
// Created by keltar on 12/6/17.
//

#ifndef TINY_C_COMPILER_EVALUATOR_H
#define TINY_C_COMPILER_EVALUATOR_H

#include "nodes/expressions.h"
#include "nodes.h"

class Evaluator
{
public:
    Evaluator() = default;
    ExprNode *Eval(ExprNode *node);
    ExprNode *Eval(PostfixDecrementNode *node);
    ExprNode *Eval(PrefixDecrementNode *node);
    ExprNode *Eval(PostfixIncrementNode *node);
    ExprNode *Eval(PrefixIncrementNode *node);
    ExprNode *Eval(ArrayAccessNode *node);
    ExprNode *Eval(BinOpNode *node);
    ExprNode *Eval(UnaryOpNode *node);
    ExprNode *Eval(SizeofExprNode *node);
    ExprNode *Eval(SizeofTypeNameNode *node);
    ExprNode *Eval(AssignmentNode *node);
    ExprNode *Eval(IntConstNode *node);
    ExprNode *Eval(FloatConstNode *node);
    ExprNode *Eval(TypeCastNode *node);
    ExprNode *Eval(EnumeratorNode *node);
};

#endif //TINY_C_COMPILER_EVALUATOR_H
