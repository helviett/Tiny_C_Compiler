//
// Created by keltar on 10/14/17.
//

#include <gmpxx.h>
#include "../includes/nodes.h"
#include "../includes/evaluator.h"

void IntConstNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << value << std::endl;
}

IntConstNode::IntConstNode(std::shared_ptr<Token> token)
{
    if (token->type != TokenType::NUM_INT) throw "";
    type = new SymBuiltInType(BuiltInTypeKind::INT32, 0);
    position = token->position;
    value = token->intValue;
}

ExprNode *IntConstNode::Eval(Evaluator *evaluator)
{
    return evaluator->Eval(this);
}

int32_t IntConstNode::GetValue() const
{
    return value;
}

IntConstNode::IntConstNode(int32_t value)
{
    this->value = value;
    type = new SymBuiltInType(BuiltInTypeKind::INT32);
}

void IntConstNode::Generate(Asm::Assembly *assembly)
{
    assembly->TextSection().AddCommand(Asm::CommandName::PUSH, (ConstNode *)this, Asm::CommandSuffix::L);
    // TODO
}

void FloatConstNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << value << std::endl;
}

FloatConstNode::FloatConstNode(std::shared_ptr<Token> token)
{
    if (token->type != TokenType::NUM_FLOAT) throw "";
    type = new SymBuiltInType(BuiltInTypeKind::FLOAT, 0);
    position = token->position;
    value = token->floatValue;
}

ExprNode *FloatConstNode::Eval(Evaluator *evaluator)
{
    return evaluator->Eval(this);
}

float FloatConstNode::GetValue() const
{
    return value;
}

void FloatConstNode::Generate(Asm::Assembly *assembly)
{
    assembly->TextSection().AddCommand(Asm::CommandName::PUSH, (ConstNode *)this, Asm::CommandSuffix::L);
    // TODO
}

FloatConstNode::FloatConstNode(float value)
{
    this->value = value;
}

void IdNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << token->text << std::endl;
}

IdNode::IdNode(std::shared_ptr<Token> token): token(token)
{
    if (token->type != TokenType::ID) throw "";
    category = ValueCategory::LVAVLUE;
    position = token->position;
}

std::string IdNode::GetName() const
{
    return token->stringValue;
}

IdNode::IdNode(std::shared_ptr<Token> token, SymType *type): IdNode(token)
{
    this->type = type;
    position = token->position;
}

ExprNode *IdNode::Eval(Evaluator *evaluator)
{
    return evaluator->Eval(this);
}

void IdNode::Generate(Asm::Assembly *assembly)
{
    using namespace Asm;
    Section &s = assembly->TextSection();
    if (variable)
    {
        auto vt = variable->GetType()->GetUnqualified();
        if (vt->GetTypeKind() == TypeKind::STRUCT && category == ValueCategory::RVALUE)
        {
            s.AddCommand(CommandName::LEA, MakeAddress(variable->GetOffset(), Register::EBP),
                         Register::EAX, CommandSuffix::L);
            for (auto field: reinterpret_cast<SymRecord *>(vt)->GetOrderedFields())
            {
                auto ft = field->GetType()->GetUnqualified();
                if (ft->GetTypeKind() == TypeKind::ARRAY)
                    arrayGenerate(assembly, field->GetOffset(), reinterpret_cast<SymArray *>(ft));
                else if (ft->GetTypeKind() == TypeKind::STRUCT)
                    structureGenerate(assembly, field->GetOffset(), reinterpret_cast<SymRecord *>(ft));
                else
                    s.AddCommand(CommandName::PUSH, MakeAddress(field->GetOffset(), Register::EAX), CommandSuffix::L);
            }
            return;
        }
        if (GetValueCategory() == ValueCategory::LVAVLUE || variable->GetType()->GetTypeKind() == TypeKind::ARRAY)
            s.AddCommand(CommandName::LEA, MakeAddress(variable->GetOffset(), Register::EBP),
                         Register::EAX, CommandSuffix::L);
        else
            s.AddCommand(CommandName::MOV, MakeAddress(variable->GetOffset(), Register::EBP),
                         Register::EAX, CommandSuffix::L);
        s.AddCommand(CommandName::PUSH, Register::EAX, CommandSuffix::L);
    }
}

void IdNode::SetVariable(SymVariable *variable)
{
    this->variable = variable;
}

SymVariable *IdNode::GetVariable() const
{
    return variable;
}

void IdNode::arrayGenerate(Asm::Assembly *assembly, int32_t offset, SymArray *array)
{
    using namespace Asm;
    Section &s = assembly->TextSection();
    auto n =  array->NumberOfElements();
    auto vt = array->GetValueType()->GetUnqualified();
    auto elemSize = vt->Size();
    for (int i = n - 1; i >= 0; i--)
    {
        if (vt->GetTypeKind() == TypeKind::ARRAY)
            arrayGenerate(assembly, offset + i * elemSize, reinterpret_cast<SymArray *>(vt));
        else if (vt->GetTypeKind() == TypeKind::STRUCT)
            structureGenerate(assembly, offset + i * elemSize, reinterpret_cast<SymRecord *>(vt));
        else
            s.AddCommand(CommandName::PUSH, MakeAddress(offset + i * elemSize, Register::EAX), CommandSuffix::L);
    }
}

void IdNode::structureGenerate(Asm::Assembly *assembly, int32_t offset, SymRecord *record)
{
    using namespace Asm;
    Section &s = assembly->TextSection();
    auto &fields = record->GetOrderedFields();
    auto n =  fields.size();
    for (int i = static_cast<int>(n - 1); i >= 0; i--)
    {
        auto ft = fields[i]->GetType()->GetUnqualified();
        if (ft->GetTypeKind() == TypeKind::ARRAY)
            arrayGenerate(assembly, offset + ft->Size(), reinterpret_cast<SymArray *>(ft));
        else if (ft->GetTypeKind() == TypeKind::STRUCT)
            structureGenerate(assembly, offset + ft->Size(), reinterpret_cast<SymRecord *>(ft));
        else
            s.AddCommand(CommandName::PUSH, MakeAddress(offset + ft->Size(), Register::EAX), CommandSuffix::L);
    }
}

void StringLiteralNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << token->text << std::endl;
}

StringLiteralNode::StringLiteralNode(std::shared_ptr<Token> token): token(token)
{
    if (token->type != TokenType::STRING) throw "";
    position = token->position;
    this->type = new SymPointer(new SymBuiltInType(BuiltInTypeKind::INT8));
}

ExprNode *StringLiteralNode::Eval(Evaluator *evaluator)
{
    return evaluator->Eval(this);
}

void StringLiteralNode::Generate(Asm::Assembly *assembly)
{
    address = assembly->NextLabel();
    assembly->DataSection().AddLabel(address);
    assembly->DataSection().AddDirective(new Asm::AsmStringDirective(token->text));
}

Asm::AsmLabel *StringLiteralNode::GetAddress() const
{
    return address;
}

void PostfixIncrementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "`++" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    expr->Print(os, indent, true);
}

PostfixIncrementNode::PostfixIncrementNode(ExprNode *node) : expr(node)
{
    this->type = node->GetType();
}

ExprNode * PostfixIncrementNode::Eval(Evaluator *evaluator)
{
    evaluator->Eval(this);
}

void PostfixIncrementNode::Generate(Asm::Assembly *assembly)
{
    using namespace Asm;
    auto &s = assembly->TextSection();
    expr->Generate(assembly);
    if (type->GetTypeKind() == TypeKind::BUILTIN)
    {
        switch (reinterpret_cast<SymBuiltInType *>(type->GetUnqualified())->GetBuiltInTypeKind())
        {
            case BuiltInTypeKind::INT32:
                s.AddCommand(CommandName::POP, Register::EAX, CommandSuffix::L);
                s.AddCommand(CommandName::PUSH, MakeAddress(Register::EAX), CommandSuffix::L);
                s.AddCommand(CommandName::INC, MakeAddress(Register::EAX), CommandSuffix::L);
                break;
            case BuiltInTypeKind::FLOAT:
                s.AddCommand(CommandName::POP, Register::EAX, CommandSuffix::L);
                s.AddCommand(CommandName::PUSH, MakeAddress(Register::EAX), CommandSuffix::L);
                s.AddCommand(CommandName::FLD, MakeAddress(Register::EAX), CommandSuffix::S);
                s.AddCommand(CommandName::FLD1);
                s.AddCommand(CommandName::FADDP);
                s.AddCommand(CommandName::FSTP, MakeAddress(Register::EAX), CommandSuffix::S);
                break;
        }
    }
}

void PostfixDecrementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "`--" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    expr->Print(os, indent, true);
}

PostfixDecrementNode::PostfixDecrementNode(ExprNode *node) : expr(node)
{
    this->type = node->GetType();
}

ExprNode *PostfixDecrementNode::Eval(Evaluator *evaluator)
{
    return evaluator->Eval(this);
}

