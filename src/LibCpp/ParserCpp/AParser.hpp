#ifndef APARSER_H
#define APARSER_H

#include "IParser.hpp"

class AParser : public IParser
{
  public:
    virtual bool parse(map_parser *content) = 0;
    virtual ~AParser() {};
  protected:
    std::string     _tmp_data;
};

#endif //APARSER_H
