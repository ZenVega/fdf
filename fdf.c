/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:15:01 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/20 12:48:06 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "includes/fdf.h"

void	reset_img(t_p *p, int width, int height)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (i++ < width * height)
	{
		pixel_put(p, x, y, 0x0);
		x++;
		if (x > width)
		{
			y++;
			x = 0;
		}
	}
}

void	rot_sequence(t_p *p)
{
	if (--p->rot_timer > 0)
		return ;
	if (p->x_rot == -1)
		rotate(p, KEY_SB_OPEN);
	else if (p->x_rot == 1)
		rotate(p, KEY_SB_CLOSE);
	if (p->y_rot == -1)
		rotate(p, KEY_SEMIC);
	else if (p->y_rot == 1)
		rotate(p, KEY_COMMA);
	if (p->z_rot == -1)
		rotate(p, KEY_DOT);
	else if (p->z_rot == 1)
		rotate(p, KEY_SLASH);
	p->rot_timer = p->rot_speed;
}

int	render_frames(t_p *p)
{
	t_img		img;
	int			col;

	col = 0xFF8F8F8F;
	img = p->img;
	if (img.img == NULL)
		return (0);
	reset_img(p, p->width, p->height);
	if (p->noise == 1)
		gen_noise(p);
	if (p->x_rot != 0 || p->y_rot != 0 || p->z_rot != 0)
		rot_sequence(p);
	draw_map(p);
	mlx_put_image_to_window(p->mlx, p->win, img.img, 0, 0);
	mlx_string_put(p->mlx, p->win, p->mouse_x, p->mouse_y, col, "<-ok_shit");
	print_menu(p, &p->menu);
	return (0);
}

void	close_program(t_p *p, t_map *map)
{
	if (p->img.img)
		mlx_destroy_image(p->mlx, p->img.img);
	p->img.img = NULL;
	if (p->win)
		mlx_destroy_window(p->mlx, p->win);
	mlx_destroy_display(p->mlx);
	free(p->mlx);
	p->mlx = NULL;
	clean_up(map, NULL);
}

//TODOS:
// make transition
// perror,strerror
int	main(int argc, char **argv)
{
	t_p			p;
	t_list		*data;
	t_map		*map;
	int			map_height;

	data = NULL;
	if (argc != 2)
		return (ft_printf("No Map"), 0);
	map_height = load_data(&data, argv);
	if (!map_height)
		return (ft_printf("No Map"), 0);
	map = init_map(data, map_height);
	p = init_img();
	p.map = map;
	init_input_hooks(&p);
	init_menu(&p);
	mlx_loop_hook(p.mlx, render_frames, &p);
	mlx_loop(p.mlx);
	close_program(&p, map);
}
