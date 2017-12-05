//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_STATEMENTS_H
#define TINY_C_COMPILER_STATEMENTS_H

#include "node.h"
#include "expressions.h"

class StatementNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override = 0;
};

class ExprStatmentNode: StatementNode
{
public:
    explicit ExprStatmentNode(ExprNode *expr): expr(expr) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    ExprNode *expr;
};

class SelectionStatementNode: public StatementNode
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override = 0;
};

class IfStatementNode: public SelectionStatementNode
{
public:
    IfStatementNode() = default;
    IfStatementNode(ExprNode *expr, StatementNode *then): expr(expr), then(then) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
protected:
    ExprNode *expr;
    StatementNode *then;
};

class IfElseStatementNode: public IfStatementNode
{
public:
    IfElseStatementNode(ExprNode *expr, StatementNode *then, StatementNode *_else):
            IfStatementNode(expr, then), _else(_else) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    StatementNode *_else;
};

class JumpStatementNode: public StatementNode
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override = 0;
};

class GotoStatementNode: public JumpStatementNode
{
public:
    explicit GotoStatementNode(IdNode *id): id(id) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    IdNode *id;
};

class ContinueStatementNode: public JumpStatementNode
{
public:
    ContinueStatementNode() = default;
    void Print(std::ostream &os, std::string ident, bool isTail) override;
};

class BreakStatementNode: public JumpStatementNode
{
public:
    BreakStatementNode() = default;
    void Print(std::ostream &os, std::string ident, bool isTail) override;
};

class ReturnStatementNode: public JumpStatementNode
{
public:
    explicit ReturnStatementNode(ExprNode *expr): expr(expr) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    ExprNode *expr;
};

class IterationStatementNode: public StatementNode
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override = 0;
    void SetBody(StatementNode *body);
protected:
    StatementNode *body;
};

class WhileStatementNode: public IterationStatementNode
{
public:
    WhileStatementNode(ExprNode *condition, StatementNode *body);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    ExprNode *condition{};
};

class DoWhileStatementNode: public IterationStatementNode
{
public:
    DoWhileStatementNode(ExprNode *condition, StatementNode *body);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void SetCondition(ExprNode *condition);
private:
    ExprNode *condition;
};

class ForStatementNode: public IterationStatementNode
{
public:
    ForStatementNode(ExprStatmentNode *init, ExprStatmentNode *condition,
                     ExprNode *iteration, StatementNode *body);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    ExprStatmentNode *init, *condition;
    ExprNode *iteration{};
};

class LabeledStatementNode: public StatementNode
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override = 0;
};

class LabelStatementNode: public LabeledStatementNode
{
public:
    LabelStatementNode(IdNode *labelName, StatementNode *statement);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    IdNode *labelName{};
    StatementNode *statement;
};

class BlockItemListNode;

class CompoundStatement: public StatementNode
{
public:
    explicit CompoundStatement(BlockItemListNode *blockItemList): blockItemList(blockItemList) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    BlockItemListNode *blockItemList;
};

class BlockItemNode: public Node
{
public:
    explicit BlockItemNode(Node *declOrStatement);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    Node *declOrStatement;
};

class BlockItemListNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(BlockItemNode *blockItem);
    uint64_t Size();
private:
    std::list<BlockItemNode *> list;
};

#endif //TINY_C_COMPILER_STATEMENTS_H
