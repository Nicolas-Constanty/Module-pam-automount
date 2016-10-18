//
// Created by consta_n on 9/19/16.
//

#ifndef PARSERJSON_H
#define PARSERJSON_H

#include "AParser.hpp"
#include "ConsumerParser.hpp"
#include "JsonVariant.hpp"
#include "JsonException.hpp"

typedef IParser::map_parser json_map;

class ParserJson : public ConsumerParser, public AParser
{
public:
    ParserJson(ProducterStream &);
    virtual bool parse(map_parser *content);

private:
    bool key;

private:
    bool save_key(json_map* json_node,  const std::string &context, bool ret);
    bool save_value(json_map* json_node,  const std::string &context, bool ret, int index);
    bool members(json_map* json_node, const std::string &context = "", int index = 0);
    bool pair(json_map* json_node, const std::string &context = "", int index = 0);
    bool value(json_map* json_node, const std::string &context = "", int index = 0);
    bool array(json_map* json_node, const std::string &context = "", int index = 0);
    bool elements(json_map* json_node, const std::string &context = "", int index = 0);
    bool object(json_map* json_node, const std::string &context = "", int index = 0);
    bool string(json_map* json_node, const std::string &context = "", int index = 0);
};

std::ostream& operator<<(std::ostream& out, const json_map* json);
std::ostream& operator<<(std::ostream& out, const json_array* jsarray);

#endif //PARSERJSON_H
