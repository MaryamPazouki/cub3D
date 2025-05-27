NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
GNL_DIR = gnl
GNL = $(GNL_DIR)/libgnl.a
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

HEADER_FILES = includes/main_header.h \
				includes/map_validation.h \
				$(LIBFT_DIR)/libft.h \
				$(GNL_DIR)/get_next_line.h

INCLUDES = -I includes -I $(LIBFT_DIR) -I $(GNL_DIR) -I $(MLX_DIR)
MLX_LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRCS = main.c \
		print_debugging_fts.c \
		map_validation/map_validation.c \
		map_validation/map_parser.c \
		map_validation/map_validation_utils.c \
		make_environment/initialize_game_struct.c \
		make_environment/initialize_mlx.c \
		make_environment/raycasting.c \
		make_environment/handle_keys.c \
		make_environment/game_loop.c \
		make_environment/put_map.c \
		make_environment/put_map_utils.c \
		make_environment/put_minimap.c

SRC_DIR = srcs
OBJ_DIR = objs
OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(GNL):
	make -C $(GNL_DIR)

$(MLX):
	make -C $(MLX_DIR)

$(NAME): $(LIBFT) $(GNL) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBFT) $(GNL) $(MLX) $(INCLUDES) $(MLX_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER_FILES)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean
	make -C $(GNL_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(GNL_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

