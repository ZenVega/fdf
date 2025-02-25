/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:39:00 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/12 19:19:43 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	pixel_put(t_p *p, int x, int y, unsigned int color)
{
	int		offset;
	char	*dst;
	t_img	*img;

	img = &p->img;
	if (x > 0 && x < WIN_WIDTH && y > 0 && y < WIN_HEIGHT)
	{
		offset = y * img->line_length + x * (img->bits_per_pixel / 8);
		dst = img->addr + offset;
		*(unsigned int *)dst = color;
	}
}

unsigned int	get_grad_col(int val, int max,
		unsigned int c_min, unsigned int c_max)
{
	int		d_r;
	int		d_g;
	int		d_b;
	float	factor;

	factor = (float)val / (float)max;
	d_r = (c_max >> 16 & 0xFF) - (c_min >> 16 & 0xFF);
	d_g = (c_max >> 8 & 0xFF) - (c_min >> 8 & 0xFF);
	d_b = (c_max & 0xFF) - (c_min & 0xFF);
	return (
		(0xFF << 24)
		| ((c_min >> 16 & 0xFF) + (int)(factor * d_r)) << 16
		| ((c_min >> 8 & 0xFF) + (int)(factor * d_g)) << 8
		| ((c_min & 0xFF) + (int)(factor * d_b)));
}

void	clean_up(t_map *map, t_list *data)
{
	int	i;

	if (data)
	{
		ft_lstclear(&data, free);
		(free(data), data = NULL);
	}
	if (map && map->matrix)
	{
		i = 0;
		while (i < map->depth && map->matrix[i])
			free(map->matrix[i++]);
		(free(map->matrix), map->matrix = NULL);
	}
	if (map)
		(free(map), map = NULL);
}

void	close_program(t_p *p, t_map *map)
{
	if (p->img.img)
		mlx_destroy_image(p->mlx, p->img.img);
	p->img.img = NULL;
	if (p->win)
		mlx_destroy_window(p->mlx, p->win);
	mlx_destroy_display(p->mlx);
	free(p->mlx);
	p->mlx = NULL;
	clean_up(map, NULL);
}
