/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:15:01 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/07 17:23:51 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "includes/fdf.h"

void	reset_img(t_data img, int width, int height)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (i++ < width * height)
	{
		pixel_put(&img, x, y, 0x0);
		x++;
		if (x > width)
		{
			y++;
			x = 0;
		}
	}
}

int	render_frames(t_p *p)
{
	t_data		img;
	int			col;
	t_vector	vector;

	vector.ax = p->width / 2;
	vector.ay = p->height / 2;
	vector.bx = p->mouse_x;
	vector.by = p->mouse_y;
	col = 0xFF8F8F8F;
	img = p->img;
	if (img.img == NULL)
		return (0);
	reset_img(img, p->width, p->height);
	let_it_snow(*p);
	mlx_put_image_to_window(p->mlx, p->win, img.img, 0, 0);
	draw_line(&p->img, &vector);
	mlx_string_put(p->mlx, p->win, p->mouse_x, p->mouse_y, col, "<-ok_shit");
	return (0);
}

t_p	init_img(void)
{
	static t_p	p;

	p.mlx = mlx_init();
	p.width = 960;
	p.height = 540;
	p.win = mlx_new_window(p.mlx, p.width, p.height, "Wrecktal!");
	p.cursor.file = "./graphics/bolt.xpm";
	p.cursor.width = 200;
	p.cursor.height = 200;
	p.cursor.img = mlx_xpm_file_to_image(p.mlx, p.cursor.file,
			&p.cursor.width, &p.cursor.height);
	p.cursor.addr = mlx_get_data_addr(p.cursor.img, &p.cursor.bits_per_pixel,
			&p.cursor.line_length, &p.cursor.endian);
	p.img.img = mlx_new_image(p.mlx, p.width, p.height);
	p.img.addr = mlx_get_data_addr(p.img.img, &p.img.bits_per_pixel,
			&p.img.line_length, &p.img.endian);
	return (p);
}

void	close_program(t_p *p, t_map *map)
{
	if (p->img.img)
		mlx_destroy_image(p->mlx, p->img.img);
	mlx_destroy_image(p->mlx, p->cursor.img);
	p->img.img = NULL;
	if (p->win)
		mlx_destroy_window(p->mlx, p->win);
	mlx_destroy_display(p->mlx);
	free(p->mlx);
	p->mlx = NULL;
	clean_up(map, NULL);
}

int	main(int argc, char **argv)
{
	t_p			p;
	t_list		*data;
	t_map		*map;
	int			i;
	int			j;

	data = NULL;
	if (argc != 2)
		return (ft_printf("No Map"), 0);
	j = load_data(&data, argv);
	if (!j)
		return (ft_printf("No Map"), 0);
	map = init_map(data, j);
	j = 0;
	while (j < map->height)
	{
		i = 0;
		while (i < map->length)
		{
			ft_printf("%d | ", map->matrix[j][i++].z);
		}
		ft_printf("\n");
		j++;
	}
	p = init_img();
	init_hooks(&p);
	mlx_loop_hook(p.mlx, render_frames, &p);
	mlx_loop(p.mlx);
	close_program(&p, map);
}
