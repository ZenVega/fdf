SRC_FOLDER	= src/

CFILES		= \
			fdf.c\
			$(SRC_FOLDER)create_graphics.c\
			$(SRC_FOLDER)draw_map.c\
			$(SRC_FOLDER)hooks.c\
			$(SRC_FOLDER)inits.c\
			$(SRC_FOLDER)input_processing.c\
			$(SRC_FOLDER)map_processing.c\
			$(SRC_FOLDER)utils.c\
			$(SRC_FOLDER)rotations.c\
			gnl/get_next_line.c\
			gnl/get_next_line_utils.c\

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

DEPS		= includes/fdf.h\
			  gnl/get_next_line.h

CC			= gcc

CFLAGS		= -g -Wall -Wextra -Werror

NAME		= fdf

all: $(NAME) 

debug: $(NAME)
	gdb --args ./fdf 42.fdf

$(NAME): $(OFILES) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OFILES) $(MLX) $(LIBFT) $(INC) -lXext -lX11 -lm -lz

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_PATH)

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
