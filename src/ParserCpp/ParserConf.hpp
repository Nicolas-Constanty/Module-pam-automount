//
// Created by consta_n on 9/19/16.
//

#ifndef PARSERHTTP_H
#define PARSERHTTP_H
#include "AParser.hpp"
#include "ConsumerParser.hpp"

class ParserConf : public ConsumerParser, public AParser
{
public:
    ParserConf(ProducterStream &);
    virtual bool parse(std::map<std::string,std::string>& content);

  private:
    bool readValue(std::map<std::string,std::string>& content);
    bool readKey(std::map<std::string,std::string>& content);
    bool readSpace();
};


#endif //PARSERHTTP_H
