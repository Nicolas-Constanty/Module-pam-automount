#include <iostream>
#include "Parser.hpp"

int main(int ac, char **av)
{
    if (ac > 1)
    {
        Parser parser = Parser(JSON, av[1]);
        IParser::map_parser *map = new IParser::map_parser();
        if (parser.parse(map))
        {
            std::cout << map << std::endl;
        }
        else
            std::cout << "Fail" << std::endl;
    }
    return 0;
}
