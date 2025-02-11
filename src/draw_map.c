/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:06:37 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/11 17:22:58 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	draw_top_down(t_p *p)
{
	if (p)
		return ;
}

void	create_projection(int id, t_p *p)
{
	if (id == 1)
		draw_top_down(p);
}

void	draw_map(t_p *p)
{
	create_projection(1, p);
}
