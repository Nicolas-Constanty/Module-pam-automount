//
// Created by consta_n on 9/19/16.
//

#include "ParserConf.hpp"

ParserConf::ParserConf(ProducterStream &ps) : ConsumerParser(ps)
{}

//Conf ::= [SPACE KEY SPACE '=' SPACE VALUE ->'\n']* EOF;
bool ParserConf::parse(map_parser *content)
{
    _comment= '#';
    _ignore= " \t";
    bool ret;
    try {
        ret = (
                repeater([content, this] () { return (
                        readChar('\n') ||
                        (
                                readKey() &&
                                readChar('=') &&
                                readValue(content) &&
                                readUntil('\n')
                        )
                );}, '*')
                && readEOF());
    }
    catch (const std::exception &e)
    {
        std::cerr << "Json : " << e.what() << std::endl;
        ret = false;
    }
    return (ret);
}

//Key ::=  ID;
bool ParserConf::readKey()
{
    beginCapture("Name");
    bool ret = readIdentifier();
    endCapture("Name", _tmp_data);
    return (ret);
}

//Value ::=  ID;
bool ParserConf::readValue(map_parser *content)
{
    beginCapture(_tmp_data);
    bool ret = ConsumerParser::readValue();
    endCapture(_tmp_data,
               boost::get<std::string>((*content)[_tmp_data].get_value())
    );
    return (ret);
}

//Space ::= [' ' | '\t']*
bool ParserConf::readSpace()
{
  return (repeater([this] () { return (readChar(' ') | readChar('\t'));}, '*'));
}
