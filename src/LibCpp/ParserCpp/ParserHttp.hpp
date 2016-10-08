//
// Created by consta_n on 9/19/16.
//

#ifndef PARSERHTTP_H
#define PARSERHTTP_H

#include "AParser.hpp"
#include "ConsumerParser.hpp"

class ParserHttp : public ConsumerParser, public AParser
{
public:
    ParserHttp(ProducterStream &);
    virtual bool parse(std::map<std::string,std::string>& content);
private:
    std::string     _tmp_data;

    bool readVersion();

    bool readCMD();

    bool readHeaderName();

    bool readURI();

    bool readData();

    bool readBody();

    bool readHeader(std::map<std::string,std::string>& content);

    bool readHeaderList(std::map<std::string,std::string>& content);

};


#endif //PYJOUR00_PARSERHTTP_H
