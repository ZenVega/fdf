/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:42:07 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/17 15:56:02 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	permanent_rotation(t_p *p, int keycode)
{
	if (keycode == KEY_SB_OPEN)
		p->x_rot = -1;
	if (keycode == KEY_SB_CLOSE)
		p->x_rot = 1;
	if (keycode == KEY_SEMIC)
		p->y_rot = -1;
	if (keycode == KEY_COMMA)
		p->y_rot = 1;
	if (keycode == KEY_DOT)
		p->z_rot = -1;
	if (keycode == KEY_SLASH)
		p->z_rot = 1;
	if (keycode == KEY_BACKSPACE)
	{
		p->x_rot = 0;
		p->y_rot = 0;
		p->z_rot = 0;
	}
}

void	rotate(t_p *p, int keycode)
{
	t_ang	*ang;

	if (p->shifted)
		permanent_rotation(p, keycode);
	ang = &p->angles;
	p->rot_timer = ROT_TIMER;
	if (keycode == KEY_SB_OPEN)
		get_angles(ang, ang->ang_x, ang->ang_y, ang->ang_z + M_PI / 20);
	if (keycode == KEY_SB_CLOSE)
		get_angles(ang, ang->ang_x, ang->ang_y, ang->ang_z - M_PI / 20);
	if (keycode == KEY_SEMIC)
		get_angles(ang, ang->ang_x, ang->ang_y + M_PI / 20, ang->ang_z);
	if (keycode == KEY_COMMA)
		get_angles(ang, ang->ang_x, ang->ang_y - M_PI / 20, ang->ang_z);
	if (keycode == KEY_DOT)
		get_angles(ang, ang->ang_x + M_PI / 20, ang->ang_y, ang->ang_z);
	if (keycode == KEY_SLASH)
		get_angles(ang, ang->ang_x - M_PI / 20, ang->ang_y, ang->ang_z);
}

void	rotate_point(t_point *point, t_p *p)
{
	double	tmp_x;
	double	tmp_y;
	double	tmp_z;

	tmp_x = point->x * p->angles.cos_z - point->y * p->angles.sin_z;
	tmp_y = point->x * p->angles.sin_z + point->y * p->angles.cos_z;
	tmp_z = (float)point->z * p->scale_factor;
	point->rot_x = tmp_x * p->angles.cos_y + tmp_z * p->angles.sin_y;
	point->rot_z = -tmp_x * p->angles.sin_y + tmp_z * p->angles.cos_y;
	point->rot_y = tmp_y;
	tmp_y = point->rot_y * p->angles.cos_x - point->rot_z * p->angles.sin_x;
	tmp_z = point->rot_y * p->angles.sin_x + point->rot_z * p->angles.cos_x;
	point->rot_y = tmp_y;
}

void	project_point(t_point *point, t_proj proj)
{
	//ft_printf("%d/%d\n", point->x, point->y);
	point->proj_x = proj.x_start + (point->rot_x
			- point->rot_y) * (proj.x_step / 2);
	point->proj_y = proj.y_start + (point->rot_x
			+ point->rot_y) * (proj.y_step / 2) - (point->z * proj.y_step) / 6;
}

void	get_angles(t_ang *angles, double ang_x, double ang_y, double ang_z)
{
	angles->ang_x = ang_x;
	angles->ang_y = ang_y;
	angles->ang_z = ang_z;
	angles->sin_x = sin(ang_x);
	angles->cos_x = cos(ang_x);
	angles->sin_y = sin(ang_y);
	angles->cos_y = cos(ang_y);
	angles->sin_z = sin(ang_z);
	angles->cos_z = cos(ang_z);
}
