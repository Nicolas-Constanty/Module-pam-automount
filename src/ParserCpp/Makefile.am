# what flags you want to pass to the C compiler & linker
#AM_CPPFLAGS = --pedantic -Wall -std=c++11 -O2 -shared -fPIC -lpam -lcryptsetup
#AM_LDFLAGS = -lpam -lcryptsetup -L./LibCpp/ -lparser

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile
lib_LTLIBRARIES = libparser.la
libparser_la_LDFLAGS = libparser
libparser_la_SOURCES =  src/ConsumerParser.cpp \
                        src/Parser.cpp \
                        src/ParserConf.cpp \
                        src/ParserHttp.cpp \
                        src/ParserJson.cpp \
                        src/ProducterStream.cpp \
                        src/JsonVariant.cpp \
                        src/JsonException.cpp

libparser_la_CPPFLAGS = -std=c++11 -O2 -fPIC