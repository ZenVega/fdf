/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:39:00 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/07 14:55:21 by uschmidt         ###   ########.fr       */
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

unsigned int	get_color_for_x(int x, int width)
{
	unsigned int	r;
	unsigned int	b;
	float			factor;

	factor = (float)x / (float)width;
	r = 255 - (factor * 255);
	b = factor * 255;
	return (0xFF000000 | (r << 16) | b);
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
