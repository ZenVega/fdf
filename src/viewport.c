/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:09:00 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/20 18:23:57 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	zoom(t_p *p, int keycode)
{
	if (keycode == KEY_I)
		p->zoom *= 1.02;
	if (keycode == KEY_O)
		p->zoom *= .98;
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

void	translate(t_p *p, int keycode)
{
	if (keycode == KEY_ARR_UP || keycode == KEY_W)
		p->center_y = (p->center_y - TRANS_STEP);
	if (keycode == KEY_ARR_DOWN || keycode == KEY_S)
		p->center_y = (p->center_y + TRANS_STEP);
	if (keycode == KEY_ARR_LEFT || keycode == KEY_A)
		p->center_x = (p->center_x - TRANS_STEP);
	if (keycode == KEY_ARR_RIGHT || keycode == KEY_D)
		p->center_x = (p->center_x + TRANS_STEP);
}

void	rot_sequence(t_p *p)
{
	if (--p->rot_timer > 0)
		return ;
	if (p->x_rot == -1)
		rotate(p, KEY_SB_OPEN);
	else if (p->x_rot == 1)
		rotate(p, KEY_SB_CLOSE);
	if (p->y_rot == -1)
		rotate(p, KEY_SEMIC);
	else if (p->y_rot == 1)
		rotate(p, KEY_COMMA);
	if (p->z_rot == -1)
		rotate(p, KEY_DOT);
	else if (p->z_rot == 1)
		rotate(p, KEY_SLASH);
	p->rot_timer = p->rot_speed;
}
