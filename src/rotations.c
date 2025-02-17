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

void	rotate(t_p *p, int keycode)
{
	t_ang	*ang;

	ang = &p->angles;
	if (keycode == 116)
		get_angles(ang, ang->ang_x, ang->ang_y, ang->ang_z + M_PI / 20);
	if (keycode == 121)
		get_angles(ang, ang->ang_x, ang->ang_y, ang->ang_z - M_PI / 20);
	if (keycode == 103)
		get_angles(ang, ang->ang_x, ang->ang_y + M_PI / 20, ang->ang_z);
	if (keycode == 104)
		get_angles(ang, ang->ang_x, ang->ang_y - M_PI / 20, ang->ang_z);
}

void	rotate_point(t_point *point, t_p *p)
{
	point->rot_x = point->x * p->angles.cos_z - point->y * p->angles.sin_z;
	point->rot_y = point->x * p->angles.sin_z + point->y * p->angles.cos_z;
	point->rot_x = point->x * p->angles.cos_y - point->z * p->angles.sin_y;
	point->rot_z = point->x * p->angles.sin_y + point->z * p->angles.cos_y;
	point->rot_y = point->y * p->angles.cos_x - point->z * p->angles.sin_x;
	point->rot_z = point->y * p->angles.sin_x + point->z * p->angles.cos_x;
}

void	project_point(t_point *point, t_proj proj)
{
	point->proj_x = proj.x_start + (point->rot_x - point->rot_y) * (proj.x_step / 2);
	point->proj_y = proj.y_start + (point->rot_x + point->rot_y) * (proj.y_step / 2)
		- (point->z * proj.y_step) / 6;
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
