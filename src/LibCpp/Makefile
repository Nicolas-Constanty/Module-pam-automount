PATH_LIB	=	../../PamDebian/pam_modules

NAME    =	$(PATH_LIB)/libautomount.a

CC		=	g++

RM		=	rm -f

DIR 	= ParserCpp/

SRCS		=	Command.cpp \
				# $(DIR)ConsumerParser.cpp \
				# $(DIR)Parser.cpp \
				# $(DIR)ParserConf.cpp \
				# $(DIR)ParserHttp.cpp \
				# $(DIR)ConsumerParser.cpp \
				# $(DIR)ProducterStream.cpp \

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-std=c++11 -fPIC -lpam

#CPPFLAGS		+=	-W -Wall -Wextra

# LDFLAGS		= -lpam -lpam_misc
LDFLAGS		= -shared -Wl

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
