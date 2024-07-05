SRC = 	


NAME	=	
OBJS = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra

//-D BUFFER_SIZE=42 <files>.c
RM = rm -rf
AR = ar crs

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)		

re:	fclean all

.PHONY:	all clean fclean re