void PostfixDecrementNode::Generate(Asm::Assembly *assembly)
{
    using namespace Asm;
    auto &s = assembly->TextSection();
    expr->Generate(assembly);
    if (type->GetTypeKind() == TypeKind::BUILTIN)
    {
        switch (reinterpret_cast<SymBuiltInType *>(type->GetUnqualified())->GetBuiltInTypeKind())
        {
            case BuiltInTypeKind::INT32:
                s.AddCommand(CommandName::POP, Register::EAX, CommandSuffix::L);
                s.AddCommand(CommandName::PUSH, MakeAddress(Register::EAX), CommandSuffix::L);
                s.AddCommand(CommandName::DEC, MakeAddress(Register::EAX), CommandSuffix::L);
                break;
            case BuiltInTypeKind::FLOAT:
                s.AddCommand(CommandName::POP, Register::EAX, CommandSuffix::L);
                s.AddCommand(CommandName::PUSH, MakeAddress(Register::EAX), CommandSuffix::L);
                s.AddCommand(CommandName::FLD1);
                s.AddCommand(CommandName::FLD, MakeAddress(Register::EAX), CommandSuffix::S);
                s.AddCommand(CommandName::FSUBP);
                s.AddCommand(CommandName::FSTP, MakeAddress(Register::EAX), CommandSuffix::S);
                break;
        }
    }
}

void StructureOrUnionMemberAccessNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "." << std::endl;
    indent.append(isTail ? "    " : "│   ");
    structureOrUnion->Print(os, indent, false);
    member->Print(os, indent, true);
}

StructureOrUnionMemberAccessNode::StructureOrUnionMemberAccessNode(ExprNode *structureOrUnion, IdNode *member) :
        member(member), structureOrUnion(structureOrUnion) {}

ExprNode *StructureOrUnionMemberAccessNode::Eval(Evaluator *evaluator)
{
    return evaluator->Eval(this);
}

void StructureOrUnionMemberAccessNode::Generate(Asm::Assembly *assembly)
{
    using namespace Asm;
    auto &s = assembly->TextSection();
    structureOrUnion->Generate(assembly);
    s.AddCommand(CommandName::POP, Register::EAX, CommandSuffix::L);
    if (category == ValueCategory::LVAVLUE)
        s.AddCommand(CommandName::LEA, MakeAddress(member->GetVariable()->GetOffset(), Register::EAX), Register::EBX,
                     CommandSuffix::L);
    else
        s.AddCommand(CommandName::MOV, MakeAddress(member->GetVariable()->GetOffset(), Register::EAX), Register::EBX,
                     CommandSuffix::L);
    s.AddCommand(CommandName::PUSH, Register::EBX, CommandSuffix::L);
}

void StructureOrUnionMemberAccessByPointerNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "->" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    structureOrUnion->Print(os, indent, false);
    member->Print(os, indent, true);
}

StructureOrUnionMemberAccessByPointerNode::StructureOrUnionMemberAccessByPointerNode(ExprNode *structureOrUnion,
                                                                                     IdNode *member) : member(member),
                                                                                                       structureOrUnion(structureOrUnion) {}

ExprNode *StructureOrUnionMemberAccessByPointerNode::Eval(Evaluator *evaluator)
{
    return evaluator->Eval(this);
}

void StructureOrUnionMemberAccessByPointerNode::Generate(Asm::Assembly *assembly)
{
    using namespace Asm;
    auto &s = assembly->TextSection();
    structureOrUnion->Generate(assembly);
    auto ptrType = reinterpret_cast<SymPointer *>(structureOrUnion->GetType()->GetUnqualified());
    auto target = ptrType->GetTarget();
    s.AddCommand(CommandName::POP, Register::EAX, CommandSuffix::L);
    if (category == ValueCategory::LVAVLUE)
        s.AddCommand(CommandName::LEA, MakeAddress(member->GetVariable()->GetOffset(), Register::EAX), Register::EBX,
                     CommandSuffix::L);
    else
        s.AddCommand(CommandName::MOV, MakeAddress(member->GetVariable()->GetOffset(), Register::EAX), Register::EBX,
                     CommandSuffix::L);
    s.AddCommand(CommandName::PUSH, Register::EBX, CommandSuffix::L);
}

void PrefixIncrementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "++'" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    expr->Print(os, indent, true);
}

PrefixIncrementNode::PrefixIncrementNode(ExprNode *node) : expr(node)
{
    this->type = node->GetType();
}

ExprNode *PrefixIncrementNode::Eval(Evaluator *evaluator)
{
    return evaluator->Eval(this);
}

void PrefixIncrementNode::Generate(Asm::Assembly *assembly)
{
    using namespace Asm;
    auto &s = assembly->TextSection();
    expr->Generate(assembly);
    if (type->GetTypeKind() == TypeKind::BUILTIN)
    {
        switch (reinterpret_cast<SymBuiltInType *>(type->GetUnqualified())->GetBuiltInTypeKind())
        {
            case BuiltInTypeKind::INT32:
                s.AddCommand(CommandName::POP, Register::EAX, CommandSuffix::L);
                s.AddCommand(CommandName::INC, MakeAddress(Register::EAX), CommandSuffix::L);
                s.AddCommand(CommandName::PUSH, MakeAddress(Register::EAX), CommandSuffix::L);
                break;
            case BuiltInTypeKind::FLOAT:
                s.AddCommand(CommandName::POP, Register::EAX, CommandSuffix::L);
                s.AddCommand(CommandName::FLD, MakeAddress(Register::EAX), CommandSuffix::S);
                s.AddCommand(CommandName::FLD1);
                s.AddCommand(CommandName::FADDP);
                s.AddCommand(CommandName::FSTP, MakeAddress(Register::EAX), CommandSuffix::S);
                s.AddCommand(CommandName::PUSH, MakeAddress(Register::EAX), CommandSuffix::L);
                break;
        }
    }
}

void PrefixDecrementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "--`" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    expr->Print(os, indent, true);
}

PrefixDecrementNode::PrefixDecrementNode(ExprNode *node) : expr(node)
{
    this->type = node->GetType();
}

ExprNode *PrefixDecrementNode::Eval(Evaluator *evaluator)
{
    return evaluator->Eval(this);
}

void PrefixDecrementNode::Generate(Asm::Assembly *assembly)
{
    using namespace Asm;
    auto &s = assembly->TextSection();
    expr->Generate(assembly);
    if (type->GetTypeKind() == TypeKind::BUILTIN)
    {
        switch (reinterpret_cast<SymBuiltInType *>(type->GetUnqualified())->GetBuiltInTypeKind())
        {
            case BuiltInTypeKind::INT32:
                s.AddCommand(CommandName::POP, Register::EAX, CommandSuffix::L);
                s.AddCommand(CommandName::DEC, MakeAddress(Register::EAX), CommandSuffix::L);
                s.AddCommand(CommandName::PUSH, MakeAddress(Register::EAX), CommandSuffix::L);
                break;
            case BuiltInTypeKind::FLOAT:
                s.AddCommand(CommandName::POP, Register::EAX, CommandSuffix::L);
                s.AddCommand(CommandName::FLD1);
                s.AddCommand(CommandName::FLD, MakeAddress(Register::EAX), CommandSuffix::S);
                s.AddCommand(CommandName::FSUBP);
                s.AddCommand(CommandName::FSTP, MakeAddress(Register::EAX), CommandSuffix::S);
                s.AddCommand(CommandName::PUSH, MakeAddress(Register::EAX), CommandSuffix::L);
                break;
        }
    }
}

void BinOpNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << op->text << std::endl;
    indent.append(isTail ? "    " : "│   ");
    left->Print(os, indent, false);
    right->Print(os, indent, true);
}

BinOpNode::BinOpNode(ExprNode *left, ExprNode *right, std::shared_ptr<Token> op) : left(left), right(right), op(std::move(op))
{
    this->type = left->GetType();
    this->position = this->op->position;
}

BinOpNode::BinOpNode(ExprNode *left, ExprNode *right, std::shared_ptr<Token> op, SymType *resultType):
        BinOpNode(left, right, std::move(op))
{
    this->type = resultType;
}

ExprNode *BinOpNode::Eval(Evaluator *evaluator)
{
    return evaluator->Eval(this);
}

ExprNode *BinOpNode::Left() const
{
    return left;
}

ExprNode *BinOpNode::Right() const
{
    return right;
}

std::shared_ptr<Token> BinOpNode::GetOperation() const
{
    return op;
}

void BinOpNode::Generate(Asm::Assembly *assembly)
{
    left->Generate(assembly);
    auto ltk = left->GetType()->GetTypeKind();
    if (op->type == TokenType::LOGIC_AND || op->type == TokenType::LOGIC_OR)
        logicalAndOrGenerate(assembly);
    else if (ltk == TypeKind::BUILTIN)
    {
        switch (reinterpret_cast<SymBuiltInType *>(left->GetType()->GetUnqualified())->GetBuiltInTypeKind())
        {
            case BuiltInTypeKind::INT32:
                int32Generate(assembly);
                break;
            case BuiltInTypeKind::FLOAT:
                floatGenerate(assembly);
                break;
        }
    }
    else if (ltk == TypeKind::POINTER)
        pointerGenerate(assembly);
}

