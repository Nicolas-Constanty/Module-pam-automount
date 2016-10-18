//
// Created by babiole on 17/10/16.
//

#ifndef PAMELA_JSONVARIANT_H
#define PAMELA_JSONVARIANT_H

#include <boost/variant.hpp>
#include "Json.hpp"
#include "JsonException.hpp"

class JsonVariant {
private:
    boost::variant<std::string, json_array *> value;
public:
    JsonVariant();
    boost::variant<std::string, json_array *> &get_value();
    const boost::variant<std::string, json_array *> &get() const;
    json_array *get_array() const;
    const std::string &operator[](const std::string &key);
    json_pair operator[](int key);
};


#endif //PAMELA_JSONVARIANT_H
