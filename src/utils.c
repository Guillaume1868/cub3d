/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:03:08 by gaubert           #+#    #+#             */
/*   Updated: 2022/09/26 16:10:51 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minimap.h"
#include <math.h>

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt(pow(bx - ax, 2) + pow(by - ay, 2)));
}

void	store_ray(t_game *g, t_rvars *v)
{
	t_ray	*ray;

	ray = &g->rays[v->r];
	ray->dist = v->dist;
	ray->hit = v->hit;
	ray->mp = v->mp;
	ray->ra = v->ra;
	ray->rx = v->rx;
	ray->ry = v->ry;
}

void	anti_bad(t_ray *rays)
{
	int	column;

	column = 0;
	while (++column < 1919)
	{
		if (rays[column - 1].hit == rays[column + 1].hit
			&& rays[column].hit != rays[column - 1].hit)
			rays[column].hit = rays[column + 1].hit;
		if (rays[column].dist - 0.1 >= rays[column + 1].dist && \
			rays[column].dist - 0.1 >= rays[column - 1].dist)
		{
			rays[column].dist = rays[column + 1].dist;
			rays[column].rx = rays[column + 1].rx;
			rays[column].ry = rays[column + 1].ry;
		}
	}
}
