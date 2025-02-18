/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:06:37 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/17 15:14:45 by uschmidt         ###   ########.fr       */
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

void	draw_proj(t_proj *proj, t_p *p)
{
	int		i;
	int		j;

	i = 0;
	while (i < p->map->width)
	{
		j = 0;
		while (j < p->map->depth)
		{
			rotate_point(&p->map->matrix[j][i], p);
			project_point(&p->map->matrix[j][i], *proj);
			j++;
		}
		i++;
	}
}
void	map_to_img(t_p *p)
{
	int		j;
	int		i;
	t_point	**matrix;

	matrix = p->map->matrix;
	j = 0;
	while (j < p->map->width)
	{
		i = 0;
		while (i < p->map->depth)
		{
			if (!(j == p->map->width - 1))
				draw_line(p, matrix[i][j], matrix[i][j + 1]);
			if (!(i == p->map->depth - 1))
				draw_line(p, matrix[i][j], matrix[i + 1][j]);
			pixel_put(&p->img, matrix[i][j].proj_x,
				matrix[i][j].proj_y, matrix[i][j].color);
			i++;
		}
		j++;
	}
}

void	draw_map(t_p *p)
{
	t_proj	proj;

	proj.x_step = (WIN_WIDTH * (1 - 2 * PADDING)) / p->map->width / p->zoom;
	proj.y_step = (WIN_HEIGHT * (1 - 2 * PADDING)) / p->map->depth / p->zoom;
	proj.width = (p->map->width + p->map->depth) * (proj.x_step / 2);
	proj.height = (p->map->width + p->map->depth) * (proj.y_step / 2);
	proj.ratio = ((float)p->map->width + p->map->depth) / p->map->depth ;
	proj.x_start = p->center_x - proj.width / 2 + (proj.width / proj.ratio);
	proj.y_start = p->center_y - proj.height / 2 + proj.height / 2;
	draw_proj(&proj, p);
	map_to_img(p);
}
