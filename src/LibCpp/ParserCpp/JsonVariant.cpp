//
// Created by babiole on 17/10/16.
//

#include "JsonVariant.hpp"

JsonVariant::JsonVariant()
{
    value = boost::variant<std::string, json_array *>();
};

boost::variant<std::string, json_array *> &JsonVariant::getValue()
{
    return value;
};
const boost::variant<std::string, json_array *> &JsonVariant::get() const
{
    return value;
};


json_array *JsonVariant::get_array() const
{
    return boost::get<json_array *>(value);
};

const std::string &JsonVariant::operator[](const std::string &key) const
{
    const std::string &s = boost::get<std::string>(value);
    return (s);
}

const json_pair &JsonVariant::operator[](int key) const
{
    try {
        json_array *a = boost::get<json_array *>(value);
        if (key >= a->size())
            throw JsonException("Out of Range");
        json_pair *p = (*a)[key];
        return (*p);
    }
    catch (boost::exception const &e) {
        throw JsonException("Element is not an array");
    }
}

