/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:03:08 by gaubert           #+#    #+#             */
/*   Updated: 2022/07/18 15:04:47 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minimap.h"
#include <math.h>

void	while_dof(t_game *g, t_rvars *v)
{
	while (v->dof < 8)
	{
		v->mx = (int)(v->rx);
		v->my = (int)(v->ry);
		v->mp = v->my * g->map_width + v->mx;
		if (v->mp > 0 && v->mp < g->map_width * g->map_height
			&& g->map[v->mp] == '1')
			v->dof = 8;
		else
		{
			v->rx += v->xo;
			v->ry += v->yo;
			v->dof += 1;
		}
	}
}

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt(pow(bx - ax, 2) + pow(by - ay, 2)));
}
