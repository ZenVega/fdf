/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:15:01 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/05 12:32:01 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	int		offset;
	char	*dst;

	offset = y * data->line_length + x * (data->bits_per_pixel / 8);
	dst = data->addr + offset;
	*(unsigned int *)dst = color;
}

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
		my_pixel_put(&img, x, y, 0x0);
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
	t_data	img;
	int		col;

	col = 0xFF8F8F8F;
	img = p->img;
	if (img.img == NULL)
		return (0);
	reset_img(img, p->width, p->height);
	let_it_snow(*p);
	mlx_put_image_to_window(p->mlx, p->win, img.img, 0, 0);
	mlx_string_put(p->mlx, p->win, p->mouse_x, p->mouse_y, col, "<-ok_shit");
	return (0);
}

t_p	init_img(void)
{
	static t_p	p;

	p.width = 960;
	p.height = 540;
	p.mlx = mlx_init();
	p.win = mlx_new_window(p.mlx, p.width, p.height, "Wrecktal!");
	p.img.img = mlx_new_image(p.mlx, p.width, p.height);
	p.img.addr = mlx_get_data_addr(p.img.img, &p.img.bits_per_pixel,
			&p.img.line_length, &p.img.endian);
	return (p);
}

int	main(void)
{
	t_p	p;

	p = init_img();
	mlx_key_hook(p.win, on_keydown, &p);
	mlx_hook(p.win, 25, 0L, on_resize, &p);
	mlx_hook(p.win, 6, 1L << 6, on_mouse_move, &p);
	mlx_hook(p.win, 7, (1L << 4), on_mouse_enter, &p);
	mlx_hook(p.win, 8, (1L << 5), on_mouse_leave, &p);
	mlx_hook(p.win, 17, (1L << 17), on_close_window, &p);
	mlx_loop_hook(p.mlx, render_frames, &p);
	mlx_loop(p.mlx);
}
