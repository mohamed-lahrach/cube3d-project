CC = cc #-fsanitize=address -g
CFLAGS = #-Wall -Wextra -Werror
INCLUDES = -I./lib/libft -I./get_next_line -I./inc -I./minilibx-linux
LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -lX11 -lXext -lm
GNL_SRCS = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
GNL_OBJS = $(GNL_SRCS:.c=.o)
PARSER_SRCS = parsing/parser.c parsing/parser1.c parsing/parser2.c parsing/parser3.c \
              parsing/parser4.c parsing/parser5.c parsing/parser6.c parsing/parser7.c \
              parsing/parser8.c parsing/parser9.c parsing/utils.c \
              parsing/utils2.c parsing/utils3.c
PARSER_OBJS = $(PARSER_SRCS:.c=.o)
ENGINE_SRCS = main.c raycasting.c render_3D_game.c utils.c input_handling.c raycasting_utils.c normalize_map.c utils_2.c
ENGINE_OBJS = $(ENGINE_SRCS:.c=.o)
OBJS = $(GNL_OBJS) $(PARSER_OBJS) $(ENGINE_OBJS)

NAME = cube3d

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Compile final executable
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

# Rule to compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Cleaning object files
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

# Full cleanup including executable
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Recompile everything
re: fclean all

.PHONY: all clean fclean re