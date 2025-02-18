/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:46:15 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/17 15:20:41 by uschmidt         ###   ########.fr       */
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

//fdf.c
int				render_frames(t_p *p);

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
void			reset_params(t_p *p);

//utils.c
unsigned int	shift_to_white(unsigned int color, int shift_val);
unsigned int	get_grad_col(int val, int max, unsigned int c_min,
					unsigned int c_max);
int				on_resize(void);
void			clean_up(t_map *map, t_list *data);

//hooks.c
int				on_close_window(t_p *param);
int				on_key_down(int keycode, t_p *param);
int				on_key_release(int keycode, t_p *param);
int				on_mouse_click(int button, int x, int y, t_p *p);

//create_graphics
void			gen_noise(t_p *param);
void			draw_noisy_square(t_p param);
void			draw_line(t_p *p, t_point a, t_point b);
void			pixel_put(t_img *data, int x, int y, unsigned int color);
void			draw_mouse_vector(t_p *p);

//rotations.c
void			get_angles(t_ang *angles,
					double ang_x, double ang_y, double ang_z);
void			rotate(t_p *p, int keycode);
void			calc_point(int x, int y, t_proj proj, t_p *p);
void			rotate_point(t_point *point, t_p *p);
void			project_point(t_point *point, t_proj proj);
void			permanent_rotation(t_p *p, int keycode);

//draw_map.c
void			draw_map(t_p *p);

#endif
