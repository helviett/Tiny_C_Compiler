//
// Created by keltar on 10/8/17.
//

#include <tokenizer.h>
#include <iostream>

void Tokenizer::OpenFile(std::string fileName)
{

}

std::vector<Token *> Tokenizer::Tokenize(std::string fileName)
{
    buffer.reserve(256);
    currentState = 0;
    std::vector<Token *> result;
    currentFile.close();
    currentFile.open(fileName, std::ifstream::in);
    Token *currentToken = nullptr;
    while(currentToken = Next())
    {
        result.push_back(currentToken);
    }
    return result;

}

Token *Tokenizer::Next()
{
    currentlyProcessingTokenPos = currentPos;
    while (currentFile.get(currentCharacter))
    {
        if (currentCharacter == '\n')
        {
            currentPos.col = 0;
            currentPos.row++;
        }
        currentPos.col++;
        buffer.push_back(currentCharacter);
        bool getNewToken = false;
        processNewState(FiniteAutomata[currentState][currentCharacter], getNewToken);
        if (getNewToken)
            return getToken();
    }
    if (currentState != 0)
        return getToken();
    return nullptr;
}

Token *Tokenizer::Current()
{
    return currentToken;
}

Token *Tokenizer::getToken()
{

    auto res = AcceptStates.find(currentState);
    if (res == AcceptStates.end())
        throw new std::exception();
    else
    {
        currentPos.col--;
        currentFile.putback(currentCharacter);
        currentState = 0;
        Token *t = new Token(res->second, currentlyProcessingTokenPos.row, currentlyProcessingTokenPos.col, buffer);
        if (t->type == TokenType::ID)
        {
            if (Keywords.find(t->text) != Keywords.end())
                t->type = TokenType::KEYWORD;
        }
        buffer.resize(0);
        currentlyProcessingTokenPos = currentPos;
        return t;
    }
}
void Tokenizer::processNewState(int newState, bool &getTokenResult)
{

    if (newState == (int)SpecialFAStates::MultilineComment)
        parseMultilineComment();
    else if (newState == (int)SpecialFAStates::Comment)
        parseComment();
    else if (newState == -1 && currentState != 0)
    {
        buffer.pop_back();
        getTokenResult = true;
    }
    else
    {
        if (!newState)
        {
            buffer.resize(0);
            currentlyProcessingTokenPos = currentPos;
        }
        currentState = newState;
    }
}

void Tokenizer::parseMultilineComment()
{
    int nesting = 1;
    char buffer[2];
    while (nesting && currentFile.get(currentCharacter))
    {
        buffer[0] = buffer[1];
        buffer[1] = currentCharacter;
        if (buffer[0] == '/' && buffer[1] == '*')
            nesting++;
        if (buffer[0] == '*' && buffer[1] == '/')
            nesting--;
    }
    currentState = 0;
}

void Tokenizer::parseComment()
{
    while (currentFile.get(currentCharacter) && currentCharacter != '\n') ;
    currentState = 0;
}




