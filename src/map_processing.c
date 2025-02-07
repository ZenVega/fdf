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

int	load_map(t_list **map, char **argv)
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
			return (ft_lstclear(map, free), 0);
		ft_lstadd_back(map, tmp);
	}
	return (1);
}
