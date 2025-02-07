SRC_FOLDER	= src/

CFILES		= \
			fractol.c\
			$(SRC_FOLDER)utils.c\
			$(SRC_FOLDER)mouse_move.c\
			$(SRC_FOLDER)create_graphics.c\

OFILES 		= $(CFILES:.c=.o)

MLX_PATH	= minilibx/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

INC			= \
			-I ./$(LIBFT_PATH)\
			-I ./$(MLX_PATH)

DEPS		= includes/fractol.h

CC			= gcc

CFLAGS		= -g -Wall -Wextra -Werror

NAME		= fractol

all: $(NAME) 

$(NAME): $(OFILES) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OFILES) $(MLX) $(LIBFT) $(INC) -lXext -lX11 -lm -lz

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

$(MLX):
	$(MAKE) -C $(MLX_PATH)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -I/usr/include $(INC) -g -c $< -o $@

clean:
	rm -f $(OFILES)
	find $(SRC_FOLDER) -name "*.o" -delete
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(MLX_PATH) clean

fclean:	clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
