/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:15:01 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/04 16:25:58 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mlx.h>
#include <stdlib.h>
#include "fractol.h"
#include "libft/libft.h"

// recolors one pixel of an image. Offset finds the appropriate position in the image memory

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	int			offset;
	char		*dst;

	offset = y * data->line_length + x * (data->bits_per_pixel / 8);
	dst = data->addr + offset;
	*(unsigned int *)dst = color;
}

void	let_it_snow(t_data img, int width, int height)
{
	int	i;
	int	x;
	int	y;
	int	color;

	i = x = y = 0;
	while (i++ < width * height)
	{
		color = get_color_for_x(x, width);
		if (random() > RAND_MAX / 1.15)
			my_pixel_put(&img, x, y, color);
		x++;
		if (x > width)
		{
			y++;
			x = 0;
		}
	}
}

void	reset_img(t_data img, int width, int height)
{
	int	i;
	int	x;
	int	y;

	i = x = y = 0;
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

void	red_square(void *mlx, t_data img, void *mlx_win, int width, int height)
{
	int	x;
	int	y;

	x = width / 3;
	y = height / 3;
	while (y < height - (height / 3))
	{
		if (x > width / 3 && x < width - (width / 3))
			if (random() > RAND_MAX / 1.15)
				my_pixel_put(&img, x, y, 0xFF00FF00);
		x++;
		if (x > width)
		{
			y++;
			x = 0;
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
}
// mlx_new_image creates an image buffer. We want to ceate the image before updating the window in order to safe CPU
int render_frames(t_param *param)
{
	static int toggle = 0;
	static t_data img_1 = {0};
    static t_data img_2 = {0};

	int width = 960;
	int height = 540;
	if (!img_1.img || !img_2.img)
	{
		img_1.img = mlx_new_image(param->mlx, width, height);
		img_2.img = mlx_new_image(param->mlx, width, height);
		img_1.addr = mlx_get_data_addr(img_1.img, &img_1.bits_per_pixel,
				&img_1.line_length, &img_1.endian);
		img_2.addr = mlx_get_data_addr(img_2.img, &img_2.bits_per_pixel,
				&img_2.line_length, &img_2.endian);
	}
	if (toggle == 0)
	{
		reset_img(img_2, width, height);
		let_it_snow(img_1, width, height);
		mlx_put_image_to_window(param->mlx, param->win, img_1.img, 0, 0);
	}
	else
	{
		reset_img(img_1, width, height);
		let_it_snow(img_2, width, height);
		mlx_put_image_to_window(param->mlx, param->win, img_2.img, 0, 0);
	}
	toggle = !toggle;
	return (0);
}

int	main(void)
{
	int		width;
	int		height;
	t_param	param;

	width = 960;
	height = 540;
	param.mlx = mlx_init();
	param.win = mlx_new_window(param.mlx, width, height, "Hello World!");
	mlx_key_hook(param.win, on_keydown, &param);
	mlx_hook(param.win, 25, 0L, on_resize, &param);
	//mlx_hook(param.win, 6, 1L << 6, on_mouse_move, &param);
	mlx_hook(param.win, 7, (1L << 4), on_mouse_enter, &param);
	mlx_hook(param.win, 8, (1L << 5), on_mouse_leave, &param);
	mlx_hook(param.win, 17, (1L << 17), on_close_window, &param);
	mlx_loop_hook(param.mlx, render_frames, &param);
	mlx_loop(param.mlx);
}
