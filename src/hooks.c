/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:53:39 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/07 15:28:52 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	init_hooks(t_p *p)
{
	mlx_key_hook(p->win, on_keydown, p);
	mlx_hook(p->win, 6, 1L << 6, on_mouse_move, p);
	mlx_hook(p->win, 17, (1L << 17), on_close_window, p);
}

int	on_mouse_move(int x, int y, t_p *p)
{
	p->mouse_x = x;
	p->mouse_y = y;
	return (0);
}

int	on_close_window(t_p *p)
{
	if (p->mlx)
		mlx_loop_end(p->mlx);
	return (0);
}

void	zoom(t_p *p, int keycode)
{
	if (keycode == 105)
		p->zoom -= .2;
	if (keycode == 111)
		p->zoom += .2;
}

int	on_keydown(int keycode, t_p *p)
{
	ft_printf("KeY; %d\n", keycode);
	if (keycode == 65307)
		on_close_window(p);
	if (keycode == 110)
		p->noise = -p->noise;
	if (keycode == 112)
	{
		if (++p->projection > PROJ_MAX)
			p->projection = 0;
	}
	if (keycode == 105 || keycode == 111)
		zoom(p, keycode);
	return (0);
}