void BinOpNode::int32Generate(Asm::Assembly *assembly)
{
    using namespace Asm;
    Section &section = assembly->TextSection();
    static std::unordered_map<TokenType, CommandName> optoasm =
    {
            {TokenType::PLUS, CommandName::ADD}, {TokenType::MINUS, CommandName::SUB},
            {TokenType::BITWISE_AND, CommandName::AND}, {TokenType::BITWISE_OR, CommandName::OR},
            {TokenType::BITWISE_XOR, CommandName::XOR}, {TokenType::BITWISE_LSHIFT, CommandName::SAL},
            {TokenType::BITWISE_RSHIFT, CommandName::SAR}, {TokenType::RELOP_EQ, CommandName::SETE},
            {TokenType::RELOP_GT, CommandName::SETG}, {TokenType::RELOP_GE, CommandName::SETGE},
            {TokenType::RELOP_LT, CommandName::SETL}, {TokenType::RELOP_LE, CommandName::SETLE},
            {TokenType::RELOP_NE, CommandName::SETNE}, {TokenType::ASTERIX, CommandName::IMUL},
            {TokenType::FORWARD_SLASH, CommandName::IDIV}, {TokenType::REMINDER, CommandName::IDIV}
    };
    right->Generate(assembly);
    section.AddCommand(CommandName::POP, op->type == TokenType::BITWISE_LSHIFT || op->type == TokenType::BITWISE_RSHIFT ?
                                         Register::ECX : Register::EBX, CommandSuffix::L);
    section.AddCommand(CommandName::POP, Register::EAX, CommandSuffix::L);
    if (op->type == TokenType::FORWARD_SLASH || op->type == TokenType::REMINDER)
    {
        section.AddCommand(CommandName::XOR, Register::EDX, Register::EDX, CommandSuffix::L);
        section.AddCommand(CommandName::IDIV, Register::EBX, CommandSuffix::L);
    }
    else if (isRelop(op->type))
    {
        section.AddCommand(CommandName::CMP, Register::EBX, Register::EAX, CommandSuffix::L);
        section.AddCommand(optoasm[op->type], Register::BL);
        section.AddCommand(CommandName::MOVZX, Register::BL, Register::EAX);
    }
    else if (op->type == TokenType::BITWISE_LSHIFT || op->type == TokenType::BITWISE_RSHIFT)
        section.AddCommand(optoasm[op->type], Register::CL, Register::EAX, CommandSuffix::L);
    else
        section.AddCommand(optoasm[op->type], Register::EBX, Register::EAX, CommandSuffix::L);
    section.AddCommand(CommandName::PUSH, op->type == TokenType::REMINDER ? Register::EDX : Register::EAX,
                       CommandSuffix::L);
}

void BinOpNode::floatGenerate(Asm::Assembly *assembly)
{
    using namespace Asm;
    Section &section = assembly->TextSection();
    static std::unordered_map<TokenType, CommandName> optoasm =
    {
            {TokenType::PLUS, CommandName::FADDP,}, {TokenType::MINUS, CommandName::FSUBP},
            {TokenType::ASTERIX, CommandName::FMULP}, {TokenType::FORWARD_SLASH, CommandName ::FDIVP},
            {TokenType::RELOP_EQ, CommandName::SETE}, {TokenType::RELOP_GT, CommandName::SETA},
            {TokenType::RELOP_GE, CommandName::SETAE}, {TokenType::RELOP_LT, CommandName::SETB},
            {TokenType::RELOP_LE, CommandName::SETBE},
            {TokenType::RELOP_NE, CommandName::SETNE}
    };
    right->Generate(assembly);
    section.AddCommand(CommandName::FLD, MakeAddress(Register::ESP), CommandSuffix::S);
    section.AddCommand(CommandName::POP, Register::EAX, CommandSuffix::L);
    section.AddCommand(CommandName::FLD, MakeAddress(Register::ESP), CommandSuffix::S);
    if (isRelop(op->type))
    {
        section.AddCommand(CommandName::FCOMIP);
        section.AddCommand(CommandName::FSTP, Register::ST0);
        section.AddCommand(optoasm[op->type], Register::BL);
        section.AddCommand(CommandName::MOVZX, Register::BL, Register::EAX);
        section.AddCommand(CommandName::MOV, Register::EAX, MakeAddress(Register::ESP), CommandSuffix::L);
    }
    else
    {
        section.AddCommand(optoasm[op->type]);
        section.AddCommand(CommandName::FSTP, MakeAddress(Register::ESP), CommandSuffix::S);
    }
}

void BinOpNode::logicalAndOrGenerate(Asm::Assembly *assembly)
{
    using namespace Asm;
    Section &section = assembly->TextSection();
    auto l1 = assembly->NextLabel(), l2 = assembly->NextLabel();
    auto ltype = left->GetType(), rtype = right->GetType();
    auto jmpCommand = op->type == TokenType::LOGIC_AND ? Asm::CommandName::JE : Asm::CommandName::JNE;
    if (ltype->GetTypeKind() == TypeKind::POINTER) ltype = new SymBuiltInType(BuiltInTypeKind::INT32);
    if (rtype->GetTypeKind() == TypeKind::POINTER) rtype = new SymBuiltInType(BuiltInTypeKind::INT32);
    static std::unordered_map<BuiltInTypeKind, std::function<void()>> bttoasm =
    {
            {BuiltInTypeKind::INT32,
            [&]()
                 {
                     section.AddCommand(CommandName::POP, Register::EAX, CommandSuffix::L);
                     section.AddCommand(CommandName::CMP, ConstNode::IntZero(), Register::EAX, CommandSuffix::L);
                 }
            },
            {BuiltInTypeKind::FLOAT,
            [&]()
                {
                    section.AddCommand(CommandName::FLD, MakeAddress(Register::ESP), CommandSuffix::S);
                    section.AddCommand(CommandName::FLDZ);
                    section.AddCommand(CommandName::FCOMIP);
                    section.AddCommand(CommandName::FSTP, Register::ST0);
                    section.AddCommand(CommandName::POP, Register::EAX, CommandSuffix::L);
                }
            }

    };
    if (ltype->GetTypeKind() == TypeKind::BUILTIN)
        bttoasm[reinterpret_cast<SymBuiltInType *>(ltype)->GetBuiltInTypeKind()]();
    section.AddCommand(jmpCommand, l1);
    right->Generate(assembly);
    if (rtype->GetTypeKind() == TypeKind::BUILTIN)
        bttoasm[reinterpret_cast<SymBuiltInType *>(rtype)->GetBuiltInTypeKind()]();
    section.AddCommand(jmpCommand, l1);
    section.AddCommand(CommandName::PUSH, ConstNode::IntOne(), CommandSuffix::L);
    section.AddCommand(CommandName::JMP, l2);
    section.AddLabel(l1);
    section.AddCommand(CommandName::PUSH, ConstNode::IntZero(), CommandSuffix::L);
    section.AddLabel(l2);
}

bool BinOpNode::isRelop(TokenType type)
{
    return type == TokenType::RELOP_NE || type == TokenType::RELOP_LE || type == TokenType::RELOP_GE ||
            type == TokenType::RELOP_GT || type == TokenType::RELOP_EQ || type == TokenType::RELOP_LT;
}

void BinOpNode::pointerGenerate(Asm::Assembly *assembly)
{
    using namespace Asm;
    Section &section = assembly->TextSection();
    right->Generate(assembly);
    auto rtype = right->GetType();
    section.AddCommand(CommandName::POP, Register::EBX, CommandSuffix::L);
    section.AddCommand(CommandName::POP, Register::EAX, CommandSuffix::L);
    auto target = reinterpret_cast<SymPointer *>(type)->GetTarget();
    if (op->type == TokenType::PLUS || (op->type == TokenType::MINUS && rtype->GetTypeKind() != TypeKind::POINTER))
    {
        if (op->type == TokenType::MINUS) section.AddCommand(CommandName::NEG, Register::EBX, CommandSuffix::L);
        section.AddCommand(CommandName::LEA, MakeAddress(0, Register::EAX, Register::EBX, target->Size()),
                           Register::EAX, CommandSuffix::L);
    }
    else
    {
        auto rt = reinterpret_cast<SymPointer *>(right->GetType())->GetTarget();
        section.AddCommand(CommandName::SUB, Register::EBX, Register::EAX, CommandSuffix::L);
        section.AddCommand(CommandName::MOV, new IntConstNode(rt->Size()), Register::EBX, CommandSuffix::L);
        section.AddCommand(CommandName::XOR, Register::EDX, Register::EDX, CommandSuffix::L);
        section.AddCommand(CommandName::IDIV, Register::EBX, CommandSuffix::L);
    }
    section.AddCommand(CommandName::PUSH, Register::EAX, CommandSuffix::L);
}

void ArrayAccessNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "[]" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    array->Print(os, indent, false);
    index->Print(os, indent, true);
}

ArrayAccessNode::ArrayAccessNode(ExprNode *left, ExprNode *inBrackets) : array(left), index(inBrackets) {}

ExprNode *ArrayAccessNode::Eval(Evaluator *evaluator)
{
    return evaluator->Eval(this);
}

