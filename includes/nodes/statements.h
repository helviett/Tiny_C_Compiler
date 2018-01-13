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
    void Generate(Asm::Assembly *assembly) override = 0;
};

class ExprStatmentNode: StatementNode
{
public:
    explicit ExprStatmentNode(ExprNode *expr);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Generate(Asm::Assembly *assembly) override;
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
    IfStatementNode(ExprNode *expr, StatementNode *then);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Generate(Asm::Assembly *assembly) override;
protected:
    ExprNode *expr;
    StatementNode *then;
};

class IfElseStatementNode: public IfStatementNode
{
public:
    IfElseStatementNode(ExprNode *expr, StatementNode *then, StatementNode *_else);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Generate(Asm::Assembly *assembly) override;
private:
    StatementNode *_else;
};

class JumpStatementNode: public StatementNode
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override = 0;
    void Generate(Asm::Assembly *assembly) override = 0;
};

class GotoStatementNode: public JumpStatementNode
{
public:
    explicit GotoStatementNode(IdNode *id);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Generate(Asm::Assembly *assembly) override;
private:
    IdNode *id;
};

class ContinueStatementNode: public JumpStatementNode
{
public:
    ContinueStatementNode() = default;
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Generate(Asm::Assembly *assembly) override;
};

class BreakStatementNode: public JumpStatementNode
{
public:
    BreakStatementNode() = default;
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Generate(Asm::Assembly *assembly) override;
};

class SymFunction;

class ReturnStatementNode: public JumpStatementNode
{
public:
    explicit ReturnStatementNode(ExprNode *expr, SymFunction *function);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Generate(Asm::Assembly *assembly) override;
private:
    ExprNode *expr;
    SymFunction *function;
};

class IterationStatementNode: public StatementNode
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override = 0;
    void SetBody(StatementNode *body);
    void Generate(Asm::Assembly *assembly) override = 0;
protected:
    StatementNode *body;
};

class WhileStatementNode: public IterationStatementNode
{
public:
    WhileStatementNode(ExprNode *condition, StatementNode *body);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Generate(Asm::Assembly *assembly) override;
private:
    ExprNode *condition{};
};

class DoWhileStatementNode: public IterationStatementNode
{
public:
    DoWhileStatementNode(ExprNode *condition, StatementNode *body);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void SetCondition(ExprNode *condition);
    void Generate(Asm::Assembly *assembly) override;
private:
    ExprNode *condition;
};

class ForStatementNode: public IterationStatementNode
{
public:
    ForStatementNode(ExprStatmentNode *init, ExprStatmentNode *condition,
                     ExprNode *iteration, StatementNode *body);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Generate(Asm::Assembly *assembly) override;
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
    void Generate(Asm::Assembly *assembly) override;
private:
    IdNode *labelName{};
    StatementNode *statement;
};

class BlockItemListNode;

class CompoundStatement: public StatementNode
{
public:
    explicit CompoundStatement(BlockItemListNode *blockItemList);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Generate(Asm::Assembly *assembly) override;
private:
    BlockItemListNode *blockItemList;
};

class BlockItemNode: public Node
{
public:
    explicit BlockItemNode(Node *declOrStatement);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Generate(Asm::Assembly *assembly) override;
private:
    Node *declOrStatement;
};

class BlockItemListNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    void Add(BlockItemNode *blockItem);
    uint64_t Size();
    void Generate(Asm::Assembly *assembly) override;
private:
    std::list<BlockItemNode *> list;
};

#endif //TINY_C_COMPILER_STATEMENTS_H
