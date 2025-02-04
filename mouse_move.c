/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:53:39 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/04 16:04:23 by uschmidt         ###   ########.fr       */
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

int	on_button_release(int keycode, t_param *param)
{
	ft_printf("Button; %d\n", keycode);
	mlx_string_put(param->mlx, param->win, 200, 200, 0xFF8F8F8F, "press shit");
	return (0);
}
