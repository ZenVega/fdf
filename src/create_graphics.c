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

void	gen_noise(t_p *p)
{
	int	x;
	int	y;

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
		if (++x >= p->width && ++y > -2)
			x = 0;
		if (random() * p->noise.intensity > RAND_MAX / 1.15)
		{
			pixel_put(p, x, y, get_grad_col(y, p->height, C_NN_BLUE, C_NN_RED));
		}
	}
}

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

int	render_frames(t_p *p)
{
	t_img		img;

	img = p->img;
	if (img.img == NULL)
		return (0);
	reset_img(p, p->width, p->height);
	gen_noise(p);
	if (p->x_rot != 0 || p->y_rot != 0 || p->z_rot != 0)
		rot_sequence(p);
	draw_map(p);
	mlx_put_image_to_window(p->mlx, p->win, img.img, 0, 0);
	print_menu(p, &p->menu);
	return (0);
}
