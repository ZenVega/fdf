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

int	load_data(t_list **data, char **argv)
{
	int		fd;
	t_list	*tmp;
	char	*path;
	char	*line;

	path = ft_strjoin("./maps/", argv[1]);
	fd = open(path, O_RDONLY);
	free(path);
	if (fd == -1)
		return (0);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		tmp = ft_lstnew(line);
		if (tmp == NULL)
			return (ft_lstclear(data, free), 0);
		ft_lstadd_back(data, tmp);
	}
	return (1);
}

int	count_vals(char *line)
{
	int	i;

	i = 0;
	while (*line || *line != '\n')
	{
		if (*line == ' ')
			i++;
		line++;
	}
	return (i + 1);
}

void	clean_up(t_map *map, int *line, t_list *data)
{
	ft_lstclear(&data, free);
	if (map)
		(free(map), map = NULL);
	if (line)
		(free(line), line = NULL);
}

t_map	*create_map_matrix(t_list *data)
{
	t_map	*map;
	int		*line;
	int		i;
	char	**vals;

	map = (t_map *)malloc(sizeof(t_map));
	line = (int *)malloc(sizeof(int) * count_vals(data->content));
	if (!map || !line)
		return (clean_up(map, line, data), NULL);
	while (data)
	{
		i = 0;
		vals = ft_split(data->content, ' ');
		while (vals[i])
		{
			line[i] = ft_atoi(vals[i]);
			free(vals[i++]);
			free(data->content);
			data->content = line;
		}
		data = data->next;
	}
	map->matrix = data;
	return (map);
}

void	create_projection(void)
{
}
