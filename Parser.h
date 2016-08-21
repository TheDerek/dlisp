//
// Created by derek on 21/08/16.
//

#ifndef DLISP_PARSER_H
#define DLISP_PARSER_H


#include <string>
#include "Function.h"

class FunctionNotFoundExecption: std::exception {};


std::string parseFunction(std::string line, Database database, Functions functions)
{
    std::string name;
    Arguments arguments;
    bool named = false;

    for(std::string::iterator it = line.begin(); it != line.end(); ++it)
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
                    arg = parseFunction(
                        line.substr(it - line.begin(), line.size()),
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
