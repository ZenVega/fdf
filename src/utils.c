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

unsigned int	shift_to_white(unsigned int color, int shift_val)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	a;
	float			factor;

	if (shift_val < 0)
		shift_val = 0;
	if (shift_val > 16)
		shift_val = 16;
	factor = shift_val / 16.0f;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	a = (color >> 24) & 0xFF;
	r = r + (255 - r) * factor;
	g = g + (255 - g) * factor;
	b = b + (255 - b) * factor;
	return ((a << 24) | (r << 16) | (g << 8) | b);
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

int	create_argb(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

void	clean_up(t_map *map, t_list *data)
{
	int	i;

	ft_lstclear(&data, free);
	if (data)
		(free(data), data = NULL);
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
