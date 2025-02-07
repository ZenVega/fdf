/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:46:15 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/07 15:22:18 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FRACTOL_H
# define FRACTOL_H
# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <X11/Xlib.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_cursor {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*file;
	int		width;
	int		height;
}	t_cursor;

typedef struct s_p {
	void		*mlx;
	void		*win;
	t_data		img;
	t_cursor	cursor;
	int			width;
	int			height;
	int			mouse_x;
	int			mouse_y;
}	t_p;

typedef struct s_vector {
	int	ax;
	int	ay;
	int	bx;
	int	by;
}	t_vector;

//fractol.c

//utils.c
unsigned int	shift_to_white(unsigned int color, int shift_val);
unsigned int	get_color_for_x(int x, int width);
int				on_keydown(int keycode, t_p *param);
int				on_resize(void);

//mouse_move.c
int				on_mouse_move(int x, int y, t_p *param);
int				on_mouse_enter(int keycode);
int				on_mouse_leave(int keycode);
int				on_close_window(t_p *param);

//create_grafics
void			let_it_snow(t_p param);
void			draw_noisy_square(t_p param);
void			draw_line(t_data *data, t_vector *vector);
void			pixel_put(t_data *data, int x, int y, int color);
#endif
