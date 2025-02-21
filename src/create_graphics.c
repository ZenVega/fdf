/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_graphics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:20:32 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/21 12:31:09 by uschmidt         ###   ########.fr       */
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
	int	x;
	int	y;
	int	color;

	x = -1;
	y = -1;
	if (p->noise.on == -1 && p->noise.intensity <= 0)
		return ;
	if (p->noise.on == -1)
		p->noise.intensity -= 0.02;
	if (p->noise.on == 1)
	{
		p->noise.intensity += 0.03;
		if (p->noise.intensity >= 1)
			p->noise.intensity = 1;
	}
	while (y <= p->height)
	{
		x++;
		if (random() * p->noise.intensity > RAND_MAX / 1.15)
		{
			color = get_grad_col(y, p->height, C_NEON_BLUE, C_NEON_RED);
			pixel_put(p, x, y, color);
		}
		if (x >= p->width)
		{
			x = 0;
			y++;
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
