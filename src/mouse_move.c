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

#include "../includes/fractol.h"

int	on_mouse_move(int x, int y, t_p *p)
{
	p->mouse_x = x;
	p->mouse_y = y;
	return (0);
}

int	on_mouse_enter(int keycode)
{
	ft_printf("MouseEnter; %d\n", keycode);
	return (0);
}

int	on_mouse_leave(int keycode)
{
	ft_printf("MouseLeave; %d\n", keycode);
	return (0);
}

int	on_close_window(t_p *p)
{
	if (p->mlx)
		mlx_loop_end(p->mlx);
	if (p->img.img)
		mlx_destroy_image(p->mlx, p->img.img);
	p->img.img = NULL;
	if (p->win)
		mlx_destroy_window(p->mlx, p->win);
	p->win = NULL;
	return (0);
}
