PATH_LIB	=	./PamDebian/pam_modules

NAME		=	$(PATH_LIB)/pam_test.so
NAME_LIB    =	$(PATH_LIB)/libautomount.a

CC		=	g++

RM		=	rm -f

DIR 	= src/

SRCS		=	$(DIR)pam_automount.cpp \
				$(DIR)Command.cpp

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-std=c++11 -shared -fPIC -lpam
# CPPFLAGS	+=	-L $(PATH_LIB) -Wl,-Bstatic -lautomount -Wl,-Bdynamic -lpam

#CPPFLAGS		+=	-W -Wall -Wextra

# LDFLAGS		= -lpam -lpam_misc
LDFLAGS		= -shared  #-L $(PATH_LIB) -lautomount

$(NAME):	$(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME) #$(LDFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
