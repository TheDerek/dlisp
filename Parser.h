//
// Created by derek on 21/08/16.
//

#ifndef DLISP_PARSER_H
#define DLISP_PARSER_H


#include <string>
#include "Function.h"

class FunctionNotFoundExecption: std::exception {};

/**
 * Parse the given code and produce a string result.
 * @param code The given code to parse.
 * @param database The storage database of the running program.
 * @param functions The functions avliable to the program.
 * @return The result of the parsing.
 */
std::string parse(std::string code, Database database, Functions functions)
{
    std::string name;
    Arguments arguments;
    bool named = false;

    for(std::string::iterator it = code.begin(); it != code.end(); ++it)
    {
        if(*it == ')')
            break;

        // Capture the name
        if(*it== '(')
        {
            named = true;
            it++;
            while (*it != ' ' && *it != ')')
            {
                name += *it;
                it++;
            }

        }

        // Capture the arguments
        if(*it == ' ')
        {
            std::string arg;
            it++;
            while(*it != ' ' && *it != ')')
            {
                if(*it == '(')
                {
                    // Add the argument as the result of the function
                    arg = parse(
                        code.substr(it - code.begin(), code.size()),
                        database,
                        functions
                    );

                    // Skip over until the closing bracket
                    int depth = 1;
                    do {
                        it++;

                        if(*it == '(')
                            depth++;

                        if(*it == ')')
                            depth--;

                    } while(depth != 0);
                    it++;
                    break;
                }
                else
                {
                    arg += *it.base();
                    it++;
                }
            }
                arguments.push_back(arg);
                it--;
        }
    }

    if(functions.count(name) < 1)
        throw FunctionNotFoundExecption();

    return functions[name]->run(arguments, database);
}

#endif //DLISP_PARSER_H