void ArrayAccessNode::Generate(Asm::Assembly *assembly)
{
    using namespace Asm;
    auto &s = assembly->TextSection();
    array->Generate(assembly);
    index->Generate(assembly);
    s.AddCommand(CommandName::POP, Register::ESI, CommandSuffix ::L);
    s.AddCommand(CommandName::POP, Register::EAX, CommandSuffix::L);
    s.AddCommand(CommandName::LEA, MakeAddress(0, Register::EAX, Register::ESI, type->Size()), Register::EBX, CommandSuffix::L);
    if (category == ValueCategory::LVAVLUE || type->GetTypeKind() == TypeKind::ARRAY)
        s.AddCommand(CommandName::PUSH, Register::EBX, CommandSuffix::L);
    else
    {
        if (type->GetTypeKind() == TypeKind::BUILTIN)
            s.AddCommand(CommandName::PUSH, MakeAddress(Register::EBX), CommandSuffix::L);
    }
}

void TernaryOperatorNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "?:" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    condition->Print(os, indent, false);
    iftrue->Print(os, indent, false);
    iffalse->Print(os, indent, true);
}

TernaryOperatorNode::TernaryOperatorNode(ExprNode *condition, ExprNode *iftrue, ExprNode *iffalse) :
        condition(condition), iftrue(iftrue), iffalse(iffalse)
{
    this->type = iftrue->GetType();
}

ExprNode *TernaryOperatorNode::Eval(Evaluator *evaluator)
{
    return evaluator->Eval(this);
}

void TernaryOperatorNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}


void AssignmentNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << assignmentOp->stringValue << std::endl;
    indent.append(isTail ? "    " : "│   ");
    left->Print(os, indent, false);
    right->Print(os, indent, true);
}

AssignmentNode::AssignmentNode(ExprNode *left, ExprNode *right, std::shared_ptr<Token> assignmentOp) : left(left), right(right),
                                                                                                       assignmentOp(std::move(assignmentOp))
{
    this->type = left->GetType();
}

ExprNode *AssignmentNode::Eval(Evaluator *evaluator)
{
    return evaluator->Eval(this);
}

void AssignmentNode::Generate(Asm::Assembly *assembly)
{
    using namespace Asm;
    Section &s = assembly->TextSection();
    right->Generate(assembly);
    left->Generate(assembly);
    s.AddCommand(CommandName::POP, Register::EBX, CommandSuffix::L);
    if (right->GetType()->GetTypeKind() == TypeKind::STRUCT)
    {
        auto rt = reinterpret_cast<SymRecord *>(right->GetType()->GetUnqualified());
        auto &fields = rt->GetOrderedFields();
        for (auto it = fields.begin(); it != fields.end(); it++)
        {
            auto ft = (*it)->GetType()->GetUnqualified();
            if (ft->GetTypeKind() == TypeKind::ARRAY)
                assignArray(assembly, (*it)->GetOffset(), reinterpret_cast<SymArray *>(ft));
            else if (ft->GetTypeKind() == TypeKind::STRUCT)
                assignStructure(assembly, (*it)->GetOffset(), reinterpret_cast<SymRecord *>(ft));
            else
            {
                s.AddCommand(CommandName::MOV, MakeAddress((*it)->GetOffset(), Register::ESP), Register::EAX, CommandSuffix::L);
                s.AddCommand(CommandName::MOV, Register::EAX, MakeAddress((*it)->GetOffset(), Register::EBX), CommandSuffix::L);
            }
        }
        return;
    }
    s.AddCommand(CommandName::POP, Register::EAX, CommandSuffix::L);
    s.AddCommand(CommandName::MOV, Register::EAX, MakeAddress(Register::EBX), CommandSuffix::L);
    s.AddCommand(CommandName::PUSH, MakeAddress(Register::EBX), CommandSuffix::L);
}

void AssignmentNode::assignArray(Asm::Assembly *assembly, int32_t offset, SymArray *array)
{
    using namespace Asm;
    Section &s = assembly->TextSection();
    auto n =  array->NumberOfElements();
    auto vt = array->GetValueType()->GetUnqualified();
    auto elemSize = vt->Size();
    for (int i = 0; i < n; i++)
    {
        offset += i * elemSize;
        if (vt->GetTypeKind() == TypeKind::ARRAY)
            assignArray(assembly, offset, reinterpret_cast<SymArray *>(vt));
        else if (vt->GetTypeKind() == TypeKind::STRUCT)
            assignStructure(assembly, offset, reinterpret_cast<SymRecord *>(vt));
        else
        {
            s.AddCommand(CommandName::MOV, MakeAddress(offset, Register::ESP), Register::EAX, CommandSuffix::L);
            s.AddCommand(CommandName::MOV, Register::EAX, MakeAddress(offset, Register::EBX), CommandSuffix::L);
        }
    }

}

void AssignmentNode::assignStructure(Asm::Assembly *assembly, int32_t offset, SymRecord *record)
{
    using namespace Asm;
    Section &s = assembly->TextSection();
    for (auto field: record->GetOrderedFields())
    {
        auto ft = field->GetType()->GetUnqualified();
        if (ft->GetTypeKind() == TypeKind::ARRAY)
            assignArray(assembly, offset + field->GetOffset(), reinterpret_cast<SymArray *>(ft));
        else if (ft->GetTypeKind() == TypeKind::STRUCT)
            assignStructure(assembly, offset + field->GetOffset(), reinterpret_cast<SymRecord *>(ft));
        else
        {
            s.AddCommand(CommandName::MOV, MakeAddress(offset + field->GetOffset(), Register::ESP), Register::EAX, CommandSuffix::L);
            s.AddCommand(CommandName::MOV, Register::EAX, MakeAddress(offset + field->GetOffset(), Register::EBX), CommandSuffix::L);
        }
    }
}

void TypeCastNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "typcast" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    castType->Print(os, indent, false);
    castExpr->Print(os, indent, true);
}

TypeCastNode::TypeCastNode(SymType *type, ExprNode *castExpr) : castType(type), castExpr(castExpr)
{
    this->type = type;
}

ExprNode *TypeCastNode::Eval(Evaluator *evaluator)
{
    return evaluator->Eval(this);
}

void TypeCastNode::Generate(Asm::Assembly *assembly)
{
    castExpr->Generate(assembly);
    auto cet = castExpr->GetType();
    if (cet->GetTypeKind() == TypeKind::BUILTIN && castType->GetTypeKind() == TypeKind::BUILTIN)
    {
        auto castTypeBtk = reinterpret_cast<SymBuiltInType *>(castType->GetUnqualified());
        auto castExprBtk = reinterpret_cast<SymBuiltInType *>(cet->GetUnqualified());
        BuiltInTypeConversions[std::make_pair(castExprBtk->GetBuiltInTypeKind(), castTypeBtk->GetBuiltInTypeKind())](assembly);
    }
    // TODO
}

void UnaryOpNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << unaryOp->stringValue << std::endl;
    indent.append(isTail ? "    " : "│   ");
    expr->Print(os, indent, true);
}

UnaryOpNode::UnaryOpNode(std::shared_ptr<Token> unaryOp, ExprNode *expr) : unaryOp(unaryOp), expr(expr)
{
    position = unaryOp->position;
}

ExprNode *UnaryOpNode::Eval(Evaluator *evaluator)
{
    return evaluator->Eval(this);
}

void UnaryOpNode::Generate(Asm::Assembly *assembly)
{
    expr->Generate(assembly);
    if (unaryOp->type == TokenType::BITWISE_AND) return;
    if (expr->GetType()->GetTypeKind() == TypeKind::BUILTIN)
        switch (reinterpret_cast<SymBuiltInType *>(expr->GetType()->GetUnqualified())->GetBuiltInTypeKind())
        {
            case BuiltInTypeKind::INT32:
                int32Generate(assembly);
                break;
            case BuiltInTypeKind::FLOAT:
                floatGenerate(assembly);
                break;
        }
    else if (expr->GetType()->GetTypeKind() == TypeKind::POINTER)
        pointerGenerate(assembly);
}

void UnaryOpNode::int32Generate(Asm::Assembly *assembly)
{
    using namespace Asm;
    Section &section = assembly->TextSection();
    section.AddCommand(CommandName::POP, Register::EAX, CommandSuffix::L);
    switch (unaryOp->type)
    {
        case TokenType::MINUS:
            section.AddCommand(CommandName::NEG, Register::EAX, CommandSuffix::L);
            break;
        case TokenType::BITWISE_NOT:
            section.AddCommand(CommandName::NOT, Register::EAX, CommandSuffix::L);
            break;
        case TokenType::LOGIC_NO:
            section.AddCommand(CommandName::CMP, ConstNode::IntZero(), Register::EAX, CommandSuffix::L);
            section.AddCommand(CommandName::SETE, Register::BL);
            section.AddCommand(CommandName::MOVZX, Register::BL, Register::EAX);
            break;
    }
    section.AddCommand(CommandName::PUSH, Register::EAX, CommandSuffix::L);
}

