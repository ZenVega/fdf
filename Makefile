CFILES		= \
			main.c\
			utils.c\

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

CC			= gcc

CFLAGS		= -g -Wall -Wextra -Werror

NAME		= fdfractal

all: $(NAME) 

$(NAME): $(OFILES) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OFILES) $(MLX) $(LIBFT) $(INC) -lXext -lX11 -lm -lz

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

$(MLX):
	$(MAKE) -C $(MLX_PATH)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -I/usr/include $(INC) -O3 -c $< -o $@

clean:
	rm -f *.o
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(MLX_PATH) clean

fclean:	clean
	$(MAKE) clean
	rm $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(MAKE) -C $(MLX_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
