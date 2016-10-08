#include "Parser.hpp"



Parser::Parser (int type)
{
    FP funcs[2] = {&Parser::init_Conf, &Parser::init_Http};
    _ps.loadStdin();
    (this->*funcs[type])();
}


Parser::Parser (int type, char *filename)
{
    FP funcs[2] = {&Parser::init_Conf, &Parser::init_Http};
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

bool Parser::parse(std::map<std::string,std::string>& content)
{
    return _pc->parse(content);
}
