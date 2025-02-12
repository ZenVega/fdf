/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:06:37 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/12 18:56:43 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// width 1920 -> (1920 - (1920 / (10 / 2)))
// height 1080 -> (1080 - (1080 / (10 / 2)))
// padding 10 -> 192 // 108
// startpoint 192/108
// endpoint (1920-192) / (1080-108)

float	map_val(int val, float input_range, int low_out, int high_out)
{
	float	result;

	result = (float)val / input_range * ((float) high_out - (float)low_out);
	result += low_out;
	return (result);
}

void	draw_top_down(t_p *p)
{
	t_point	**matrix;
	int		x;
	int		y;

	x = 0;
	matrix = p->map->matrix;
	while (x < p->map->width)
	{
		y = 0;
		while (y < p->map->depth)
		{
			matrix[y][x].proj_x = map_val(x, p->map->width,
					(WIN_WIDTH / PADDING),
					(WIN_WIDTH - (WIN_WIDTH / PADDING)));
			matrix[y][x].proj_y = map_val(y, p->map->depth,
					(WIN_HEIGHT / PADDING),
					(WIN_HEIGHT - (WIN_HEIGHT / PADDING)));
			y++;
		}
		x++;
	}
}

void	create_projection(int id, t_p *p)
{
	if (id == 1)
		draw_top_down(p);
}

void	map_to_img(t_p *p)
{
	int		x;
	int		y;
	t_point	**matrix;

	matrix = p->map->matrix;
	x = 0;
	while (x < p->map->width)
	{
		y = 0;
		while (y < p->map->depth)
		{
			if (!(x == p->map->width - 1))
				draw_line(p, matrix[y][x], matrix[y][x + 1]);
			if (!(y == p->map->depth - 1))
				draw_line(p, matrix[y][x], matrix[y + 1][x]);
			pixel_put(&p->img, matrix[y][x].proj_x, matrix[y][x].proj_y, matrix[y][x].color);
			y++;
		}
		x++;
	}
}

void	draw_map(t_p *p)
{
	create_projection(1, p);
	map_to_img(p);
}
