/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:41:45 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/18 16:48:31 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#define LINE_HEIGHT 16
#define TEXT_COL 0xFFFFFFFF
#define MENUE_LEN 17
#define M_Y_OFF 80
#define M_X_OFF 30
#define M_COL 120

#include "../includes/fdf.h"

char	**get_keys(void)
{
	char	*keys_str;
	char	**keys;

	keys_str = "\
rotate X|\
rotate Y|\
rotate Z|\
start rotation|\
stop rotation|\
 |\
zoom in|\
zoom out|\
 |\
scale up|\
scale down|\
 |\
toggle noise|\
 |\
reset|\
 |\
exit|\
";
	keys = ft_split(keys_str, '|');
	return (keys);
}

char	**get_vals(void)
{
	char	*vals_str;
	char	**vals;

	vals_str = "\
[[] - []]|\
[;] - [']|\
[.] - [/]|\
[SHIFT] + rotate|\
[BACKSPACE]|\
 |\
[I] // [Click left]|\
[O] // [Click right]|\
 |\
[S]|\
[SHIFT] + [S]|\
 |\
[N]|\
 |\
[X]|\
 |\
[ESC]|\
";
	vals = ft_split(vals_str, '|');
	return (vals);
}

void	print_menue(t_p *p)
{
	int		i;
	char	**keys;
	char	**vals;

	keys = get_keys();
	vals = get_vals();
	i = 0;
	mlx_string_put(p->mlx, p->win, M_X_OFF,
		M_Y_OFF - LINE_HEIGHT, TEXT_COL, "ACTIONS");
	mlx_string_put(p->mlx, p->win, M_X_OFF + M_COL,
		M_Y_OFF - LINE_HEIGHT, TEXT_COL, "CONTROLS");
	while (i < MENUE_LEN)
	{
		mlx_string_put(p->mlx, p->win, M_X_OFF, M_Y_OFF
			+ ((i + 1) * LINE_HEIGHT), TEXT_COL, keys[i]);
		mlx_string_put(p->mlx, p->win, M_X_OFF + M_COL,
			M_Y_OFF + ((i + 1) * LINE_HEIGHT), TEXT_COL, vals[i]);
		i++;
	}
}
