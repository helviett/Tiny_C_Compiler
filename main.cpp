#include <iostream>
#include <tokenizer.h>
#include <parser.h>
#include "includes/args.hxx"

args::ArgumentParser parser("This is tcc - Tiny C Compiler", "");
args::HelpFlag help(parser, "help", "Display this menu", {'h', "help"});
args::Flag parseOnly(parser, "parse-only", "Parse only", {'p', "parse-only"});
args::Flag tokenizeOnly(parser, "tokenize-only", "Tokenize only", {'t', "tokenize-only"});
args::Positional<std::string> sourceFile(parser, "source file(s)", "The name(s) of source file(s)");

void TokenizeOnly()
{
    Tokenizer tok;
    printf("Position\t\tType\t\t\tValue\t\t\tText\n\n");
    try
    {
        tok.OpenFile(sourceFile.Get());
        Token *t;

        while ((t = tok.Next())->type != TokenType::END_OF_FILE)
            switch (t->type)
            {
                case TokenType::NUM_INT:
                    printf("(%d, %d)\t\t\t%s\t\t%llu\t\t%s\n", t->row, t->col,
                           TokenTypeToString[t->type].c_str(), t->intValue,t->text.c_str());
                    break;
                case TokenType::NUM_FLOAT:
                    printf("(%d, %d)\t\t\t%s\t\t%llf\t\t%s\n", t->row,
                           t->col, TokenTypeToString[t->type].c_str(), t->floatValue, t->text.c_str());
                    break;
                default:
                    printf("(%d, %d)\t\t\t%s\t\t%s\t\t%s\n", t->row, t->col,
                           TokenTypeToString[t->type].c_str(), t->stringValue,t->text.c_str());
            }

    }
    catch (LexicalError e)
    {
        std::cout << e.what();
        exit(1);
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
        parser.ParseCLI(argc, argv);
    }
    catch (args::Help)
    {
        std::cout << parser;
        return 0;
    }
    catch (args::ParseError &e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }
    catch (args::ValidationError &e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }
    if (!sourceFile)
        throw new std::exception();
    if (tokenizeOnly)
    {
        TokenizeOnly();
    }
    else if (parseOnly)
    {
        ParseOnly();
    }
	return 0;
}