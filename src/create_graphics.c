/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_graphics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:20:32 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/20 12:52:43 by uschmidt         ###   ########.fr       */
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

void	clip_line(t_p *p, t_vector *v, t_point *a)
{
	if (a->proj_x < 0)
	{
		a->proj_y = ft_abs(a->proj_x) * v->slope;
		a->proj_x = 0;
	}
	else if (a->proj_x > p->width)
	{
		a->proj_y = (a->proj_x - p->width) * v->slope;
		a->proj_x = p->width;
	}
	else if (a->proj_y < 0)
	{
		a->proj_x = ft_abs(a->proj_y) * v->slope;
		a->proj_y = 0;
	}
	else if (a->proj_y > p->height)
	{
		a->proj_x = (a->proj_y - p->height) * v->slope;
		a->proj_y = p->height;
	}
}

int	validate_line(t_p *p, t_vector *v, t_point *a, t_point *b)
{
	if ((a->proj_x < 0 && b->proj_x < 0)
		|| (a->proj_x > p->width && b->proj_x > p->width)
		|| (a->proj_y < 0 && b->proj_y < 0)
		|| (a->proj_y > p->height && b->proj_y > p->height))
	{
		v->pixels = 1;
		return (-1);
	}
	if ((a->proj_x > 0 && b->proj_x > 0)
		&& (a->proj_x < p->width && b->proj_x < p->width)
		&& (a->proj_y > 0 && b->proj_y > 0)
		&& (a->proj_y < p->height && b->proj_y < p->height))
		return (1);
	if (a->proj_x < 0 || a->proj_y < 0 || a->proj_x > p->width
		|| a->proj_y < p->height)
		clip_line(p, v, a);
	if (b->proj_x < 0 || b->proj_y < 0 || b->proj_x > p->width
		|| b->proj_y < p->height)
		clip_line(p, v, b);
	return (1);
}

t_vector	get_vector(t_p *p, t_point *a, t_point *b)
{
	t_vector		v;

	v.delta_x = b->proj_x - a->proj_x;
	v.delta_y = b->proj_y - a->proj_y;
	v.slope = sqrt(pow(v.delta_x, 2) + pow(v.delta_y, 2));
	if (b->proj_y < a->proj_y || b->proj_x < a->proj_x)
		v.slope *= -1;
	if (validate_line(p, &v, a, b) != -1)
	{
		if (ft_abs(v.delta_x) > ft_abs(v.delta_y))
			v.pixels = v.delta_x;
		else
			v.pixels = v.delta_y;
		v.delta_x /= ft_abs(v.pixels);
		v.delta_y /= ft_abs(v.pixels);
		v.pixel_x = a->proj_x;
		v.pixel_y = a->proj_y;
	}
	else
		v.pixels = 0;
	return (v);
}

void	draw_line(t_p *p, t_point a, t_point b)
{
	t_vector		v;
	unsigned int	color;
	int				i;

	v = get_vector(p, &a, &b);
	i = 0;
	while (i < ft_abs(v.pixels))
	{
		if (p->syscol == 1)
			color = get_grad_col(i, ft_abs(v.pixels), a.color, b.color);
		else
			color = get_grad_col(i, ft_abs(v.pixels), a.color_height, b.color_height);
		pixel_put(p, round(v.pixel_x), round(v.pixel_y), color);
		v.pixel_x += v.delta_x;
		v.pixel_y += v.delta_y;
		i++;
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