void UnaryOpNode::floatGenerate(Asm::Assembly *assembly)
{
    using namespace Asm;
    Section &section = assembly->TextSection();
    section.AddCommand(CommandName::FLD, MakeAddress(Register::ESP), CommandSuffix::S);
    switch (unaryOp->type)
    {
        case TokenType::MINUS:
            section.AddCommand(CommandName::FCHS);
            section.AddCommand(CommandName::FSTP, MakeAddress(Register::ESP), CommandSuffix::S);
            break;
        case TokenType::LOGIC_NO:
            section.AddCommand(CommandName::POP, Register::EAX, CommandSuffix::L);
            section.AddCommand(CommandName::FLDZ);
            section.AddCommand(CommandName::FCOMIP);
            section.AddCommand(CommandName::FSTP, Register::ST0);
            section.AddCommand(CommandName::SETE, Register::BL);
            section.AddCommand(CommandName::MOVZX, Register::BL, Register::EAX);
            section.AddCommand(CommandName::PUSH, Register::EAX, CommandSuffix::L);
            break;
    }
}

void UnaryOpNode::pointerGenerate(Asm::Assembly *assembly)
{
    using namespace Asm;
    auto &s = assembly->TextSection();
    auto ptrType = reinterpret_cast<SymPointer *>(expr->GetType()->GetUnqualified());
    auto target = ptrType->GetTarget();
    if ((target->GetTypeKind() == TypeKind::BUILTIN || target->GetTypeKind() == TypeKind::POINTER)
        && category == ValueCategory::RVALUE)
    {
        s.AddCommand(CommandName::POP, Register::EBX, CommandSuffix::L);
        s.AddCommand(CommandName::MOV, MakeAddress(Register::EBX), Register::EAX, CommandSuffix::L);
        s.AddCommand(CommandName::PUSH, Register::EAX, CommandSuffix::L);
    }

}

void SizeofExprNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "sizeof" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    expr->Print(os, indent, true);
}

SizeofExprNode::SizeofExprNode(ExprNode *expr) : expr(expr) {}

ExprNode *SizeofExprNode::Eval(Evaluator *evaluator)
{
    return evaluator->Eval(this);
}

void SizeofExprNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void SizeofTypeNameNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "sizeof()" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    typeName->Print(os, indent, true);
}

SizeofTypeNameNode::SizeofTypeNameNode(SymType *typeName) : typeName(typeName) {}

ExprNode *SizeofTypeNameNode::Eval(Evaluator *evaluator)
{
    return evaluator->Eval(this);
}

void SizeofTypeNameNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void CommaSeparatedExprs::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "," << std::endl;
    indent.append(isTail ? "    " : "│   ");
    auto it = expressions.begin();
    if (expressions.size() > 1)
        for (; it != --expressions.end(); it++)
            (*it)->Print(os, indent, false);
    (*it)->Print(os, indent, true);
}

ExprNode *CommaSeparatedExprs::Eval(Evaluator *evaluator)
{
    return evaluator->Eval(this);
}

void CommaSeparatedExprs::Generate(Asm::Assembly *assembly)
{
    auto it = expressions.begin();
    for (; it != --expressions.end(); it++)
    {
        (*it)->Generate(assembly);
        ExprStatmentNode::CleanStackAfterExpression((*it), assembly);
    }
    expressions.back()->Generate(assembly);
}

void CommaSeparatedExprs::Add(ExprNode *expr)
{
    expressions.push_back(expr);
    type = expr->GetType();
}

uint64_t CommaSeparatedExprs::Size()
{
    return expressions.size();
}

std::list<ExprNode *> &CommaSeparatedExprs::List()
{
    return expressions;
}

void PointerNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "*" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (pointer)
    {
        typeQualifierList->Print(os, indent, false);
        pointer->Print(os, indent, true);
    }
    else
        typeQualifierList->Print(os, indent, true);
}

PointerNode::PointerNode(DeclarationSpecifiersNode *typeQualifierList, PointerNode *pointer) :
        typeQualifierList(typeQualifierList), pointer(pointer) {}

void PointerNode::Generate(Asm::Assembly *assembly)
{

}

void ExprStatmentNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << ";" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (expr) expr->Print(os, indent, true);
}

ExprStatmentNode::ExprStatmentNode(ExprNode *expr) : expr(expr) {}

void ExprStatmentNode::Generate(Asm::Assembly *assembly)
{
    using namespace Asm;
    auto &s = assembly->TextSection();
    if (expr)
    {
        expr->Generate(assembly);
        auto etype = expr->GetType()->GetUnqualified();
        if (etype->GetTypeKind() == TypeKind::POINTER || etype->GetTypeKind() == TypeKind::BUILTIN)
        {
            if (etype->GetTypeKind() == TypeKind::BUILTIN &&
                    reinterpret_cast<SymBuiltInType *>(etype)->GetBuiltInTypeKind() == BuiltInTypeKind::VOID)
                return;
            s.AddCommand(CommandName::POP, Register::EAX, CommandSuffix::L);
        }
    }
}

void ExprStatmentNode::CleanStackAfterExpression(ExprNode *expr, Asm::Assembly *assembly)
{
    using namespace Asm;
    auto &s = assembly->TextSection();
    auto etype = expr->GetType()->GetUnqualified();
    if (etype->GetTypeKind() == TypeKind::POINTER || etype->GetTypeKind() == TypeKind::BUILTIN)
    {
        if (etype->GetTypeKind() == TypeKind::BUILTIN &&
            reinterpret_cast<SymBuiltInType *>(etype)->GetBuiltInTypeKind() == BuiltInTypeKind::VOID)
            return;
        s.AddCommand(CommandName::POP, Register::EAX, CommandSuffix::L);
    }
    else if (etype->GetTypeKind() == TypeKind::STRUCT)
    {
        auto rt = reinterpret_cast<SymRecord *>(etype);
        s.AddCommand(CommandName::ADD, new IntConstNode(rt->Size()), Register::ESP, CommandSuffix::L);
    }
}

void IfStatementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "if" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    condition->Print(os, indent, false);
    body->Print(os, indent, true);
}

void IfStatementNode::Generate(Asm::Assembly *assembly)
{
    using namespace Asm;
    auto &s = assembly->TextSection();
    auto outLabel = assembly->NextLabel();
    condition->Generate(assembly);
    StatementNode::GenerateConditionCheck(assembly, condition);
    s.AddCommand(CommandName::JE, outLabel);
    body->Generate(assembly);
    s.AddLabel(outLabel);
}

IfStatementNode::IfStatementNode(ExprNode *expr, StatementNode *then) : condition(expr), body(then) {}

void IfElseStatementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "if else" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    condition->Print(os, indent, false);
    body->Print(os, indent, false);
    elseBody->Print(os, indent, true);
}

IfElseStatementNode::IfElseStatementNode(ExprNode *expr, StatementNode *then, StatementNode *_else) :
        IfStatementNode(expr, then), elseBody(_else) {}

void IfElseStatementNode::Generate(Asm::Assembly *assembly)
{
    using namespace Asm;
    auto &s = assembly->TextSection();
    auto outLabel = assembly->NextLabel();
    auto elseLabel = assembly->NextLabel();
    condition->Generate(assembly);
    StatementNode::GenerateConditionCheck(assembly, condition);
    s.AddCommand(CommandName::JE, elseLabel);
    body->Generate(assembly);
    s.AddCommand(CommandName::JMP, outLabel);
    s.AddLabel(elseLabel);
    elseBody->Generate(assembly);
    s.AddLabel(outLabel);
}

void GotoStatementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "goto" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    id->Print(os, indent, true);
}

GotoStatementNode::GotoStatementNode(IdNode *id) : id(id) {}

void GotoStatementNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void ContinueStatementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "continue" << std::endl;
}

void ContinueStatementNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void BreakStatementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "break" << std::endl;
}

void BreakStatementNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void ReturnStatementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "return" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (expr) expr->Print(os, indent, true);
}

ReturnStatementNode::ReturnStatementNode(ExprNode *expr, SymFunction *function) : expr(expr), function(function) {}

void ReturnStatementNode::Generate(Asm::Assembly *assembly)
{
    using namespace Asm;
    auto &s = assembly->TextSection();
    if (!expr) return;
    expr->Generate(assembly);
    auto etype = expr->GetType()->GetUnqualified();
    if (etype->GetTypeKind() == TypeKind::POINTER || etype->GetTypeKind() == TypeKind::BUILTIN)
    {
        s.AddCommand(CommandName::POP, Register::EAX, CommandSuffix::L);
    }
    s.AddCommand(CommandName::JMP, function->GetReturnLabel());
}

void WhileStatementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "while" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    condition->Print(os, indent, false);
    body->Print(os, indent, true);
}

WhileStatementNode::WhileStatementNode(ExprNode *condition, StatementNode *body)
{
    this->condition = condition;
    this->body = body;
}

void WhileStatementNode::Generate(Asm::Assembly *assembly)
{
    using namespace Asm;
    auto &s = assembly->TextSection();
    continueLabel = assembly->NextLabel(), breakLabel = assembly->NextLabel();
    s.AddLabel(continueLabel);
    condition->Generate(assembly);
    StatementNode::GenerateConditionCheck(assembly, condition);
    s.AddCommand(CommandName::JE, breakLabel);
    if (body) body->Generate(assembly);
    s.AddCommand(CommandName::JMP, continueLabel);
    s.AddLabel(breakLabel);
}

void DoWhileStatementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "do" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    body->Print(os, indent, false);
    condition->Print(os, indent, true);
}

DoWhileStatementNode::DoWhileStatementNode(ExprNode *condition, StatementNode *body)
{
    this->condition = condition;
    this->body = body;
}

