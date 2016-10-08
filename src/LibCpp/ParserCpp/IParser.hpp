#ifndef IPARSER_H
#define IPARSER_H

#include <map>

class IParser
{
  public:
    virtual bool parse(std::map<std::string,std::string>& content) = 0;
};


#endif //IPARSER_H
