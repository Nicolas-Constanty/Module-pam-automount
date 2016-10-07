PATH_LIB	=	./PamDebian/pam_modules

NAME		=	$(PATH_LIB)/pam_test.so

CC		=	g++

RM		=	rm -f

SRCS		=	src/pam_automount.cpp \

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-fPIC -DPIC -shared -rdynamic

#CPPFLAGS		+=	-W -Wall -Wextra

#LDFLAGS		= \

$(NAME):	$(OBJS)
	mkdir -p $(PATH_LIB)
	$(CC) $(CPPFLAGS) -o $(NAME) $(SRCS) #$(LDFLAGS)

all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
