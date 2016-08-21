#include <iostream>
#include <unordered_map>

#include "Function.h"
#include "Parser.h"
#include "dlib.h"


int main()
{
    // Setup the database for our program
    Database db;
    auto functions = getDlib();

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
        std::cout << parse(input, db, functions) << std::endl;
    }

    return 0;
}