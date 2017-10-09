//
// Created by keltar on 10/8/17.
//

#include <tokenizer.h>
#include <iostream>

Tokenizer::Tokenizer()
{

}

std::vector<Token *> Tokenizer::Tokenize(std::string fileName)
{
    OpenFile(fileName);
    std::vector<Token *> result;
    while(currentToken = Next())
    {
        result.push_back(currentToken);
    }
    return result;

}

Token *Tokenizer::Next()
{
    while (currentFile.get(currentCharacter))
    {
        int newState = FiniteAutomata[currentState][currentCharacter];
        if (newState == -1 && currentState != 0)
        {
            auto res = AcceptStates.find(currentState);
            if (res == AcceptStates.end())
                throw new std::exception();
            else
            {
                currentFile.putback(currentCharacter);
                currentState = 0;
                return new Token(res->second);
            }

        }
        else
            currentState = newState;
    }
    return nullptr;
}

Token *Tokenizer::Current()
{
    return currentToken;
}

void Tokenizer::OpenFile(std::string fileName)
{
    currentState = 0;
    currentFile.close();
    currentFile.open(fileName, std::ifstream::in);
    Token *currentToken = nullptr;
}


