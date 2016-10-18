#include "Parser.hpp"

Parser::Parser (int type)
{
    FP funcs[3] = {&Parser::init_Conf, &Parser::init_Http, &Parser::init_Json};
    _ps.loadStdin();
    (this->*funcs[type])();
}


Parser::Parser (int type, char *filename)
{
    FP funcs[3] = {&Parser::init_Conf, &Parser::init_Http, &Parser::init_Json};
    _ps.loadFile(filename);
    (this->*funcs[type])();
}

Parser::~Parser()
{
    delete _pc;
}

void Parser::init_Conf()
{
    _pc = new ParserConf(_ps);
}

void Parser::init_Http()
{
    _pc = new ParserHttp(_ps);
}

void Parser::init_Json()
{
    _pc = new ParserJson(_ps);
}

bool Parser::parse(map_parser *content)
{
    return _pc->parse(content);
}
