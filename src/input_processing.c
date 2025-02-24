/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:18:20 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/21 13:00:08 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	remove_nl(char *line)
{
	int	i;

	if (!line)
		return (-1);
	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			line[i] = 0;
			return (i);
		}
		i++;
	}
	return (i);
}

static int	get_fd(char *map)
{
	int		fd;
	char	*path;

	path = ft_strjoin("./maps/", map);
	fd = open(path, O_RDONLY);
	free(path);
	return (fd);
}

int	load_data(t_list **data, char **argv)
{
	t_list	*tmp;
	char	*line;
	int		height;
	int		fd;

	fd = get_fd(argv[1]);
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
	close(fd);
	return (height);
}
