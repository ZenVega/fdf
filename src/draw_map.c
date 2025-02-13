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

float	map_val(float val, float input_range, int low_out, int high_out)
{
	float	result;

	result = val / input_range * ((float) high_out - (float)low_out);
	result += low_out;
	return (result);
}

void	draw_top_down(t_p *p)
{
	t_point	**matrix;
	int		x;
	int		y;
	double	x_start;
	double	y_start;

	x_start = ((double)WIN_WIDTH / PADDING);
	y_start = ((double)WIN_HEIGHT / PADDING);
	x = 0;
	matrix = p->map->matrix;
	while (x < p->map->width)
	{
		y = 0;
		while (y < p->map->depth)
		{
			matrix[y][x].proj_x = map_val((float)(x + 0.5), p->map->width,
					x_start, (WIN_WIDTH - x_start));
			matrix[y][x].proj_y = map_val((float)(y + 0.5), p->map->depth,
					y_start, (WIN_HEIGHT - y_start));
			y++;
		}
		x++;
	}
}

void	draw_iso(t_p *p)
{
	t_point	**matrix;
	int		x;
	int		y;
	double	x_step;
	double	y_step;
	double	x_start;
	double	y_start;
//TOTO: Scale factor for z_offset
	x_start = (float)WIN_WIDTH / 2;
	y_start = (float)WIN_HEIGHT / PADDING;
	x_step = (WIN_WIDTH - 2 * (double)WIN_WIDTH / PADDING) / p->map->width;
	y_step = (WIN_HEIGHT - 2 * (double)WIN_HEIGHT / PADDING) / p->map->depth;
	x = 0;
	matrix = p->map->matrix;
	while (x < p->map->width)
	{
		y = 0;
		while (y < p->map->depth)
		{
			matrix[y][x].proj_x = x_start + (x - y) * (x_step / 2);
			matrix[y][x].proj_y = y_start + (x + y) * (y_step / 2) - (matrix[y][x].z * y_step);
			y++;
		}
		x++;
	}
}

void	create_projection(int id, t_p *p)
{
	if (id == 1)
		draw_top_down(p);
	else if (id == 2)
		draw_iso(p);
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
	create_projection(2, p);
	map_to_img(p);
}
