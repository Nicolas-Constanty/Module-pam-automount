# what flags you want to pass to the C compiler & linker
#AM_CPPFLAGS = --pedantic -Wall -std=c++11 -O2 -shared -fPIC -lpam -lcryptsetup
#AM_LDFLAGS = -lpam -lcryptsetup -L./LibCpp/ -lparser

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile
lib_LTLIBRARIES = libpam_automount.la
libpam_automount_la_LDFLAGS = libpam_automount -lpam -lcryptsetup -L../ParserCpp/ -lparser
libpam_automount_la_SOURCES =  src/pam_automount.cpp \
                                src/Command.cpp \
                                src/User.cpp

libpam_automount_la_CPPFLAGS = -std=c++11 -O2 -shared