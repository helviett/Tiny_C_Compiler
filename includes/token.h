//
// Created by keltar on 10/8/17.
//

#ifndef TINY_C_COMPILER_TOKEN_H
#define TINY_C_COMPILER_TOKEN_H

#include <string>
#include <unordered_map>
#include <utility>

enum class TokenType
{
    ID, NUM_INT, NUM_FLOAT,
    LBRACKET, RBRACKET, LCURLY_BRACKET, RCURLY_BRACKET, LSQUARE_BRACKET, RSQUARE_BRACKET,
    SEMICOLON, COLON, DOT, QUESTION_MARK, COMMA,
    RELOP_EQ, RELOP_GT, RELOP_LT, RELOP_GE, RELOP_LE, RELOP_NE, ASSIGNMENT,
    BITWISE_NOT, REMINDER, BITWISE_LSHIFT, BITWISE_RSHIFT, BITWISE_OR, BITWISE_XOR, BITWISE_AND,
    LOGIC_NO, LOGIC_OR, LOGIC_AND, MINUS, PLUS, ASTERIX, DOUBLE_PLUS, DOUBLE_MINUS,
    ASSIGNMENT_BY_SUM, ASSIGNMENT_BY_DIFFERENCE, ASSIGNMENT_BY_PRODUCT, ASSIGNMENT_BY_QUOTIENT, ASSIGNMENT_BY_REMINDER,
    ASSIGNMENT_BY_BITWISE_OR, ASSIGNMENT_BY_BITWISE_XOR, ASSIGNMENT_BY_BITWISE_AND, ASSIGNMENT_BY_BITWISE_LSHIFT,
    ASSIGNMENT_BY_BITWISE_RSHIFT,
    BACK_SLASH, FORWARD_SLASH, ARROW, KEYWORD, CHARACTER, STRING, END_OF_FILE
};

enum class Keyword
{
    BREAK, CASE, CHAR, CONST, CONTINUE, DEFAULT, DO, DOUBLE, ELSE, ENUM,
    EXTERN, FLOAT, FOR, GOTO, IF, INT, LONG, REGISTER, RETURN, SHORT,
    SIGNED, SIZEOF, STATIC, STRUCT, TYPEDEF, UNION, UNSIGNED, VOID, VOLATILE, WHILE, INLINE
};

