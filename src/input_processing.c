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
	close(fd);
	return (height);
}
