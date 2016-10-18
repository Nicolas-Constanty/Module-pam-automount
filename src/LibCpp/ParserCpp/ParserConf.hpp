//
// Created by consta_n on 9/19/16.
//

#ifndef PARSERCONF_H
#define PARSERCONF_H
#include "AParser.hpp"
#include "ConsumerParser.hpp"

class ParserConf : public ConsumerParser, public AParser
{
public:
    ParserConf(ProducterStream &);
    virtual bool parse(map_parser *content);

  private:
    bool readValue(map_parser *content);
    bool readKey();
};


#endif //PARSERCONF_H