void DoWhileStatementNode::SetCondition(ExprNode *condition)
{
    this->condition = condition;
}

void DoWhileStatementNode::Generate(Asm::Assembly *assembly)
{
    using namespace Asm;
    auto &s = assembly->TextSection();
    continueLabel = assembly->NextLabel(), breakLabel = assembly->NextLabel();
    begining = assembly->NextLabel();
    s.AddLabel(begining);
    body->Generate(assembly);
    s.AddLabel(continueLabel);
    condition->Generate(assembly);
    StatementNode::GenerateConditionCheck(assembly, condition);
    s.AddCommand(CommandName::JNE, begining);
    s.AddLabel(breakLabel);
}

void ForStatementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "for" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (init)
        init->Print(os, indent, false);
    else
        os << indent << "├── " << std::endl;
    if (condition)
        condition->Print(os, indent, false);
    else
        os << indent << "├── " << std::endl;
    if (iteration)
        iteration->Print(os, indent, false);
    else
        os << indent << "├── " << std::endl;
    body->Print(os, indent, true);

}

ForStatementNode::ForStatementNode(ExprNode *init, ExprNode *condition, ExprNode *iteration,
                                   StatementNode *body) : init(init), iteration(iteration)
{
    this->condition = condition;
    this->body = body;
}

void ForStatementNode::Generate(Asm::Assembly *assembly)
{
    using namespace Asm;
    auto &s = assembly->TextSection();
    if (init)
    {
        init->Generate(assembly);
        ExprStatmentNode::CleanStackAfterExpression(init, assembly);
    }
    continueLabel = assembly->NextLabel(), breakLabel = assembly->NextLabel();
    s.AddLabel(continueLabel);
    if (condition)
    {
        condition->Generate(assembly);
        StatementNode::GenerateConditionCheck(assembly, condition);
        s.AddCommand(CommandName::JE, breakLabel);
    }
    body->Generate(assembly);
    if (iteration)
    {
        iteration->Generate(assembly);
        ExprStatmentNode::CleanStackAfterExpression(iteration, assembly);
    }
    s.AddCommand(CommandName::JMP, continueLabel);
    s.AddLabel(breakLabel);
}


void LabelStatementNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "functionLabel" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    labelName->Print(os, indent, false);
    statement->Print(os, indent, true);
}

LabelStatementNode::LabelStatementNode(IdNode *labelName, StatementNode *statement) : labelName(labelName), statement(statement) {}

void LabelStatementNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void DeclaratorNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "Declarator" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (id) id->Print(os, indent, false);
    type->Print(os, indent, true);
}

void DeclaratorNode::SetType(SymType *type)
{
    this->type = type;
}

SymType *DeclaratorNode::GetType() const
{
//    if (type->GetTypeKind() == TypeKind::TYPEDEF)
//        return reinterpret_cast<>
    return type;
}

void DeclaratorNode::SetId(IdNode *name)
{
    this->id = name;
}

IdNode *DeclaratorNode::GetId() const
{
    return id;
}

void DeclaratorNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

DeclaratorNode::DeclaratorNode()
{
    type = nullptr;
}

void ArgumentExprListNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    if (list.empty()) return;
    os << indent << (isTail ? "└── " : "├── ");
    os << "ArgumentExprList" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    auto it = list.begin();
    if (list.size() > 1)
        for (; it != --list.end(); it++)
            (*it)->Print(os, indent, false);
    (*it)->Print(os, indent, true);
}

void ArgumentExprListNode::Add(ExprNode *assignmentExpr)
{
    list.push_back(assignmentExpr);
}

uint64_t ArgumentExprListNode::Size()
{
    return list.size();
}

std::list<ExprNode *> &ArgumentExprListNode::List()
{
    return list;
}

void ArgumentExprListNode::Generate(Asm::Assembly *assembly)
{
    for (auto it = list.rbegin(); it != list.rend(); it++)
        (*it)->Generate(assembly);
}

int32_t ArgumentExprListNode::GetArgumentsSize()
{
    if (!this) return 0;
    int32_t res = 0;
    for (auto expr: list)
        res += expr->GetType()->Size();
    return res;
}

void FunctionCallNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "FuncCall" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (arguments->Size())
    {
        function->Print(os, indent, false);
        arguments->Print(os, indent, true);
        return;
    }
    function->Print(os, indent, true);
}

FunctionCallNode::FunctionCallNode(ExprNode *function, ArgumentExprListNode *arguments) :
        function(function), arguments(arguments) {}

ExprNode *FunctionCallNode::Eval(Evaluator *evaluator)
{
    return evaluator->Eval(this);
}

void FunctionCallNode::Generate(Asm::Assembly *assembly)
{
    using namespace Asm;
    auto &s = assembly->TextSection();
    auto t = reinterpret_cast<SymFunction *>(function->GetType()->GetUnqualified());
    if (arguments) arguments->Generate(assembly);
    auto rt = t->GetReturnType()->GetUnqualified();
    if (rt->GetTypeKind() == TypeKind::STRUCT)
        s.AddCommand(CommandName::SUB, new IntConstNode(rt->Size()), Register::ESP, CommandSuffix::L);
    s.AddCommand(CommandName::CALL, t->GetLabel());
    if (t->GetArgumentsStorageSize())
        s.AddCommand(CommandName::ADD, new IntConstNode(t->GetArgumentsStorageSize()), Register::ESP, CommandSuffix::L);
    if (rt->GetTypeKind() != TypeKind::STRUCT)
        s.AddCommand(CommandName::PUSH, Register::EAX, CommandSuffix::L);
}

void DeclarationSpecifiersNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    if (list.empty()) return;
    os << indent << (isTail ? "└── " : "├── ");
    os << "DeclarationSpecifiers" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    auto it = list.begin();
    if (list.size() > 1)
        for (; it != --list.end(); it++)
            (*it)->Print(os, indent, false);
    (*it)->Print(os, indent, true);
}

void DeclarationSpecifiersNode::Add(DeclarationSpecifierNode *specifier)
{
    list.push_back(specifier);
}

uint64_t DeclarationSpecifiersNode::Size()
{
    return list.size();
}

DeclarationSpecifiersNode::DeclarationSpecifiersNode(std::initializer_list<DeclarationSpecifierNode *> initializerList)
{
    for (auto it : initializerList)
        Add(it);
}

std::list<DeclarationSpecifierNode *> &DeclarationSpecifiersNode::List()
{
    return list;
}

void DeclarationSpecifiersNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void ParameterList::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "ParameterList" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    auto it = list.begin();
    if (list.size() > 1)
        for (; it != --list.end(); it++)
            (*it)->Print(os, indent, false);
    (*it)->Print(os, indent, true);
}

void ParameterList::Add(ParameterDeclarationNode *parameterDeclaration)
{
    list.push_back(parameterDeclaration);
}

uint64_t ParameterList::Size()
{
    return list.size();
}

std::list<ParameterDeclarationNode *> &ParameterList::List()
{
    return list;
}

void ParameterList::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void ParameterDeclarationNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "param" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (GetId()) GetId()->Print(os, indent, false);
    GetType()->Print(os, indent, true);
}

ParameterDeclarationNode::ParameterDeclarationNode(DeclaratorNode *declarator)
{
    SetId(declarator->GetId());
    SetType(declarator->GetType());
}

void ParameterDeclarationNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void DeclarationNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "Decl" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (list) list->Print(os, indent, true);
}

void DeclarationNode::Generate(Asm::Assembly *assembly)
{
    if (list) list->Generate(assembly);
}

uint64_t InitDeclaratorListNode::Size()
{
    return list.size();
}

void InitDeclaratorListNode::Add(InitDeclaratorNode *initDeclarator)
{
    list.push_back(initDeclarator);
}

void InitDeclaratorListNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    if (list.empty()) return;
    os << indent << (isTail ? "└── " : "├── ");
    os << "InitDeclaratorList" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    auto it = list.begin();
    if (list.size() > 1)
        for (; it != --list.end(); it++)
            (*it)->Print(os, indent, false);
    (*it)->Print(os, indent, true);
}

std::list<InitDeclaratorNode *> &InitDeclaratorListNode::List()
{
    return list;
}

void InitDeclaratorListNode::Generate(Asm::Assembly *assembly)
{
    for (auto idn: list)
        idn->Generate(assembly);
}

void InitDeclaratorNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "InitDeclarator" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    GetId()->Print(os, indent, false);
    GetType()->Print(os, indent, !initializer);
    if (initializer) initializer->Print(os, indent, true);
}

InitDeclaratorNode::InitDeclaratorNode(DeclaratorNode *declarator, InitializerNode *initializer): initializer(initializer)
{
    SetType(declarator->GetType());
    SetId(declarator->GetId());
}

InitializerNode *InitDeclaratorNode::GetInitializer() const
{
    return initializer;
}

void InitDeclaratorNode::Generate(Asm::Assembly *assembly)
{
    // TODO complex initializer
    if (initializer)
    {
        initializer->Generate(assembly);
        Asm::Section &s = assembly->TextSection();
        s.AddCommand(Asm::CommandName::POP, Asm::Register::EAX, Asm::CommandSuffix::L);
        s.AddCommand(Asm::CommandName::MOV, Asm::Register::EAX,
                     Asm::MakeAddress(variable->GetOffset(), Asm::Register::EBP), Asm::CommandSuffix::L);
    }
}

