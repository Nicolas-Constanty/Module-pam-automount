PATH_LIB	=	./PamDebian/pam_modules/

NAME		=	$(PATH_LIB)pam_test.so

CC		=	gcc

RM		=	rm -f

SRCS		=	src/test_coucou.c \

OBJS		=	$(SRCS:.c=.o)

CFLAGS		=	-fPIC -DPIC -shared -rdynamic

#CFLAGS		+=	-W -Wall -Wextra

#LDFLAGS		= \

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) #$(LDFLAGS)

all:	$(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
