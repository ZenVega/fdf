/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:19:01 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/17 12:27:23 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <limits.h>

void	color_matrix(t_map *map)
{
	int		x;
	int		y;
	t_point	**matrix;

	x = 0;
	matrix = map->matrix;
	while (x < map->width)
	{
		y = 0;
		while (y < map->depth)
		{
			if (matrix[y][x].z >= 0)
				matrix[y][x].color = get_grad_col(matrix[y][x].z,
						map->highest_z, C_ZERO, C_HIGH);
			else
				matrix[y][x].color = get_grad_col(matrix[y][x].z,
						map->lowest_z, C_ZERO, C_LOW);
			y++;
		}
		x++;
	}
}

static void	create_point(t_map *map, int i, int j, char **vals)
{
	t_point	*dest;

	dest = &map->matrix[i][j];
	dest->x = j - map->width / 2;
	dest->y = i - map->depth / 2;
	dest->z = ft_atoi(vals[j]);
	if (dest->z > map->highest_z)
		map->highest_z = dest->z;
	if (dest->z < map->lowest_z)
		map->lowest_z = dest->z;
	free(vals[j]);
}

t_map	*create_map_matrix(t_list *data, t_map *map)
{
	int		j;
	int		i;
	char	**vals;

	i = 0;
	while (data)
	{
		map->matrix[i] = (t_point *)malloc(sizeof(t_point) * map->width);
		if (!map->matrix[i])
			return (clean_up(map, data), NULL);
		j = -1;
		vals = ft_split(data->content, ' ');
		while (vals[++j])
			create_point(map, i, j, vals);
		free(vals);
		i++;
		data = data->next;
	}
	return (map);
}

int	get_map_width(char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		while (*line == ' ')
			line++;
		if (*line && *line != ' ')
		{
			count++;
			while (*line && *line != ' ')
				line++;
		}
	}
	return (count);
}