void InitDeclaratorNode::SetVariable(SymVariable *variable)
{
    this->variable = variable;
}

void CompoundStatement::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "{}" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (blockItemList) blockItemList->Print(os, indent, true);
}

CompoundStatement::CompoundStatement(BlockItemListNode *blockItemList) : blockItemList(blockItemList) {}

void CompoundStatement::Generate(Asm::Assembly *assembly)
{
    blockItemList->Generate(assembly);
}

void BlockItemNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << std::endl;
    indent.append(isTail ? "    " : "│   ");
    declOrStatement->Print(os, indent, true);
}

BlockItemNode::BlockItemNode(Node *declOrStatement) : declOrStatement(declOrStatement) {}

void BlockItemNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

uint64_t BlockItemListNode::Size()
{
    return list.size();
}

void BlockItemListNode::Add(BlockItemNode *blockItem)
{
    list.push_back(blockItem);
}

void BlockItemListNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    if (list.empty()) return;
    os << indent << (isTail ? "└── " : "├── ");
    os << "BlockItemList" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    auto it = list.begin();
    if (list.size() > 1)
        for (; it != --list.end(); it++)
            (*it)->Print(os, indent, false);
    (*it)->Print(os, indent, true);
}

void BlockItemListNode::Generate(Asm::Assembly *assembly)
{
    for (auto &element: list)
        element->Generate(assembly);
}

uint64_t EnumeratorList::Size()
{
    return list.size();
}

void EnumeratorList::Add(EnumeratorNode *initDeclarator)
{
    list.push_back(initDeclarator);
}

void EnumeratorList::Print(std::ostream &os, std::string indent, bool isTail)
{
    if (list.empty()) return;
    os << indent << (isTail ? "└── " : "├── ");
    os << "EnumeratorList" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    auto it = list.begin();
    if (list.size() > 1)
        for (; it != --list.end(); it++)
            (*it)->Print(os, indent, false);
    (*it)->Print(os, indent, true);
}

std::list<EnumeratorNode *> &EnumeratorList::List()
{
    return list;
}

void EnumeratorList::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void EnumSpecifierNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "enum" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (id)
    {
        if (enumeratorList)
        {
            id->Print(os, indent, false);
            enumeratorList->Print(os, indent, true);
            return;
        }
        id->Print(os, indent, true);
        return;
    }
    enumeratorList->Print(os, indent, true);
}

EnumSpecifierNode::EnumSpecifierNode(IdNode *id, EnumeratorList *enumeratorList) : id(id), enumeratorList(enumeratorList)
{
    this->kind = SpecifierKind::ENUM;
}

void EnumSpecifierNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void EnumeratorNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "Enumerator" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (value)
    {
        enumerationConstant->Print(os, indent, false);
        value->Print(os, indent, true);
        return;
    }
    enumerationConstant->Print(os, indent, true);
}

ExprNode *EnumeratorNode::GetValue() const
{
    return value;
}

void EnumeratorNode::SetValue(ExprNode *value)
{
    this->value = value;
}

IdNode *EnumeratorNode::GetId()
{
    return enumerationConstant;
}

EnumeratorNode::EnumeratorNode(IdNode *enumerationConstant, ExprNode *value) :
        enumerationConstant(enumerationConstant), value(value)
{
    this->type = new SymBuiltInType(BuiltInTypeKind::INT32);
}

ExprNode *EnumeratorNode::Eval(Evaluator *evaluator)
{
    return evaluator->Eval(this);
}

void EnumeratorNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void TypeSpecifierQualifierNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << value->text << std::endl;
}

TypeSpecifierQualifierNode::TypeSpecifierQualifierNode(std::shared_ptr<Token> value) : SimpleSpecifier(std::move(value)) {}

void TypeSpecifierQualifierNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void TypeSpecifierNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << value->text << std::endl;
}

TypeSpecifierNode::TypeSpecifierNode(std::shared_ptr<Token> specifier) : TypeSpecifierQualifierNode(std::move(specifier)) {}

void TypeSpecifierNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void TypeQualifierNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << value->text << std::endl;
}

TypeQualifierNode::TypeQualifierNode(std::shared_ptr<Token> qualifier) : TypeSpecifierQualifierNode(std::move(qualifier)) {}

void TypeQualifierNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void StorageClassSpecifierNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << value->text << std::endl;
}

StorageClassSpecifierNode::StorageClassSpecifierNode(std::shared_ptr<Token> specifier) : SimpleSpecifier(std::move(specifier)) {}

void StorageClassSpecifierNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void FunctionSpecifierNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << value->text << std::endl;
}

FunctionSpecifierNode::FunctionSpecifierNode(std::shared_ptr<Token> specifier) : SimpleSpecifier(std::move(specifier)) {}

void FunctionSpecifierNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void SimpleSpecifier::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << value->text << std::endl;
}

std::shared_ptr<Token> SimpleSpecifier::Value()
{
    return value;
}

SimpleSpecifier::SimpleSpecifier(std::shared_ptr<Token> specifier) : value(std::move(specifier)) { kind = SpecifierKind::SIMPLE; }

void SimpleSpecifier::Generate(Asm::Assembly *assembly)
{

}

void StructDeclaratorListNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    if (list.empty()) return;
    os << indent << (isTail ? "└── " : "├── ");
    os << "StructDeclaratorList" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    auto it = list.begin();
    if (list.size() > 1)
        for (; it != --list.end(); it++)
            (*it)->Print(os, indent, false);
    (*it)->Print(os, indent, true);
}

void StructDeclaratorListNode::Add(StructDeclaratorNode *initDeclarator)
{
    list.push_back(initDeclarator);
}

uint64_t StructDeclaratorListNode::Size()
{
    return list.size();
}

std::list<StructDeclaratorNode *> &StructDeclaratorListNode::List()
{
    return list;
}

void StructDeclaratorListNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void StructDeclarationNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "StructDeclaratorList" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    structDeclaratorList->Print(os, indent, true);
}

std::list<StructDeclaratorNode *> & StructDeclarationNode::List() const
{
    return structDeclaratorList->List();
}

void StructDeclarationNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

uint64_t StructDeclarationListNode::Size()
{
    return list.size();
}

void StructDeclarationListNode::Add(StructDeclarationNode *initDeclarator)
{
    list.push_back(initDeclarator);
}

void StructDeclarationListNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    if (list.empty()) return;
    os << indent << (isTail ? "└── " : "├── ");
    os << "StructDeclarationList" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    auto it = list.begin();
    if (list.size() > 1)
        for (; it != --list.end(); it++)
            (*it)->Print(os, indent, false);
    (*it)->Print(os, indent, true);
}

std::list<StructDeclarationNode *> &StructDeclarationListNode::List()
{
    return list;
}

void StructDeclarationListNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void StructSpecifierNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "struct" << std::endl;
    indent.append(isTail ? "    " : "│   ");
}

void StructSpecifierNode::SetId(IdNode *id)
{
    this->type->SetTag(id);
}

IdNode *StructSpecifierNode::GetId() const
{
    return this->type->GetTag();
}

SymRecord *StructSpecifierNode::GetRecordType() const
{
    return type;
}

void StructSpecifierNode::SetRecordType(SymRecord *type)
{
    this->type = type;
}

StructSpecifierNode::StructSpecifierNode(SymRecord *type, std::shared_ptr<Token> structToken) : type(type),
                                                                                                token(std::move(structToken))
{
    kind = SpecifierKind::STRUCT;
}

std::shared_ptr<Token> StructSpecifierNode::GetToken() const
{
    return token;
}

void StructSpecifierNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void StructDeclaratorNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "StructDeclarator" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (GetId()) GetId()->Print(os, indent, false);
    GetType()->Print(os, indent, constantExpr);
    if (constantExpr) constantExpr->Print(os, indent, true);
}

StructDeclaratorNode::StructDeclaratorNode(DeclaratorNode *declarator, ExprNode *constantExpr): constantExpr(constantExpr)
{
    SetId(declarator->GetId());
    SetType(declarator->GetType());
}

void StructDeclaratorNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

uint64_t InitializerListNode::Size()
{
    return list.size();
}

void InitializerListNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    if (list.empty()) return;
    os << indent << (isTail ? "└── " : "├── ");
    os << "InitializerList" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    auto it = list.begin();
    if (list.size() > 1)
        for (; it != --list.end(); it++)
            (*it)->Print(os, indent, false);
    (*it)->Print(os, indent, true);
}

void InitializerListNode::Add(InitializerNode *initializer)
{
    list.push_back(initializer);
}

std::list<InitializerNode *> &InitializerListNode::List()
{
    return list;
}

void InitializerListNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void DesignatorListNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    if (list.empty()) return;
    os << indent << (isTail ? "└── " : "├── ");
    os << "DesignatorList" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    auto it = list.begin();
    if (list.size() > 1)
        for (; it != --list.end(); it++)
            (*it)->Print(os, indent, false);
    (*it)->Print(os, indent, true);
}

