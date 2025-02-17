/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:22:56 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/17 12:17:30 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_p	init_img(void)
{
	static t_p	p;

	p.mlx = mlx_init();
	p.noise = -1;
	p.projection = 2;
	p.zoom = 1;
	p.width = WIN_WIDTH;
	p.height = WIN_HEIGHT;
	p.win = mlx_new_window(p.mlx, p.width, p.height, "Wrecktal!");
	p.img.img = mlx_new_image(p.mlx, p.width, p.height);
	p.img.addr = mlx_get_data_addr(p.img.img, &p.img.bits_per_pixel,
			&p.img.line_length, &p.img.endian);
	get_angles(&p.angles, 90, 0, 0);
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
	mlx_key_hook(p->win, on_keydown, p);
	mlx_hook(p->win, 6, 1L << 6, on_mouse_move, p);
	mlx_hook(p->win, 17, (1L << 17), on_close_window, p);
}
