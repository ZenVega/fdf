/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:53:39 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/04 16:29:29 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <mlx.h>
#include "fractol.h"

int	on_mouse_move(int x, int y, t_param *param)
{
	ft_printf("MouseMove; %d / %d\n", x, y);
	mlx_string_put(param->mlx, param->win, x, y, 0xFF8F8F8F, "ok shit");
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
int	on_close_window(t_param *param)
{
	ft_printf("Button Close; %d\n");
	mlx_destroy_window(param->mlx, param->win);
	return (0);
}
