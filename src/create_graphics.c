/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_graphics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:20:32 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/21 10:54:24 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	pixel_put(t_p *p, int x, int y, unsigned int color)
{
	int		offset;
	char	*dst;
	t_img	*img;

	img = &p->img;
	if (x > 0 && x < WIN_WIDTH && y > 0 && y < WIN_HEIGHT)
	{
		offset = y * img->line_length + x * (img->bits_per_pixel / 8);
		dst = img->addr + offset;
		*(unsigned int *)dst = color;
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
		color = get_grad_col(x, p->width, 0xFFFF0000, 0xFF0000FF);
		if (random() > RAND_MAX / 1.15)
			pixel_put(p, x, y, color);
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
				pixel_put(&p, x, y, 0xFF00FF00);
		x++;
		if (x > p.width)
		{
			y++;
			x = 0;
		}
	}
}
