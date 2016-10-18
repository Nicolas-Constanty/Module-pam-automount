//
// Created by consta_n on 9/19/16.
//

#include "ParserJson.hpp"

ParserJson::ParserJson(ProducterStream &ps) : ConsumerParser(ps)
{
    key = false;
}

bool ParserJson::object(json_map* json_node, const std::string &context,
                        int index)
{
    return (readChar('{') &&
            repeater([this, json_node, context, index]{
                return (members(json_node, context, index));
            }, '?') &&
            readChar('}'));
}

bool ParserJson::members(json_map* json_node, const std::string &context,
                         int index)
{
    return (pair(json_node, context, index) &&
            repeater([this, json_node, context, index] () {
                return (readChar(',') && pair(json_node, context, index));
            }, '*'));
}

bool ParserJson::save_key(json_map* json_node,  const std::string &context, bool ret)
{
    beginCapture("key");
    ret = (ret && ConsumerParser::readValue());
    endCapture("key", _tmp_data);
    if (!context.empty())
    {
        json_array *&a = boost::get<json_array *&>(
                (*json_node)[context].getValue());
        if (!a)
            a = new std::vector<json_pair *>();
    }
    else
        (*json_node)[_tmp_data].getValue() = nullptr;
    return (ret);
}

bool ParserJson::save_value(json_map* json_node,  const std::string &context, bool ret, int index)
{
    std::string val;
    beginCapture("value");
    ret = (ret && ConsumerParser::readValue());
    endCapture("value", val);
    if (!context.empty())
    {
        json_array *a = boost::get<json_array *>(
                (*json_node)[context].getValue());
        if (a)
        {
            if (a->size() <= index)
            {
                json_pair *p = new json_pair();
                a->push_back(p);
            }
            json_pair *p = (*a)[index];
            (*p)[_tmp_data] = val;
        }
        else
            throw JsonException("Invalid array");
    }
    return (ret);
}

bool ParserJson::string(json_map* json_node, const std::string &context,
                        int index)
{
    bool ret = readChar('"');
    if (key)
        ret = save_key(json_node, context, ret);
    else
        ret = save_value(json_node, context, ret, index);
    return (ret && readChar('"'));
}

bool ParserJson::pair(json_map* json_node, const std::string &context,
                      int index)
{
    bool ret;
    key = true;
    ret = value(json_node, context);
    key = false;
    return (ret && readChar(':') && value(json_node, context, index));
}

bool ParserJson::value(json_map* json_node, const std::string &context,
                       int index)
{
    return (object(json_node, context, index)||
            array(json_node, context, index) ||
            string(json_node, context, index));
}

bool ParserJson::elements(json_map* json_node, const std::string &context,
                          int index)
{
    int idx = 0;
    return ( value(json_node, context) &&
            repeater([this, json_node, context, idx] () {
                static int i = idx;
                if (!context.empty())
                    ++i;
                return(readChar(',') && value(json_node, context, i));
            }, '*'));
}

bool ParserJson::array(json_map* json_node, const std::string &context,
                       int index)
{
    bool ret = readChar('[');
    if (ret)
    {
        std::string ctx = _tmp_data;
        ret = ret &&
                repeater([this, json_node, ctx, index] () {
                    return (elements(json_node, ctx, index));
                }, '?') &&
                readChar(']');
    }
    else
        ret = ret &&
                repeater([this, json_node, context, index] () {
                    return (elements(json_node, context, index));
                }, '?') &&
                readChar(']');
    return (ret);
}
std::ostream& operator<<(std::ostream& out, const json_array* jsarray)
{
    for (int j = 0; j < jsarray->size(); ++j) {
        json_pair *elem = (*jsarray)[j];
        out << "    ";
        int n = 0;
        for (json_pair::const_iterator k = elem->begin(); k != elem->end(); ++k) {
            ++n;
            out << "{\"" << (*k).first << "\" : \"" << (*k).second << "\"}";
            if (n != elem->size())
                out << ", ";
        }
        if (j < jsarray->size() - 1)
            out << ", ";
        out << std::endl;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const json_map* json)
{
    int n = 0;
    for (json_map::const_iterator i = json->begin(); i != json->end(); i++) {
        try {
            out << "{\"" << (*i).first << "\" : \""
                << boost::get<std::string>(((*i).second).get()) << "\"}";
            ++n;
            if (n != json->size())
                out << ", ";
        }
        catch (std::exception const &e)
        {
            out << "{\"" << (*i).first << "\" : [" << std::endl;
            json_array *a = (*i).second.get_array();
            out << a;
            out << "]}";
        }
    }
    return out;
}

bool ParserJson::parse(map_parser* content)
{
    _comment= '#';
    _ignore= "\t\n ";
    bool ret;
    try
    {
        ret = object(content) && readUntilEOF();
    }
    catch (std::exception const &e)
    {
        std::cerr << "Json : " << e.what() << std::endl;
        ret = false;
    }
    return (ret);
}