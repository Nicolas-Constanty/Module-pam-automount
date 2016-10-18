#ifndef IPARSER_H
#define IPARSER_H

#include <map>
#include <boost/variant.hpp>
#include "JsonVariant.hpp"
class IParser
{
  public:
    typedef std::map<std::string, JsonVariant> map_parser;
    virtual bool parse(map_parser *content) = 0;
};


#endif //IPARSER_H
