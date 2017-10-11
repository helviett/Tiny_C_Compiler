#include <iostream>
#include <tokenizer.h>
#include "includes/args.hxx"

int main(int argc, char **argv)
{
    args::ArgumentParser parser("This is tcc - Tiny C Compiler", "");
    args::HelpFlag help(parser, "help", "Display this menu", {'h', "help"});
    args::Group group(parser, "Stages of compilation(exclusive):", args::Group::Validators::Xor);
    args::Flag tokenize(group, "tokenize", "Tokenize only", {'t', "tokenize"});
    args::Positional<std::string> sourceFile(parser, "source file(s)", "The name(s) of source file(s)");
    try
    {
        parser.ParseCLI(argc, argv);
    }
    catch (args::Help)
    {
        std::cout << parser;
        return 0;
    }
    catch (args::ParseError e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }
    catch (args::ValidationError e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }
    if (!sourceFile)
        throw new std::exception();
    if (tokenize)
    {
        Tokenizer t;
        printf("Position\tType\tValue\t\t\tText\n\n");
        try
        {
            auto tokens = t.Tokenize(sourceFile.Get());
            for (int i = 0; i < tokens.size(); i++)
                switch (tokens[i]->type)
                {
                    case TokenType::NUM_INT:
                        printf("(%d, %d)\t\t%s\t%llu\t\t%s\n", tokens[i]->row, tokens[i]->col,
                               TokenTypeToString[tokens[i]->type].c_str(), tokens[i]->intValue,tokens[i]->text.c_str());
                        break;
                    case TokenType::NUM_FLOAT:
                        printf("(%d, %d)\t\t%s\t%llf\t\t%s\n", tokens[i]->row,
                               tokens[i]->col, TokenTypeToString[tokens[i]->type].c_str(), tokens[i]->floatValue, tokens[i]->text.c_str());
                        break;
                    default:
                        printf("(%d, %d)\t\t%s\t%s\t\t%s\n", tokens[i]->row, tokens[i]->col,
                               TokenTypeToString[tokens[i]->type].c_str(), tokens[i]->stringValue,tokens[i]->text.c_str());
                }

        }
        catch (LexicalError e)
        {
            std::cout << e.what();
            return 1;
        }
    }
	return 0;
}