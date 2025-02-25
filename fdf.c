/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:15:01 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/21 13:18:33 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "includes/fdf.h"

int	main(int argc, char **argv)
{
	t_p			p;
	t_list		*data;
	t_map		*map;
	int			map_height;

	data = NULL;
	if (argc != 2)
		return (errno = ENOENT, perror("./fdf <No Map>"), 1);
	map_height = load_data(&data, argv);
	if (!map_height)
		return (errno = EIO, perror("./fdf <No Map>"), 1);
	map = init_map(data, map_height);
	if (map == NULL)
		return (errno = EIO, perror("./fdf <No Map>"), 1);
	p = init_img();
	p.map = map;
	init_input_hooks(&p);
	init_menu(&p);
	mlx_loop_hook(p.mlx, render_frames, &p);
	mlx_loop(p.mlx);
	close_program(&p, map);
	return (0);
}
