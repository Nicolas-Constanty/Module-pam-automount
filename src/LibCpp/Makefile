NAME    =	test_parser

NAME_LIB    =	libparser.a

CC		=	g++

RM		=	rm -f

DIR 	= ParserCpp/

SRCS		=   $(DIR)ConsumerParser.cpp \
				$(DIR)Parser.cpp \
				$(DIR)ParserConf.cpp \
				$(DIR)ParserHttp.cpp \
				$(DIR)ParserJson.cpp \
				$(DIR)ProducterStream.cpp \
				$(DIR)JsonVariant.cpp \
				$(DIR)JsonException.cpp \
				$(DIR)main.cpp \

SRCS_LIB	=   $(DIR)ConsumerParser.cpp \
				$(DIR)Parser.cpp \
				$(DIR)ParserConf.cpp \
				$(DIR)ParserHttp.cpp \
				$(DIR)ParserJson.cpp \
				$(DIR)ProducterStream.cpp \
				$(DIR)JsonVariant.cpp \
				$(DIR)JsonException.cpp

OBJS		=	$(SRCS:.cpp=.o)

OBJS_LIB	=	$(SRCS_LIB:.cpp=.o)

CPPFLAGS	=	-std=c++11 -O2

#CPPFLAGS		+=	-W -Wall -Wextra

# LDFLAGS		= -lpam -lpam_misc
LDFLAGS		= -shared -Wl

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

$(NAME_LIB): $(OBJS_LIB)
	ar rcs $(NAME_LIB) $(OBJS_LIB)
	ranlib $(NAME_LIB)

all: $(NAME)

lib: $(NAME_LIB)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)
	$(RM) $(NAME_LIB)

re:	fclean all

.PHONY:	all clean fclean re
