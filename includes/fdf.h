/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:46:15 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/11 17:38:19 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FDF_H
# define FDF_H

# include "constants.h"
# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include <X11/Xlib.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

//map_processing.c
int				load_data(t_list **data, char **argv);
t_map			*create_map_matrix(t_list *data, t_map *map);
t_map			*init_map(t_list *data, int height);

//utils.c
unsigned int	shift_to_white(unsigned int color, int shift_val);
unsigned int	get_color_for_x(int x, int width);
int				on_keydown(int keycode, t_p *param);
int				on_resize(void);
void			clean_up(t_map *map, t_list *data);

//hooks.c
void			init_hooks(t_p *p);
int				on_mouse_move(int x, int y, t_p *param);
int				on_close_window(t_p *param);

//create_graphics
void			let_it_snow(t_p *param);
void			draw_noisy_square(t_p param);
void			draw_line(t_data *data, t_vector *vector);
void			pixel_put(t_data *data, int x, int y, int color);
void			draw_mouse_vector(t_p *p);

//draw_map.c
void			draw_map(t_p *p);

#endif
