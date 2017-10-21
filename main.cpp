#include <iostream>
#include <tokenizer.h>
#include <parser.h>
#include "includes/args.hxx"

args::ArgumentParser argParser("This is tcc - Tiny C Compiler", "");
args::HelpFlag help(argParser, "help", "Display this menu", {'h', "help"});
args::Flag parseOnly(argParser, "parse-only", "Parse only", {'p', "parse-only"});
args::Flag tokenizeOnly(argParser, "tokenize-only", "Tokenize only", {'t', "tokenize-only"});
args::Positional<std::string> sourceFile(argParser, "source file(s)", "The name(s) of source file(s)");

void TokenizeOnly()
{
    Tokenizer tok;
    printf("Position\t\tType\t\t\tValue\t\t\tText\n\n");
    tok.OpenFile(sourceFile.Get());
    Token *t;
    while ((t = tok.Next())->type != TokenType::END_OF_FILE)
        switch (t->type)
        {
            case TokenType::NUM_INT:case TokenType::CHARACTER:
                printf("(%d, %d)\t\t\t%s\t\t\t%llu\t\t\t\t  %s\n", t->row, t->col,
                       TokenTypeToString[t->type].c_str(), t->intValue,t->text.c_str());
                break;
            case TokenType::NUM_FLOAT:
                printf("(%d, %d)\t\t\t%s\t\t\t%llf\t\t\t\t  %s\n", t->row,
                       t->col, TokenTypeToString[t->type].c_str(), t->floatValue, t->text.c_str());
                break;
            default:
                printf("(%d, %d)\t\t\t%s\t\t\t%s\t\t\t\t  %s\n", t->row, t->col,
                       TokenTypeToString[t->type].c_str(), t->stringValue,t->text.c_str());
        }

}

void ParseOnly()
{
    Parser par(new Tokenizer(sourceFile.Get()));
    par.Parse();
    std::cout << par;
}

int main(int argc, char **argv)
{

    try
    {
        argParser.ParseCLI(argc, argv);
    }
    catch (args::Help)
    {
        std::cout << argParser;
        return 0;
    }
    catch (args::ParseError &e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << argParser;
        return 1;
    }
    catch (args::ValidationError &e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << argParser;
        return 1;
    }
    if (!sourceFile)
        throw new std::exception();
    try
    {
        if (tokenizeOnly)
        {
            TokenizeOnly();
        }
        else if (parseOnly)
        {
            ParseOnly();
        }
    }
    catch (CompilationError &e)
    {
        std::cout << e.what() << std::endl;
        exit(1);
    }
	return 0;
}