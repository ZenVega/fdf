/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:19:01 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/07 17:24:08 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	remove_nl(char *line)
{
	int	i;

	if (!line)
		return ;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			line[i] = 0;
		i++;
	}
}

int	load_data(t_list **data, char **argv)
{
	int		fd;
	t_list	*tmp;
	char	*path;
	char	*line;
	int		height;

	path = ft_strjoin("./maps/", argv[1]);
	fd = open(path, O_RDONLY);
	free(path);
	if (fd == -1)
		return (0);
	height = 0;
	while (1)
	{
		line = get_next_line(fd);
		remove_nl(line);
		if (line == NULL)
			break ;
		tmp = ft_lstnew(line);
		if (tmp == NULL)
			return (ft_lstclear(data, free), 0);
		ft_lstadd_back(data, tmp);
		height++;
	}
	return (height);
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

t_map	*create_map_matrix(t_list *data, t_map *map)
{
	int		i;
	int		j;
	char	**vals;

	j = 0;
	while (data)
	{
		map->matrix[j] = (t_point *)malloc(sizeof(t_point) * map->length);
		if (!map->matrix[j])
			return (clean_up(map, data), NULL);
		i = 0;
		vals = ft_split(data->content, ' ');
		while (vals[i])
		{
			map->matrix[j][i].x = i;
			map->matrix[j][i].y = j;
			map->matrix[j][i].z = ft_atoi(vals[i]);
			free(vals[i++]);
		}
		free(vals);
		j++;
		data = data->next;
	}
	return (map);
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
	map->length = get_map_width(data->content);
	map->height = height;
	map = create_map_matrix(data, map);
	clean_up(NULL, tmp);
	return (map);
}
