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

void	zoom(t_p *p, int keycode)
{
	if (keycode == KEY_O)
		p->zoom -= .2;
	if (keycode == KEY_I)
		p->zoom += .2;
}

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
	ft_printf("ZOOM: %f\n", zoom_factor);
	return (0);
}

int	on_close_window(t_p *p)
{
	if (p->mlx)
		mlx_loop_end(p->mlx);
	return (0);
}

void	change_projection(t_p *p)
{
	p->projection++;
	if (p->projection > PROJ_MAX)
		p->projection = 0;
	if (p->projection == 0)
		get_angles(&p->angles, INIT_X_ANG, INIT_Y_ANG, INIT_Z_ANG);
	else if (p->projection == 1)
		get_angles(&p->angles, 0, 0, 0);
	render_frames(p);
}

int	on_key_down(int keycode, t_p *p)
{
	ft_printf("KeY; %d\n", keycode);
	if (keycode == KEY_ESC)
		on_close_window(p);
	if (keycode == KEY_SHIFT)
		p->shifted = 1;
	if (keycode == KEY_N)
		p->noise = -p->noise;
	if (keycode == KEY_P)
		change_projection(p);
	if (keycode == KEY_I || keycode == KEY_O)
		zoom(p, keycode);
	if (keycode == KEY_SB_OPEN || keycode == KEY_SB_CLOSE
		|| keycode == KEY_SEMIC || keycode == KEY_COMMA
		|| keycode == KEY_DOT || keycode == KEY_SLASH)
		rotate(p, keycode);
	if (keycode == KEY_BACKSPACE)
		permanent_rotation(p, KEY_BACKSPACE);
	if (keycode == KEY_X)
		reset_params(p);
	if (keycode == KEY_MINUS)
		p->rot_speed++;
	if (keycode == KEY_EQUAL)
		p->rot_speed--;
	return (0);
}

int	on_key_release(int keycode, t_p *p)
{
	ft_printf("KeY; %d\n", keycode);
	if (keycode == KEY_SHIFT)
		p->shifted = 0;
	return (0);
}
