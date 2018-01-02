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
#include <memory>

static std::unordered_set<std::string> Keywords =
{
    "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum",
    "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short",
    "signed", "sizeof", "static", "struct", "typedef", "union", "unsigned", "void", "volatile", "while",
    "printf"
};

class Tokenizer
{
public:
    Tokenizer() {}
    Tokenizer(std::string fileName);

    std::vector<Token *> Tokenize(std::string fileName);
    std::shared_ptr<Token> Next();
    std::shared_ptr<Token> Current();
    std::shared_ptr<Token> Peek();
    void OpenFile(std::string fileName);
private:
    int currentState = 0;
    char currentCharacter = 0;
    int prevRowCol = 0;
    Position currentPos{1, 1};
    Position currentlyProcessingTokenPos;
    std::shared_ptr<Token> currentToken;
    std::shared_ptr<Token> nextToken;
    std::ifstream currentFile;
    std::string buffer;
    std::shared_ptr<Token> getToken();
    bool processNewState(int state);
    void parseMultilineComment();
    void parseComment();
    void error(int state);
    char toChar();
    char *toString();
    char toEscape(char c);
};

#endif //TINY_C_COMPILER_TOKENIZER_H
