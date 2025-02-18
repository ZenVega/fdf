/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:53:39 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/17 15:52:42 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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
	if (keycode == KEY_O)
		p->zoom -= .2;
	if (keycode == KEY_I)
		p->zoom += .2;
}

int	on_keydown(int keycode, t_p *p)
{
	ft_printf("KeY; %d\n", keycode);
	if (keycode == KEY_ESC)
		on_close_window(p);
	if (keycode == KEY_N)
		p->noise = -p->noise;
	if (keycode == KEY_P)
	{
		if (++p->projection > PROJ_MAX)
			p->projection = 0;
	}
	if (keycode == KEY_I || keycode == KEY_O)
		zoom(p, keycode);
	if (keycode == KEY_SB_OPEN || keycode == KEY_SB_CLOSE
		|| keycode == KEY_SEMIC || keycode == KEY_COMMA
		|| keycode == KEY_DOT || keycode == KEY_SLASH)
		rotate(p, keycode);
	if (keycode == KEY_R)
	{
		p->rotating = -p->rotating;
		ft_printf("ROT; %d\n", p->rotating);
	}
	return (0);
}
