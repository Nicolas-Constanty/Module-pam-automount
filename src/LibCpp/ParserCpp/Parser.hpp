#ifndef PARSER_H
#define PARSER_H

#include "ProducterStream.hpp"
#include "AParser.hpp"
#include "ParserConf.hpp"
#include "ParserHttp.hpp"
#include "ParserJson.hpp"

#define  CONF 0
#define  HTTP 1
#define  JSON 2


class Parser : public IParser {
private:
    typedef void (Parser::*FP)();
    ProducterStream _ps;
    AParser *_pc;
public:
    Parser (int type);
    Parser (int type, char *filename);
    virtual ~Parser ();

    void init_Conf();
    void init_Http();
    void init_Json();
    virtual bool parse(map_parser *content);
};


#endif //PARSER_H
