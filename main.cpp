#include <iostream>
#include <unordered_map>

#include "Function.h"
#include "Parser.h"


int main()
{
    // Setup the database for our program
    Database db;

    // Our list of functions
    auto functions = Functions();

    // Create some functions
    Function helloWorld(
        "hello-world", 0,
        [](int8_t argc, Arguments arguments, Database database)
        {
            return "Hello World!";
        }
    );

    functions.insert(std::make_pair("hello-world", &helloWorld));

    Function add(
        "add", 2,
        [](int8_t argc, Arguments arguments, Database database)
        {
            int32_t x = std::stoi(arguments[0]);
            int32_t y = std::stoi(arguments[1]);

            return std::to_string(x + y);
        }
    );

    functions.insert(std::make_pair("add", &add));


    std::cout << "Welcome to dlisp version 0.0.1." << std::endl;
    std::cout << "Type `exit` to exit." << std::endl;

    std::string input;
    while(true)
    {
        std::cout << "dlisp > ";
        getline(std::cin, input);
        //input = "(add (add 1 2) 2)";

        if(input == "exit")
            break;

        // Parse the function
        std::cout << parseFunction(input, db, functions) << std::endl;
    }

    return 0;
}