//
// Created by keltar on 10/8/17.
//

#ifndef TINY_C_COMPILER_TOKENIZER_H
#define TINY_C_COMPILER_TOKENIZER_H

#include "errors/tcc_exceptions.h"
#include "dfa.h"
#include "token.h"

#include <fstream>
#include <vector>
#include <unordered_set>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <utility>

static std::unordered_set<std::string> Keywords =
{
    "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum",
    "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short",
    "signed", "sizeof", "static", "struct", "typedef", "union", "unsigned", "void", "volatile", "while"
};

struct Position
{
    Position() {}
    Position(int row, int col): row(row), col(col) {}
    int row, col;
};

class Tokenizer
{
public:
    Tokenizer(): currentPos(1, 1) {}
    Tokenizer(std::string fileName);

    std::vector<Token *> Tokenize(std::string fileName);
    Token *Next();
    Token *Current();
    Token *Peek();
    void OpenFile(std::string fileName);
private:
    int currentState = 0;
    char currentCharacter = 0;
    Position currentPos;
    Position currentlyProcessingTokenPos;
    Token *currentToken;
    Token *nextToken;
    std::ifstream currentFile;
    std::string buffer;
    Token *getToken();
    bool processNewState(int state);
    void parseMultilineComment();
    void parseComment();
    void error(int state);
    char toChar();
    char *toString();
    char toEscape(char c);
};

#endif //TINY_C_COMPILER_TOKENIZER_H
