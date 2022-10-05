/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:08:19 by ldominiq          #+#    #+#             */
/*   Updated: 2022/10/05 14:21:40 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	check_player(t_game *g)
{
	if (g->p.is_player == 0)
		clean("No player found", g);
	else if (g->p.is_player > 1)
		clean("Multiple players found", g);
}

void	pre_check(t_game *g)
{
	if (g->textures->tex_num != 4)
		clean("Textures missing", g);
	if (g->sky_color == -1 || g->floor_color == -1)
		clean("One or more colors are missing", g);
}
