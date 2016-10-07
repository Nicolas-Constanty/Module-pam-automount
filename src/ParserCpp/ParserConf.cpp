//
// Created by consta_n on 9/19/16.
//

#include "ParserConf.hpp"

ParserConf::ParserConf(ProducterStream &ps) : ConsumerParser(ps)
{}

//Conf ::= [SPACE KEY SPACE '=' SPACE VALUE ->'\n']* EOF;
bool ParserConf::parse(std::map<std::string,std::string>& content)
{
    _comment= '#';
    _ignore= "";
    return (
      repeater([&content, this] () { return (
        readChar('\n') |
        (
          readSpace() &&
          readKey(content) &&
          readSpace() &&
          readChar('=') &&
          readSpace() &&
          readValue(content) &&
          readUntil('\n')
        )
      );}, '*')
     && readEOF());
}

//Key ::=  ID;
bool ParserConf::readKey(std::map<std::string,std::string>& content)
{
    beginCapture("Name");
    bool ret = readIdentifier();
    endCapture("Name", _tmp_data);
    return (ret);
}

//Value ::=  ID;
bool ParserConf::readValue(std::map<std::string,std::string>& content)
{
    beginCapture(_tmp_data);
    bool ret = ConsumerParser::readValue();
    endCapture(_tmp_data, content[_tmp_data]);
    return (ret);
}

//Space ::= [' ' | '\t']*
bool ParserConf::readSpace()
{
  return (repeater([this] () { return (readChar(' ') | readChar('\t'));}, '*'));
}
