SRC = get_next_line.c\
	  get_next_line_utils.c\
	   get_next_line_bonus.c\
	  get_next_line_utils_bonus.c\


NAME	=	get_next_line
OBJS = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra

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