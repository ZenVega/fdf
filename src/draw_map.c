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

//void	rotate(t_p *p, int dir)
//{
//}

void	draw_top_down(t_p *p)
{
	t_point	**matrix;
	int		x;
	int		y;
	t_proj	proj;

	proj.x_step = (WIN_WIDTH * (1 - 2 * PADDING)) / p->map->width / p->zoom;
	proj.y_step = (WIN_HEIGHT * (1 - 2 * PADDING)) / p->map->depth / p->zoom;
	proj.width = p->map->width * proj.x_step / p->zoom;
	proj.height = p->map->depth * proj.y_step / p->zoom;
	proj.x_start = (WIN_WIDTH - proj.width) / 2;
	proj.y_start = (WIN_HEIGHT - proj.height) / 2;
	x = 0;
	matrix = p->map->matrix;
	while (x < p->map->width)
	{
		y = 0;
		while (y < p->map->depth)
		{
			matrix[y][x].proj_x = map_val((float)(x + 0.5), p->map->width,
					proj.x_start, (WIN_WIDTH - proj.x_start));
			matrix[y][x].proj_y = map_val((float)(y + 0.5), p->map->depth,
					proj.y_start, (WIN_HEIGHT - proj.y_start));
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
	t_proj	proj;

	proj.x_step = (WIN_WIDTH * (1 - 2 * PADDING)) / p->map->width / p->zoom;
	proj.y_step = (WIN_HEIGHT * (1 - 2 * PADDING)) / p->map->depth / p->zoom;
	proj.width = (p->map->width + p->map->depth) * (proj.x_step / 2);
	proj.height = (p->map->width + p->map->depth) * (proj.y_step / 2);
	proj.ratio = ((float)p->map->width + p->map->depth) / p->map->depth ;
	proj.x_start = (WIN_WIDTH - proj.width) / 2 + (proj.width / proj.ratio);
	proj.y_start = (WIN_HEIGHT - proj.height) / 2;
	x = 0;
	matrix = p->map->matrix;
	while (x < p->map->width)
	{
		y = 0;
		while (y < p->map->depth)
		{
			matrix[y][x].proj_x = proj.x_start + (x - y) * (proj.x_step / 2);
			matrix[y][x].proj_y = proj.y_start + (x + y) * (proj.y_step / 2)
				- (matrix[y][x].z * proj.y_step) / 6;
			y++;
		}
		x++;
	}
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
			pixel_put(&p->img, matrix[y][x].proj_x,
				matrix[y][x].proj_y, matrix[y][x].color);
			y++;
		}
		x++;
	}
}

void	draw_map(t_p *p)
{
	if (p->projection == 1)
		draw_top_down(p);
	else if (p->projection == 2)
		draw_iso(p);
	map_to_img(p);
}
