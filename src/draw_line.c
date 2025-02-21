/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:53:51 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/21 10:54:20 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	clip_line(t_p *p, t_vector *v, t_point *outlier, t_point *b)
{
	if (outlier->proj_x < 0)
	{
		outlier->proj_y = b->proj_y + (0 - b->proj_x) * v->slope;
		outlier->proj_x = 0;
	}
	else if (outlier->proj_x > p->width)
	{
		outlier->proj_y = b->proj_y + (p->width - b->proj_x) * v->slope;
		outlier->proj_x = p->width;
	}
	else if (outlier->proj_y < 0)
	{
		outlier->proj_x = b->proj_x + (0 - b->proj_y) / v->slope;
		outlier->proj_y = 0;
	}
	else if (outlier->proj_y > p->height)
	{
		outlier->proj_x = b->proj_x + (p->height - b->proj_y) / v->slope;
		outlier->proj_y = p->height;
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
		|| a->proj_y > p->height)
		clip_line(p, v, a, b);
	if (b->proj_x < 0 || b->proj_y < 0 || b->proj_x > p->width
		|| b->proj_y > p->height)
		clip_line(p, v, b, a);
	return (1);
}

t_vector	get_vector(t_p *p, t_point *a, t_point *b)
{
	t_vector		v;

	v.delta_x = b->proj_x - a->proj_x;
	v.delta_y = b->proj_y - a->proj_y;
	if (v.delta_x != 0)
		v.slope = v.delta_y / (double)v.delta_x;
	else
		v.slope = 1;
	if (validate_line(p, &v, a, b) != -1)
	{
		if (ft_abs(v.delta_x) > ft_abs(v.delta_y))
			v.pixels = v.delta_x;
		else
			v.pixels = v.delta_y;
		if (v.pixels == 0)
			v.pixels = 1;
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
