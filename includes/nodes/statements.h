//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_STATEMENTS_H
#define TINY_C_COMPILER_STATEMENTS_H

#include "node.h"
#include "expressions.h"

//statement ::= labeled-statement | compound-statement
//              | expression-statement | selection-statement
//              | iteration-statement | jump-statement

class StatementNode: public Node
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override = 0;
};

//expression-statement ::= `expr ;

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

//jump-statement ::= goto id ;
//                  | continue ;
//                  | break ;
//                  | return `expr ;

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
};

class WhileStatementNode: public IterationStatementNode
{
public:
    WhileStatementNode(ExprNode *condition, StatementNode *body): condition(condition), body(body) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    ExprNode *condition;
    StatementNode *body;
};

class DoWhileStatementNode: public IterationStatementNode
{
public:
    DoWhileStatementNode(ExprNode *condition, StatementNode *body): condition(condition), body(body) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    ExprNode *condition;
    StatementNode *body;
};

class ForStatementNode: public IterationStatementNode
{
public:
    ForStatementNode(ExprStatmentNode *init, ExprStatmentNode *condition,
                     ExprNode *iteration, StatementNode *body):
            init(init), condition(condition), iteration(iteration), body(body) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    ExprStatmentNode *init, *condition;
    ExprNode *iteration;
    StatementNode *body;
};

//labeled-statement ::= id : statement

class LabeledStatementNode: public StatementNode
{
public:
    void Print(std::ostream &os, std::string ident, bool isTail) override = 0;
};

class LabelStatementNode: public LabeledStatementNode
{
public:
    LabelStatementNode(IdNode *labelName, StatementNode *statement): labelName(labelName), statement(statement) {}
    void Print(std::ostream &os, std::string ident, bool isTail) override;
private:
    IdNode *labelName;
    StatementNode *statement;
};

//compound-statement ::= {`block-item-list}

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
    explicit BlockItemNode(Node *declOrStatement): declOrStatement(declOrStatement) {}
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
