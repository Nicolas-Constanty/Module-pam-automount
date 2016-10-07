#include <iostream>
#include "ProducterStream.hpp"
#include "ConsumerParser.hpp"
#include "ParserConf.hpp"

int main(int ac, char **av) {
    ProducterStream ps = ProducterStream();
    ParserConf parser = ParserConf(ps);
    if (ac > 1)
    {
      ps.loadFile(av[1]);
      std::map<std::string, std::string> map;
      if (parser.parse(map)) {
          for (std::pair<const std::string, std::string> &i : map) {
              std::cout << i.first << " = " << i.second << std::endl;
          }
      }
      else
          std::cout << "Fail" << std::endl;
    }
    return 0;
}
