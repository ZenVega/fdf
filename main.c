/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:15:01 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/03 15:45:25 by uschmidt         ###   ########.fr       */
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

void	let_it_snow(void *mlx, t_data img, void *mlx_win, int width, int height)
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
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
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
	while (y < (height - (height / 3)))
	{
		if (random() > RAND_MAX / 1.15)
			my_pixel_put(&img, x, y, 0xFFFF0000);
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

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img_1;
	t_data	img_2;
	int		width;
	int		height;

	width = 960;
	height = 540;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, width, height, "Hello World!");
	img_1.img = mlx_new_image(mlx, width, height);
	img_2.img = mlx_new_image(mlx, width, height);
	img_1.addr = mlx_get_data_addr(img_1.img, &img_1.bits_per_pixel,
			&img_1.line_length, &img_1.endian);
	img_2.addr = mlx_get_data_addr(img_2.img, &img_2.bits_per_pixel,
			&img_2.line_length, &img_2.endian);
	while (1)
	{
		let_it_snow(mlx, img_1, mlx_win, width, height);
		reset_img(img_2, width, height);
		let_it_snow(mlx, img_2, mlx_win, width, height);
		reset_img(img_1, width, height);
	}
	red_square(mlx, img_1, mlx_win, width, height);
	mlx_loop(mlx);
}
