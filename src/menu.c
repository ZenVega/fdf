/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:41:45 by uschmidt          #+#    #+#             */
/*   Updated: 2025/02/18 17:38:32 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/fdf.h"

void	get_keys(t_menu *menu)
{
	menu->keys[0] = "rotate X";
	menu->keys[1] = "rotate Y";
	menu->keys[2] = "rotate Z";
	menu->keys[3] = "start rotation";
	menu->keys[4] = "stop rotation";
	menu->keys[5] = "rotation speed";
	menu->keys[6] = "";
	menu->keys[7] = "zoom in";
	menu->keys[8] = "zoom out";
	menu->keys[9] = "";
	menu->keys[10] = "";
	menu->keys[11] = "translate";
	menu->keys[12] = " ";
	menu->keys[13] = "scale up";
	menu->keys[14] = "scale down";
	menu->keys[15] = "";
	menu->keys[16] = "toggle noise";
	menu->keys[17] = "toggle projection";
	menu->keys[18] = "toggle color";
	menu->keys[19] = "";
	menu->keys[20] = "reset";
	menu->keys[21] = "";
	menu->keys[22] = "exit";
}

void	get_vals(t_menu *menu)
{
	menu->vals[0] = "[[] - []]";
	menu->vals[1] = "[;] - [']";
	menu->vals[2] = "[.] - [/]";
	menu->vals[3] = "[SHIFT] + rotate";
	menu->vals[4] = "[BACKSPACE]";
	menu->vals[5] = "[-] - [=]";
	menu->vals[6] = " ";
	menu->vals[7] = "[I] // [Click left]";
	menu->vals[8] = "[O] // [Click right]";
	menu->vals[9] = " ";
	menu->vals[10] = "   [W]";
	menu->vals[11] = "[A][S][D]";
	menu->vals[12] = " ";
	menu->vals[13] = "[Q]";
	menu->vals[14] = "[SHIFT] + [Q]";
	menu->vals[15] = " ";
	menu->vals[16] = "[N]";
	menu->vals[17] = "[P]";
	menu->vals[18] = "[C]";
	menu->vals[19] = " ";
	menu->vals[20] = "[X]";
	menu->vals[21] = " ";
	menu->vals[22] = "[ESC]";
}

void	print_menu(t_p *p, t_menu *menu)
{
	int		i;

	i = 0;
	mlx_string_put(p->mlx, p->win, M_X_OFF,
		M_Y_OFF - LINE_HEIGHT, TEXT_COL, "ACTIONS");
	mlx_string_put(p->mlx, p->win, M_X_OFF + M_COL,
		M_Y_OFF - LINE_HEIGHT, TEXT_COL, "CONTROLS");
	while (i < MENU_LEN)
	{
		mlx_string_put(p->mlx, p->win, M_X_OFF, M_Y_OFF
			+ ((i + 1) * LINE_HEIGHT), TEXT_COL, menu->keys[i]);
		mlx_string_put(p->mlx, p->win, M_X_OFF + M_COL,
			M_Y_OFF + ((i + 1) * LINE_HEIGHT), TEXT_COL, menu->vals[i]);
		i++;
	}
}
