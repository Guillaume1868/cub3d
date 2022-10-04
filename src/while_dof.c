/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   while_dof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:49:18 by gaubert           #+#    #+#             */
/*   Updated: 2022/09/26 13:52:20 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	while_dof2(t_rvars *v, char is_vertical)
{
	if (is_vertical)
	{
		if (v->ra > P2 && v->ra < P3)
			v->hitv = 'W';
		else
			v->hitv = 'E';
	}
	else
	{
		if (v->ra > 0 && v->ra < PI)
			v->hith = 'S';
		else
			v->hith = 'N';
	}
	v->dof = 8;
}

void	while_dof(t_game *g, t_rvars *v, char is_vertical)
{
	while (v->dof < 8)
	{
		v->mx = (int)(v->rx);
		v->my = (int)(v->ry);
		v->mp = v->my * g->map_width + v->mx;
		if (v->mp > 0 && v->mp < g->map_width * g->map_height
			&& g->map[v->mp] == '1')
			while_dof2(v, is_vertical);
		else
		{
			v->rx += v->xo;
			v->ry += v->yo;
			v->dof += 1;
		}
	}
}
