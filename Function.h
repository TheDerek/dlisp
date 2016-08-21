#ifndef DLISP_FUNCTION_H
#define DLISP_FUNCTION_H

#include <unitypes.h>
#include <string>
#include <unordered_map>
#include <list>
#include <functional>
#include <vector>

using Arguments = std::vector<std::string>;
using Database = std::unordered_map<std::string, std::string>;
using Action = std::function<
    // Action returns a string, the result of calling Action.
    std::string (
        // The number of arguments that action supports.
        int8_t,
        // The list of Arguments provided to action.
        Arguments,
        // The current programs memory.
        Database
    )>;

class Function
{
    public:
        // The number of arguments the function takes
        const int8_t argc;

        // The action this function performs when it is run
        const Action action;

        /**
         * Create a new callable Function.
         * @param name The name to use when calling this function.
         * @param argc The number of agruments this function takes.
         * @param action The action this function performs when called.
         */
        Function(int8_t argc, Action action): argc(argc), action(action) {};

        /**
         * Perform this functions action.
         * @param arguments The arguments provided to the function.
         * @param database The current database for this running program.
         * @return The results of this function.
         */
        std::string operator ()(Arguments arguments, Database database)
        {
            return run(arguments, database);
        }

        /**
         * Perform this functions action.
         * @param arguments The arguments provided to the function.
         * @param database The current database for this running program.
         * @return The results of this function.
         */
        std::string run(Arguments arguments, Database database)
        {
            if(arguments.size() != argc)
                throw IncorrectArgCountException();

            return action(argc, arguments, database);
        }

    private:
        class IncorrectArgCountException: std::exception {};
};

using Functions = std::unordered_map<std::string, Function*>;



#endif //DLISP_FUNCTION_H
