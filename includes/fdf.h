/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:46:15 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/12 17:31:04 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FDF_H
# define FDF_H

# include "constants.h"

# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"

# include <X11/Xlib.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

//map_processing.c
t_map			*create_map_matrix(t_list *data, t_map *map);
int				get_map_width(char *line);
void			color_matrix(t_map *map);

//input_processing.c
int				load_data(t_list **data, char **argv);

//inits.c
t_p				init_img(void);
t_map			*init_map(t_list *data, int height);
void			init_input_hooks(t_p *p);

//utils.c
unsigned int	shift_to_white(unsigned int color, int shift_val);
unsigned int	get_grad_col(int val, int max, unsigned int c_min,
					unsigned int c_max);
int				on_resize(void);
void			clean_up(t_map *map, t_list *data);

//hooks.c
int				on_mouse_move(int x, int y, t_p *param);
int				on_close_window(t_p *param);
int				on_keydown(int keycode, t_p *param);

//create_graphics
void			gen_noise(t_p *param);
void			draw_noisy_square(t_p param);
void			draw_line(t_p *p, t_point a, t_point b);
void			pixel_put(t_img *data, int x, int y, unsigned int color);
void			draw_mouse_vector(t_p *p);

//draw_map.c
void			draw_map(t_p *p);

#endif
