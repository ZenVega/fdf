/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_graphics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:20:32 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/07 15:13:00 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	pixel_put(t_data *data, int x, int y, int color)
{
	int		offset;
	char	*dst;

	offset = y * data->line_length + x * (data->bits_per_pixel / 8);
	dst = data->addr + offset;
	*(unsigned int *)dst = color;
}

void	draw_line(t_data *data, t_vector *vector)
{
	double	delta_x;
	double	delta_y;
	int		pixels;
	double	pixel_x;
	double	pixel_y;

	delta_x = vector->bx - vector->ax;
	delta_y = vector->by - vector->ay;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= pixels;
	delta_y /= pixels;
	pixel_x = vector->ax;
	pixel_y = vector->ay;
	while (pixels)
	{
		pixel_put(data, pixel_x, pixel_y, 0xFFFFFFFF);
		pixel_x += delta_x;
		pixel_y += delta_y;
		--pixels;
	}
}

void	let_it_snow(t_p p)
{
	int	i;
	int	x;
	int	y;
	int	color;

	i = 0;
	x = 0;
	y = 0;
	while (i++ < p.width * p.height)
	{
		color = get_color_for_x(x, p.width);
		if (random() > RAND_MAX / 1.15)
			pixel_put(&p.img, x, y, color);
		x++;
		if (x > p.width)
		{
			y++;
			x = 0;
		}
	}
}

void	draw_noisy_square(t_p p)
{
	int	x;
	int	y;

	x = p.width / 3;
	y = p.height / 3;
	while (y < p.height - (p.height / 3))
	{
		if (x > p.width / 3 && x < p.width - (p.width / 3))
			if (random() > RAND_MAX / 1.15)
				pixel_put(&p.img, x, y, 0xFF00FF00);
		x++;
		if (x > p.width)
		{
			y++;
			x = 0;
		}
	}
	mlx_put_image_to_window(p.mlx, p.win, p.img.img, 0, 0);
}
