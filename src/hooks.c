/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:53:39 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/20 18:21:21 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	on_mouse_click(int button, int x, int y, t_p *p)
{
	double	zoom_factor;

	if (button == 1)
		zoom_factor = p->zoom - p->zoom * .2;
	else if (button == 3)
		zoom_factor = p->zoom + p->zoom * .2;
	p->center_x = x + (p->center_x - x) * zoom_factor;
	p->center_y = y + (p->center_y - y) * zoom_factor;
	p->zoom = zoom_factor;
	return (0);
}

static void	key_extra(int keycode, t_p *p)
{
	if (keycode == KEY_ESC)
		on_close_window(p);
	if (keycode == KEY_SHIFT)
		p->shifted = 1;
	if (keycode == KEY_BACKSPACE)
		permanent_rotation(p, KEY_BACKSPACE);
	if (keycode == KEY_MINUS)
		p->rot_speed++;
	if (keycode == KEY_EQUAL)
		p->rot_speed--;
	if (keycode == KEY_ARR_UP || keycode == KEY_ARR_DOWN
		|| keycode == KEY_ARR_LEFT || keycode == KEY_ARR_RIGHT)
		translate(p, keycode);
}

static void	key_ascii(int keycode, t_p *p)
{
	if (keycode == KEY_N)
		p->noise = -p->noise;
	if (keycode == KEY_P)
		change_projection(p);
	if (keycode == KEY_X)
		reset_params(p);
	if (keycode == KEY_Q)
	{
		if (p->shifted)
			p->scale_factor = p->scale_factor * 1.1;
		else
			p->scale_factor = p->scale_factor * 0.9;
	}
	if (keycode == KEY_I || keycode == KEY_O)
		zoom(p, keycode);
	if (keycode == KEY_C)
		p->syscol = -p->syscol;
	if (keycode == KEY_SB_OPEN || keycode == KEY_SB_CLOSE
		|| keycode == KEY_SEMIC || keycode == KEY_COMMA
		|| keycode == KEY_DOT || keycode == KEY_SLASH)
		rotate(p, keycode);
	if (keycode == KEY_W || keycode == KEY_A
		|| keycode == KEY_S || keycode == KEY_D)
		translate(p, keycode);
}

int	on_key_down(int keycode, t_p *p)
{
	ft_printf("%d\n", keycode);
	if (keycode > 177)
		key_extra(keycode, p);
	else
		key_ascii(keycode, p);
	return (0);
}

int	on_key_release(int keycode, t_p *p)
{
	if (keycode == KEY_SHIFT)
		p->shifted = 0;
	return (0);
}
