//
// Created by keltar on 10/8/17.
//

    #include <tokenizer.h>

Tokenizer::Tokenizer(std::string fileName)
{
    OpenFile(fileName);
}


void Tokenizer::OpenFile(std::string fileName)
{
    currentFile.close();
    currentFile.open(fileName, std::ifstream::in);
    Next();
}

std::vector<Token *> Tokenizer::Tokenize(std::string fileName)
{
    buffer.reserve(256);
    currentState = 0;
    std::vector<Token *> result;
//    OpenFile(std::move(fileName));
//    while(Next()->type != TokenType::END_OF_FILE)
//        result.push_back(currentToken);
    return result;

}

std::shared_ptr<Token> Tokenizer::Next()
{
    currentlyProcessingTokenPos = currentPos;
    currentToken = nextToken;
    while (currentFile.get(currentCharacter))
    {
        if (currentCharacter == '\n')
        {
            prevRowCol = currentPos.col;
            currentPos.col = 0;
            currentPos.row++;
        }
        if (!currentState) currentlyProcessingTokenPos = currentPos;
        currentPos.col++;
        buffer.push_back(currentCharacter);
        if (processNewState(FiniteAutomata[currentState][currentCharacter]))
        {
            nextToken = getToken();
            return currentToken;
        }
    }
    if (currentState != 0)
    {
        nextToken = getToken();
        return currentToken;
    }
    nextToken = std::make_shared<Token>(TokenType::END_OF_FILE, currentPos.row, currentPos.col, "");
    return currentToken;
}

std::shared_ptr<Token> Tokenizer::Current()
{
    auto debugging = currentToken.get();
    return currentToken;
}

std::shared_ptr<Token> Tokenizer::getToken()
{

    auto res = AcceptStates.find(currentState);
    if (res == AcceptStates.end())
        error(currentState);
    else
    {
        currentPos.col--;
        currentFile.putback(currentCharacter);
        if (currentCharacter == '\n')
        {
            currentPos.col = prevRowCol;
            currentPos.row--;
        }
        currentState = 0;
        auto t = std::make_shared<Token>(res->second, currentlyProcessingTokenPos.row, currentlyProcessingTokenPos.col, buffer);
        try
        {

            if (t->type == TokenType::ID && Keywords.find(t->text) != Keywords.end())
            {
                t->type = TokenType::KEYWORD;
                t->keyword = StringToKeyword[buffer];
            }
            else if (t->type == TokenType::NUM_INT)
            {
                if (buffer.length() >= 2 && (buffer[1] == 'x' || buffer[1] == 'X'))
                    t->intValue = std::stoull(buffer, nullptr, 16);
                else if (buffer[0] == '0')
                    t->intValue = std::stoull(buffer, nullptr, 8);
                else
                    t->intValue = std::stoull(buffer, nullptr, 10);
            }
            else if (t->type == TokenType::CHARACTER)
                t->intValue = (uint64_t)toChar();
            else if (t->type == TokenType::NUM_FLOAT)
            {
                t->floatValue = std::stold(buffer);
            }

            else
            {
                t->stringValue = toString();
            }
        }
        catch (std::out_of_range &e)
        {
            throw NumberOutOfRange(currentlyProcessingTokenPos.row, currentlyProcessingTokenPos.col, buffer);
        }
        catch (std::invalid_argument &e)
        {
            throw WrongNumberLiteral(currentlyProcessingTokenPos.row, currentlyProcessingTokenPos.col, buffer);
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
        error(currentState);
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

void Tokenizer::error(int state)
{
    switch (state)
    {
        case 5:case 10:case 70:case 11:case 68:
            throw WrongNumberLiteral(currentPos.row, currentPos.col, buffer);
        case 59:case 58:case 60:
            throw WrongStringLiteral(currentPos.row, currentPos.col, buffer);
        case -1:
            throw UnknownSymbol(currentPos.row, currentPos.col, buffer);
        case 63:case 65:case 62:
            throw WrongCharacterLiteral(currentPos.row, currentPos.col, buffer);
    }
}

char Tokenizer::toChar()
{
    if (buffer.length() == 3)
        return buffer[1];

    toEscape(buffer[3]);
}

char *Tokenizer::toString()
{
    char *res = new char[buffer.length() + 1];
    int i = 0;
    bool isEscape = false;
    for (char j : buffer)
    {
        if (j == '"' && !isEscape)
            continue;
        if (j == '\\' && !isEscape)
        {
            isEscape = true;
            continue;
        }
        res[i++] = isEscape ? toEscape(j) : j;
        if (isEscape) isEscape = false;
    }
    res[i++] = '\0';
    return res;
}

char Tokenizer::toEscape(char c)
{
    switch (c)
    {
        case 'n':
            return '\n';
        case 'a':
            return '\a';
        case 't':
            return '\t';
        case 'v':
            return '\v';
        case '?':
            return '\?';
        case '\\':
            return '\\';
        case '\'':
            return '\'';
        case 'b':
            return '\b';
        case 'f':
            return '\f';
        case '0':
            return '\0';
        case '\"':
            return '\"';
    }
}

std::shared_ptr<Token> Tokenizer::Peek()
{
    return nextToken;
}



