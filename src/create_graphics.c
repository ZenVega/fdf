/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_graphics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:20:32 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/11 17:37:54 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	pixel_put(t_img *img, int x, int y, int color)
{
	int		offset;
	char	*dst;

	offset = y * img->line_length + x * (img->bits_per_pixel / 8);
	dst = img->addr + offset;
	*(unsigned int *)dst = color;
}

void	draw_line(t_img *img, t_point a, t_point b)
{
	double	delta_x;
	double	delta_y;
	int		pixels;
	double	pixel_x;
	double	pixel_y;

	delta_x = b.proj_x - a.proj_x;
	delta_y = b.proj_y - a.proj_y;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= pixels;
	delta_y /= pixels;
	pixel_x = a.proj_x;
	pixel_y = a.proj_y;
	while (pixels)
	{
		pixel_put(img, pixel_x, pixel_y, 0xFFFFFFFF);
		pixel_x += delta_x;
		pixel_y += delta_y;
		--pixels;
	}
}

void	gen_noise(t_p *p)
{
	int	i;
	int	x;
	int	y;
	int	color;

	i = 0;
	x = 0;
	y = 0;
	while (i++ < p->width * p->height)
	{
		color = get_color_for_x(x, p->width);
		if (random() > RAND_MAX / 1.15)
			pixel_put(&p->img, x, y, color);
		x++;
		if (x > p->width)
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
}
//void	draw_mouse_vector(t_p *p)
//{
//	t_vector	vector;
//
//	vector.ax = p->width / 2;
//	vector.ay = p->height / 2;
//	vector.bx = p->mouse_x;
//	vector.by = p->mouse_y;
//	//draw_line(&p->img, &vector);
//}
