#include <iostream>
#include "Parser.hpp"

int main(int ac, char **av)
{
    if (ac > 1)
    {
        Parser parser = Parser(JSON, av[1]);
        JsonVariant::json_pair *map = new JsonVariant::json_pair();
        if (parser.parse(map))
        {
            std::cout << map << std::endl;
            std::cout << (*map)["conf"][0]["toto"][1]["filename"]() << std::endl;
            std::cout << (*map)["conf"][0]["toto"][1]["keyfile"]() << std::endl;
            delete map;
        }
        else
            std::cout << "Fail" << std::endl;
    }
    return 0;
}
