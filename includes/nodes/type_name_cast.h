//
// Created by keltar on 11/4/17.
//

#ifndef TINY_C_COMPILER_TYPE_NAME_CAST_H
#define TINY_C_COMPILER_TYPE_NAME_CAST_H

#include "node.h"
#include "declaration_specifier_nodes.h"
#include "decls.h"

struct BuiltInTypePairHash
{
    size_t operator()(const std::pair<BuiltInTypeKind, BuiltInTypeKind> &p) const
    {
        return (size_t)p.first + 2 * (size_t)p.second;
    }
};

static std::unordered_map<std::pair<BuiltInTypeKind, BuiltInTypeKind>, std::function<void(Asm::Assembly *)>, BuiltInTypePairHash>
        BuiltInTypeConversions =
{
        {std::make_pair(BuiltInTypeKind::INT32, BuiltInTypeKind::INT32), [](Asm::Assembly *assembly) {}},
        {std::make_pair(BuiltInTypeKind::INT32, BuiltInTypeKind::FLOAT),
                [](Asm::Assembly *assembly)
                {
                    assembly->AddCommand(Asm::CommandName::FILD, Asm::MakeAddress(Asm::Registers[Asm::Register::ESP]),
                                         Asm::CommandSuffix::L);
                    assembly->AddCommand(Asm::CommandName::FSTP,Asm::MakeAddress(Asm::Registers[Asm::Register::ESP]),
                                         Asm::CommandSuffix::S);
                }},
        {std::make_pair(BuiltInTypeKind::FLOAT, BuiltInTypeKind::DOUBLE),
                [](Asm::Assembly *assembly)
                {
                    assembly->AddCommand(Asm::CommandName::FILD, Asm::MakeAddress(Asm::Registers[Asm::Register::ESP]),
                                         Asm::CommandSuffix::S);
                    assembly->AddCommand(Asm::CommandName::PUSH, Asm::Register::EAX, Asm::CommandSuffix::L);
                    assembly->AddCommand(Asm::CommandName::FSTP,Asm::MakeAddress(Asm::Registers[Asm::Register::ESP]),
                                         Asm::CommandSuffix::L);
                }},
};

class TypeCastNode: public ExprNode
{
public:
    TypeCastNode(SymType *typeName, ExprNode *castExpr);
    void Print(std::ostream &os, std::string ident, bool isTail) override;
    ExprNode *Eval(Evaluator *evaluator) override;
    void Generate(Asm::Assembly *assembly) override;
private:
    SymType *castType;
    ExprNode *castExpr;
};


#endif //TINY_C_COMPILER_TYPE_NAME_CAST_H
