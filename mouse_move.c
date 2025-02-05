/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:53:39 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/05 12:05:30 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <mlx.h>
#include "fractol.h"

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

//TODO Why segfault???
int	on_close_window(t_p *p)
{
	mlx_destroy_image(p->mlx, p->img.img);
	mlx_destroy_window(p->mlx, p->win);
	return (0);
}
