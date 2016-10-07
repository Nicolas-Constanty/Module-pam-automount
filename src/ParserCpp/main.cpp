#include <iostream>
#include "Parser.hpp"

int main(int ac, char **av)
{
    if (ac > 1)
    {
        Parser parser = Parser(CONF, av[1]);
        std::map<std::string, std::string> map;
        if (parser.parse(map))
        {
            for (std::pair<const std::string, std::string> &i : map)
            {
                std::cout << i.first << " = " << i.second << std::endl;
            }
        }
        else
            std::cout << "Fail" << std::endl;
    }
    return 0;
}
