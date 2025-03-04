/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:19:01 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/21 13:13:29 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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
				matrix[y][x].color_height = get_grad_col(matrix[y][x].z,
						map->highest_z, C_ZERO, C_HIGH);
			else
				matrix[y][x].color_height = get_grad_col(matrix[y][x].z,
						map->lowest_z, C_ZERO, C_LOW);
			y++;
		}
		x++;
	}
}

void	extract_from_str(char *str, unsigned long *col, unsigned int *alt)
{
	int		i;
	char	**splitted;

	splitted = NULL;
	i = -1;
	while (str[++i])
		if (str[i] == ',')
			break ;
	if (str[i] != ',')
		*alt = ft_atoi(str);
	else
	{
		splitted = ft_split(str, ',');
		if (splitted)
		{
			*alt = ft_atoi(splitted[0]);
			if (splitted[1])
				*col = ft_atoi_base(splitted[1], HEX) | (0xFF << 24);
		}
	}
	if (splitted)
		(free(splitted[0]), free(splitted[1]), free(splitted));
}

static void	create_point(t_map *map, int i, int j, char **vals)
{
	t_point			*dest;
	unsigned int	alt;
	unsigned long	col;

	col = C_ZERO;
	extract_from_str(vals[j], &col, &alt);
	dest = &map->matrix[i][j];
	dest->x = j - map->width / 2;
	dest->y = i - map->depth / 2;
	dest->z = alt;
	dest->color = col;
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
