/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:15:01 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/07 15:29:53 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "includes/fractol.h"

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

//TODO: Extract an slice from a sprite using pixel_put / get pixel at!!!
//get a sprite, write a function that takes dimentions, start and endpoint and copies the image
//also make all pixels of one color transparent
// get info here: https://pulgamecanica.herokuapp.com/posts/mlx-animations
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

int	main(void)
{
	t_p			p;

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