static std::unordered_map<TokenType, std::string> TokenTypeToString(
{
    {TokenType::ASSIGNMENT_BY_BITWISE_RSHIFT, "ASSIGNMENT_BY_BITWISE_RSHIFT"},
    {TokenType::ASSIGNMENT_BY_BITWISE_LSHIFT, "ASSIGNMENT_BY_BITWISE_LSHIFT"},
    {TokenType::ASSIGNMENT_BY_BITWISE_XOR, "ASSIGNMENT_BY_BITWISE_XOR"},
    {TokenType::ASSIGNMENT_BY_BITWISE_AND, "ASSIGNMENT_BY_BITWISE_AND"},
    {TokenType::ASSIGNMENT_BY_DIFFERENCE, "ASSIGNMENT_BY_DIFFERENCE"},
    {TokenType::ASSIGNMENT_BY_BITWISE_OR, "ASSIGNMENT_BY_BITWISE_OR"},
    {TokenType::ASSIGNMENT_BY_QUOTIENT, "ASSIGNMENT_BY_QUOTIENT"},
    {TokenType::ASSIGNMENT_BY_REMINDER, "ASSIGNMENT_BY_REMINDER"},
    {TokenType::ASSIGNMENT_BY_PRODUCT, "ASSIGNMENT_BY_PRODUCT"},
    {TokenType::ASSIGNMENT_BY_SUM, "ASSIGNMENT_BY_SUM"},
    {TokenType::LSQUARE_BRACKET, "LSQUARE_BRACKET"},
    {TokenType::RSQUARE_BRACKET, "RSQUARE_BRACKET"},
    {TokenType::LCURLY_BRACKET, "LCURLY_BRACKET"},
    {TokenType::RCURLY_BRACKET, "RCURLY_BRACKET"},
    {TokenType::BITWISE_LSHIFT, "BITWISE_LSHIFT"},
    {TokenType::BITWISE_RSHIFT, "BITWISE_RSHIFT"},
    {TokenType::QUESTION_MARK, "QUESTION_MARK"},
    {TokenType::FORWARD_SLASH, "FORWARD_SLASH"},
    {TokenType::DOUBLE_MINUS, "DOUBLE_MINUS"},
    {TokenType::BITWISE_NOT, "BITWISE_NOT"},
    {TokenType::DOUBLE_PLUS, "DOUBLE_PLUS"},
    {TokenType::BITWISE_AND, "BITWISE_AND"},
    {TokenType::BITWISE_XOR, "BITWISE_XOR"},
    {TokenType::ASSIGNMENT, "ASSIGNMENT"},
    {TokenType::BITWISE_OR, "BITWISE_OR"},
    {TokenType::BACK_SLASH, "BACK_SLASH"},
    {TokenType::NUM_FLOAT, "NUM_FLOAT"},
    {TokenType::SEMICOLON, "SEMICOLON"},
    {TokenType::LOGIC_AND, "LOGIC_AND"},
    {TokenType::CHARACTER, "CHARACTER"},
    {TokenType::LOGIC_OR, "LOBIC_OR"},
    {TokenType::LBRACKET, "LBRACKET"},
    {TokenType::RBRACKET, "RBRACKET"},
    {TokenType::RELOP_EQ, "RELOP_EQ"},
    {TokenType::RELOP_GT, "RELOP_GT"},
    {TokenType::RELOP_LT, "RELOP_LT"},
    {TokenType::RELOP_GE, "RELOP_GE"},
    {TokenType::RELOP_LE, "RELOP_LE"},
    {TokenType::RELOP_NE, "RELOP_NE"},
    {TokenType::LOGIC_NO, "LOGIC_NO"},
    {TokenType::REMINDER, "REMINDER"},
    {TokenType::NUM_INT, "NUM_INT"},
    {TokenType::ASTERIX, "ASTERIX"},
    {TokenType::KEYWORD, "KEYWORD"},
    {TokenType::STRING, "STRING"},
    {TokenType::COMMA, "COMMA"},
    {TokenType::MINUS, "MINUS"},
    {TokenType::COLON, "COLON"},
    {TokenType::ARROW, "ARROW"},
    {TokenType::PLUS, "PLUS"},
    {TokenType::DOT, "DOT"},
    {TokenType::ID, "ID"}
});

static std::unordered_map<std::string, Keyword> StringToKeyword
{
    {"register", Keyword::REGISTER},
    {"volatile", Keyword::VOLATILE},
    {"continue", Keyword::CONTINUE},
    {"unsigned", Keyword::UNSIGNED},
    {"default", Keyword::DEFAULT},
    {"typedef", Keyword::TYPEDEF},
    {"return", Keyword::RETURN},
    {"signed", Keyword::SIGNED},
    {"sizeof", Keyword::SIZEOF},
    {"static", Keyword::STATIC},
    {"struct", Keyword::STRUCT},
    {"double", Keyword::DOUBLE},
    {"extern", Keyword::EXTERN},
    {"const", Keyword::CONST},
    {"while", Keyword::WHILE},
    {"break", Keyword::BREAK},
    {"float", Keyword::FLOAT},
    {"short", Keyword::SHORT},
    {"union", Keyword::UNION},
    {"case", Keyword::CASE},
    {"char", Keyword::CHAR},
    {"else", Keyword::ELSE},
    {"enum", Keyword::ENUM},
    {"goto", Keyword::GOTO},
    {"long", Keyword::LONG},
    {"void", Keyword::VOID},
    {"for", Keyword::FOR},
    {"int", Keyword::INT},
    {"if", Keyword::IF},
    {"do", Keyword::DO}
};

struct Token
{
    TokenType type;
    int row, col;
    std::string text;
    union
    {
        char *stringValue;
        uint64_t intValue;
        long double floatValue;
        Keyword keyword;
    };
    Token(TokenType type, int row, int col, std::string text): type(type), row(row), col(col), text(std::move(text)) {}
};

#endif //TINY_C_COMPILER_TOKEN_H
