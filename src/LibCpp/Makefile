PATH_LIB	=	../../PamDebian/pam_modules

#NAME    =	$(PATH_LIB)/libautomount.a
NAME    =	test_parser

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

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-g -std=c++11

#CPPFLAGS		+=	-W -Wall -Wextra

# LDFLAGS		= -lpam -lpam_misc
LDFLAGS		= -shared -Wl

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
