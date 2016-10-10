PATH_LIB	=	./PamDebian/pam_modules

NAME		=	$(PATH_LIB)/pam_automount.so
NAME_LIB    =	$(PATH_LIB)/libautomount.a

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
	$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME) #$(LDFLAGS)
	#./PamDebian/export.sh

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
