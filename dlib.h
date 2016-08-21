//
// Created by derek on 21/08/16.
//

#ifndef DLISP_DLIB_H
#define DLISP_DLIB_H

/**
 * The dlisp standard library.
 */

#include "Function.h"

namespace {
    Function helloWorld(
        0, [](int8_t argc, Arguments arguments, Database database)
        {
            return "Hello World!";
        }
    );

    Function add(
        2, [](int8_t argc, Arguments arguments, Database database)
        {
            float x = std::stoi(arguments[0]);
            float y = std::stoi(arguments[1]);

            auto result = x + y;

            return std::to_string(result);
        }
    );

    Function subtract(
        2, [](int8_t argc, Arguments arguments, Database database)
        {
            float x = std::stoi(arguments[0]);
            float y = std::stoi(arguments[1]);

            auto result = x - y;

            return std::to_string(result);
        }
    );

    Function multiply(
        2, [](int8_t argc, Arguments arguments, Database database)
        {
            float x = std::stof(arguments[0]);
            float y = std::stof(arguments[1]);

            auto result = x * y;

            return std::to_string(result);
        }
    );

    Function divide(
        2, [](int8_t argc, Arguments arguments, Database database)
        {
            float x = std::stof(arguments[0]);
            float y = std::stof(arguments[1]);

            auto result = x / y;

            return std::to_string(result);
        }
    );

    // TODO: Implement ifThen function
    /*Function ifThen(
        2, [](int8_t argc, Arguments arguments, Database database)
        {
            //TODO: Check to make sure arguments are of a valid type
        }
    );*/
}

// Our list of functions
Functions getDlib()
{
    auto functions = Functions();
    functions.insert(std::make_pair("hello-world", &helloWorld));
    functions.insert(std::make_pair("+", &add));
    functions.insert(std::make_pair("-", &subtract));
    functions.insert(std::make_pair("*", &multiply));
    functions.insert(std::make_pair("/", &divide));

    return functions;
}




#endif //DLISP_DLIB_H
