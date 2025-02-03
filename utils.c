/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:39:00 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/03 15:03:23 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	shift_to_white(unsigned int color, int shift_val)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	a;
	float			factor;

	if (shift_val < 0)
		shift_val = 0;
	if (shift_val > 16)
		shift_val = 16;
	factor = shift_val / 16.0f;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	a = (color >> 24) & 0xFF;
	r = r + (255 - r) * factor;
	g = g + (255 - g) * factor;
	b = b + (255 - b) * factor;
	return ((a << 24) | (r << 16) | (g << 8) | b);
}