void DesignatorListNode::Add(DesignatorNode *designator)
{
    list.push_back(designator);
}

uint64_t DesignatorListNode::Size()
{
    return list.size();
}

std::list<DesignatorNode *> &DesignatorListNode::List()
{
    return list;
}

void DesignatorListNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void ArrayDesignator::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "[]" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    index->Print(os, indent, true);
}

ArrayDesignator::ArrayDesignator(ExprNode *index) : index(index) {}

ExprNode *ArrayDesignator::GetIndex() const
{
    return index;
}

void ArrayDesignator::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void DesignationNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    designatorList->Print(os, indent, true);
}

DesignationNode::DesignationNode(DesignatorListNode *designatorList) : designatorList(designatorList) {}

std::list<DesignatorNode *> &DesignationNode::List()
{
    return designatorList->List();
}

void DesignationNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void StructMemberDesignator::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "." << std::endl;
    indent.append(isTail ? "    " : "│   ");
    id->Print(os, indent, true);
}

StructMemberDesignator::StructMemberDesignator(IdNode *id) : id(id) {}

IdNode *StructMemberDesignator::GetMemberId() const
{
    return id;
}

void StructMemberDesignator::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void DesignatedInitializerNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "DesignatedInitializer" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    if (designation) designation->Print(os, indent, false);
    initializer->Print(os, indent, true);
}

DesignatedInitializerNode::DesignatedInitializerNode(DesignationNode *designation, InitializerNode *initializer) :
        designation(designation), initializer(initializer) {}

DesignationNode *DesignatedInitializerNode::GetDesignation() const
{
    return designation;
}

InitializerNode *DesignatedInitializerNode::GetInitializer() const
{
    return initializer;
}

void DesignatedInitializerNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

void FunctionDefinitionNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "FuncDef" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    declarator->Print(os, indent, false);
    body->Print(os, indent, true);
}

void FunctionDefinitionNode::SetBody(CompoundStatement *body)
{
    this->body = body;
}

SymType *FunctionDefinitionNode::GetType() const
{
    return declarator->GetType();
}

FunctionDefinitionNode::FunctionDefinitionNode(DeclaratorNode *declarator, CompoundStatement *compoundStatement) :
        declarator(declarator), body(compoundStatement) {}

void FunctionDefinitionNode::Generate(Asm::Assembly *assembly)
{
    auto t = reinterpret_cast<SymFunction *>(GetType());
    auto fl = assembly->MakeFunctionLabel(t->GetName());
    auto rl = assembly->NextLabel();
    t->SetLabel(fl);
    t->SetReturnLabel(rl);
    Asm::Section &s = assembly->TextSection();
    s.AddLabel(fl);
    s.AddCommand(Asm::CommandName::PUSH, Asm::Register::EBP, Asm::CommandSuffix::L);
    s.AddCommand(Asm::CommandName::MOV, Asm::Register::ESP, Asm::Register::EBP, Asm::CommandSuffix::L);
    if (t->GetLocalVariablesStorageSize())
        s.AddCommand(Asm::CommandName::SUB, new IntConstNode(t->GetLocalVariablesStorageSize()), Asm::Register::ESP,
                     Asm::CommandSuffix::L);
    body->Generate(assembly);
    s.AddLabel(rl);
    s.AddCommand(Asm::CommandName::LEAVE);
    s.AddCommand(Asm::CommandName::RET);
}

void TranslationUnitNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    if (list.empty()) return;
    os << indent << (isTail ? "└── " : "├── ");
    os << "Unit" << std::endl;
    indent.append(isTail ? "    " : "│   ");
    auto it = list.begin();
    if (list.size() > 1)
        for (; it != --list.end(); it++)
            (*it)->Print(os, indent, false);
    (*it)->Print(os, indent, true);
}

void TranslationUnitNode::Add(ExternalDeclarationNode *initDeclarator)
{
    list.push_back(initDeclarator);
}

uint64_t TranslationUnitNode::Size()
{
    return list.size();
}

void TranslationUnitNode::Generate(Asm::Assembly *assembly)
{
    for (auto it = list.begin(); it != list.end(); it++)
        (*it)->Generate(assembly);
}

SpecifierKind DeclarationSpecifierNode::Kind()
{
    return kind;
}

SymType *ExprNode::GetType() const
{
    return type;
}

void ExprNode::SetType(SymType *type)
{
    this->type = type;
}

void ExprNode::SetValueCategory(ValueCategory category)
{
    this->category = category;
}

ValueCategory ExprNode::GetValueCategory() const
{
    return category;
}

void ExprNode::SetPosition(int row, int col)
{
    position = Position(row, col);
}

void ExprNode::SetPosition(Position position)
{
    this->position = position;
}

Position ExprNode::GetPosition() const
{
    return position;
}

void ExprNode::SetPosition(std::shared_ptr<Token> token)
{
    position = token->position;
}

void IterationStatementNode::SetBody(StatementNode *body)
{
    this->body = body;
}

Asm::AsmLabel *IterationStatementNode::ContinueLabel() const
{
    return continueLabel;
}

Asm::AsmLabel *IterationStatementNode::BreakLabel() const
{
    return breakLabel;
}

TypedefIdentifierNode::TypedefIdentifierNode(SymAlias *alias): alias(alias)
{
    this->kind = SpecifierKind::TYPEDEF;
}

std::shared_ptr<Token> TypedefIdentifierNode::GetToken()
{
    return id;
}

SymAlias *TypedefIdentifierNode::GetAlias() const
{
    return alias;
}

void TypedefIdentifierNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "Typedef " << std::endl;
    indent.append(isTail ? "    " : "│   ");
    alias->Print(os, indent, true);
}

void TypedefIdentifierNode::Generate(Asm::Assembly *assembly)
{
    // TODO
}

SimpleInitializer::SimpleInitializer(ExprNode *expr): value(expr) {}

void SimpleInitializer::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "Initializer " << std::endl;
    indent.append(isTail ? "    " : "│   ");
    value->Print(os, indent, true);
}

void SimpleInitializer::SetValue(ExprNode *value)
{
    this->value = value;
}

ExprNode *SimpleInitializer::GetValue() const
{
    return value;
}

void SimpleInitializer::Generate(Asm::Assembly *assembly)
{
    value->Generate(assembly);
}

void DesignatorNode::SetValue(InitializerNode *value)
{
    this->value = value;
}

PrintfNode::PrintfNode(StringLiteralNode *format, ArgumentExprListNode *arguments):
        format(format), arguments(arguments)
{
    type = new SymBuiltInType(BuiltInTypeKind::VOID);
}

void PrintfNode::Print(std::ostream &os, std::string indent, bool isTail)
{
    os << indent << (isTail ? "└── " : "├── ");
    os << "printf " << std::endl;
    indent.append(isTail ? "    " : "│   ");
    format->Print(os, indent, !arguments);
    if (arguments) arguments->Print(os, indent, true);
}

ExprNode *PrintfNode::Eval(Evaluator *evaluator)
{
    return nullptr;
}

void PrintfNode::Generate(Asm::Assembly *assembly)
{
    auto &s = assembly->TextSection();
    if (arguments) arguments->Generate(assembly);
    format->Generate(assembly);
    s.AddCommand(Asm::CommandName::PUSH, format->GetAddress(), true, Asm::CommandSuffix::L);
    s.AddCommand(Asm::CommandName::CALL, new Asm::AsmFunction("printf"));
    auto size = 4 + arguments->GetArgumentsSize();
    s.AddCommand(Asm::CommandName::ADD, new IntConstNode(size), Asm::Register::ESP, Asm::CommandSuffix::L);
}

IntConstNode *ConstNode::IntZero()
{
    static auto zero = new IntConstNode(0);
    return zero;
}

IntConstNode *ConstNode::IntOne()
{
    static auto one = new IntConstNode(1);
    return one;
}

FloatConstNode *ConstNode::FloatZero()
{
    static auto zero = new FloatConstNode(0.0f);
    return nullptr;
}

FloatConstNode *ConstNode::FloatOne()
{
    static auto one = new FloatConstNode(0.1f);
    return one;
}

void StatementNode::GenerateConditionCheck(Asm::Assembly *assembly, ExprNode *condition)
{
    using namespace Asm;
    auto &s = assembly->TextSection();
    auto ctype = condition->GetType()->GetUnqualified();
    auto btk = ctype->GetTypeKind() == TypeKind::POINTER ? BuiltInTypeKind::INT32 :
               reinterpret_cast<SymBuiltInType *>(ctype)->GetBuiltInTypeKind();
    switch (btk)
    {
        case BuiltInTypeKind::INT32:
            s.AddCommand(CommandName::POP, Register::EAX, CommandSuffix::L);
            s.AddCommand(CommandName::CMP, ConstNode::IntZero(), Register::EAX);
            break;
        case BuiltInTypeKind::FLOAT:
            s.AddCommand(CommandName::FLD, MakeAddress(Register::ESP), CommandSuffix::S);
            s.AddCommand(CommandName::FLDZ);
            s.AddCommand(CommandName::FCOMIP);
            s.AddCommand(CommandName::FSTP, Register::ST0);
            s.AddCommand(CommandName::POP, Register::EAX, CommandSuffix::L);
            break;
    }
}
