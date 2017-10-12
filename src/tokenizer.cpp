//
// Created by keltar on 10/8/17.
//

#include <tokenizer.h>


void Tokenizer::OpenFile(std::string fileName)
{
    currentFile.close();
    currentFile.open(fileName, std::ifstream::in);
}

std::vector<Token *> Tokenizer::Tokenize(std::string fileName)
{
    buffer.reserve(256);
    currentState = 0;
    std::vector<Token *> result;
    OpenFile(std::move(fileName));
    while(Next()->type != TokenType::END_OF_FILE)
        result.push_back(currentToken);
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
        if (processNewState(FiniteAutomata[currentState][currentCharacter]))
            return currentToken = getToken();
    }
    if (currentState != 0)
        return currentToken = getToken();
    return new Token(TokenType::END_OF_FILE, currentPos.row, currentPos.col, "");
}

Token *Tokenizer::Current()
{
    return currentToken;
}

Token *Tokenizer::getToken()
{

    auto res = AcceptStates.find(currentState);
    if (res == AcceptStates.end())
        throw LexicalError(currentlyProcessingTokenPos.row, currentlyProcessingTokenPos.col, buffer);
    else
    {
        currentPos.col--;
        currentFile.putback(currentCharacter);
        currentState = 0;
        Token *t = new Token(res->second, currentlyProcessingTokenPos.row, currentlyProcessingTokenPos.col, buffer);
        try
        {
            if (t->type == TokenType::ID && Keywords.find(t->text) != Keywords.end())
                t->type = TokenType::KEYWORD;
            if (t->type == TokenType::NUM_INT)
            {
                if (buffer.length() >= 2 && (buffer[1] == 'x' || buffer[1] == 'X'))
                    t->intValue = std::stoull(buffer, nullptr, 16);
                else if (buffer[0] == '0')
                    t->intValue = std::stoull(buffer, nullptr, 8);
                else
                    t->intValue = std::stoull(buffer, nullptr, 10);
            }
            else if (t->type == TokenType::NUM_FLOAT)
            {
                t->floatValue = std::stold(buffer);
            }

            else
            {
                t->stringValue = (char *)malloc(buffer.length() + 1);
                strcpy(t->stringValue, buffer.c_str());
            }
        }
        catch (std::out_of_range &e)
        {
            throw LexicalError(currentlyProcessingTokenPos.row, currentlyProcessingTokenPos.col, buffer);
        }
        catch (std::invalid_argument &e)
        {
            throw LexicalError(currentlyProcessingTokenPos.row, currentlyProcessingTokenPos.col, buffer);
        }
        buffer.resize(0);
        currentlyProcessingTokenPos = currentPos;
        return t;
    }
}
bool Tokenizer::processNewState(int newState)
{

    if (newState == (int)SpecialFAStates::MultilineComment)
        parseMultilineComment();
    else if (newState == (int)SpecialFAStates::Comment)
        parseComment();
    else if (newState == -1 && currentState != 0)
    {
        buffer.pop_back();
        return true;
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
    return false;
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
    while (currentFile.get(currentCharacter))
        if (currentCharacter == '\n') break;
    buffer.resize(0);
    currentState = 0;
}




