/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_graphics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:40:49 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/05 11:56:10 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
			my_pixel_put(&p.img, x, y, color);
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
				my_pixel_put(&p.img, x, y, 0xFF00FF00);
		x++;
		if (x > p.width)
		{
			y++;
			x = 0;
		}
	}
	mlx_put_image_to_window(p.mlx, p.win, p.img.img, 0, 0);
}
