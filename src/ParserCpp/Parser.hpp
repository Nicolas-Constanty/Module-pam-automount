#ifndef PARSER_H
#define PARSER_H

#include "ProducterStream.hpp"
#include "AParser.hpp"

class Parser {
private:
  ProducterStream ps;
  AParser *pc;
public:
  Parser ();
  virtual ~Parser ();

};


#endif //PARSER_H
