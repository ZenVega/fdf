/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:46:15 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/04 16:27:52 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_param {
	void	*mlx;
	void	*win;
}	t_param;

//utils.c
unsigned int	shift_to_white(unsigned int color, int shift_val);
unsigned int	get_color_for_x(int x, int width);
int				on_keydown(int keycode, t_param *param);
int				on_resize(void);

//mouse_move.c
int				on_mouse_move(int x, int y, t_param *param);
int				on_mouse_enter(int keycode);
int				on_mouse_leave(int keycode);
int				on_close_window(t_param *param);
