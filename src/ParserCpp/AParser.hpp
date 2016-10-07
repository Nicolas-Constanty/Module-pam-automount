#ifndef APARSER_H
#define APARSER_H

#include "IParser.hpp"

class AParser
{
  public:
    virtual bool parse(std::map<std::string,std::string>& content) = 0;
  protected:
    std::string     _tmp_data;
};


#endif //APARSER_H
