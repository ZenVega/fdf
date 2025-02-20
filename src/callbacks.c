/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:09:00 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/20 18:21:44 by uschmidt         ###   ########.fr       */
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
	if (keycode == KEY_ARR_UP)
		p->center_y = (p->center_y - TRANS_STEP);
	if (keycode == KEY_ARR_DOWN)
		p->center_y = (p->center_y + TRANS_STEP);
	if (keycode == KEY_ARR_LEFT)
		p->center_x = (p->center_x - TRANS_STEP);
	if (keycode == KEY_ARR_RIGHT)
		p->center_x = (p->center_x + TRANS_STEP);
}
