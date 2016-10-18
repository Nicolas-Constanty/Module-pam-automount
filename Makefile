PATH_LIB	=	./PamDebian/pam_modules

NAME		=	$(PATH_LIB)/pam_automount.so

CC		=	g++

RM		=	rm -f

DIR 	= src/

SRCS		=	$(DIR)pam_automount.cpp \
				$(DIR)Command.cpp		\
				$(DIR)User.cpp		    \

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-std=c++11 -shared -fPIC -lpam -lcryptsetup

CPPFLAGS		+=	-W -Wall -Wextra

LDFLAGS		= -shared

$(NAME):	$(OBJS)
	$(MAKE) -C $(DIR)LibCpp/ lib
	$(CC) $(CPPFLAGS) $(OBJS) -L -$(SRC)LibCpp/lparser -o $(NAME)

all: $(NAME)

clean:
	$(MAKE) -C src/LibCpp/ clean
	$(RM) $(OBJS)

fclean:	clean
	$(MAKE) -C src/LibCpp/ fclean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
