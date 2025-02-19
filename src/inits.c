/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:22:56 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/18 17:36:41 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	reset_params(t_p *p)
{
	p->noise = -1;
	p->x_rot = 0;
	p->y_rot = 0;
	p->z_rot = 0;
	p->rot_timer = ROT_TIMER;
	p->rot_speed = ROT_TIMER;
	p->projection = 0;
	p->scale_factor = 1.0;
	p->zoom = 1;
	p->center_x = (double)WIN_WIDTH / 2;
	p->center_y = (double)WIN_HEIGHT / 2;
	get_angles(&p->angles, INIT_X_ANG, INIT_Y_ANG, INIT_Z_ANG);
}

t_p	init_img(void)
{
	static t_p	p;

	p.mlx = mlx_init();
	reset_params(&p);
	p.width = WIN_WIDTH;
	p.height = WIN_HEIGHT;
	p.syscol = 1;
	p.win = mlx_new_window(p.mlx, p.width, p.height, "Wrecktal!");
	p.img.img = mlx_new_image(p.mlx, p.width, p.height);
	p.img.addr = mlx_get_data_addr(p.img.img, &p.img.bits_per_pixel,
			&p.img.line_length, &p.img.endian);
	get_angles(&p.angles, INIT_X_ANG, INIT_Y_ANG, INIT_Z_ANG);
	return (p);
}

t_map	*init_map(t_list *data, int height)
{
	t_map	*map;
	t_list	*tmp;

	tmp = data;
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (clean_up(map, data), NULL);
	map->matrix = (t_point **)malloc(sizeof(t_point *) * height);
	if (!map->matrix)
		return (clean_up(map, data), NULL);
	map->width = get_map_width(data->content);
	map->depth = height;
	map->highest_z = INT_MIN;
	map->lowest_z = INT_MAX;
	map = create_map_matrix(data, map);
	color_matrix(map);
	clean_up(NULL, tmp);
	return (map);
}

void	init_input_hooks(t_p *p)
{
	mlx_mouse_hook(p->win, on_mouse_click, p);
	mlx_hook(p->win, 2, (1L << 0), on_key_down, p);
	mlx_hook(p->win, 3, (1L << 1), on_key_release, p);
	mlx_hook(p->win, 17, (1L << 17), on_close_window, p);
}

void	init_menu(t_p *p)
{
	get_keys(&p->menu);
	get_vals(&p->menu);
}
