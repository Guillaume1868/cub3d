/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:07:09 by gaubert           #+#    #+#             */
/*   Updated: 2022/10/03 15:17:33 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minimap.h"
#include "threed.h"
#include "pixel_put.h"
#include <math.h>

t_image	*get_texture(t_game *g, t_ray *v)
{
	if (v->hit == 'W')
		return (&g->img_w);
	if (v->hit == 'E')
		return (&g->img_e);
	if (v->hit == 'N')
		return (&g->img_n);
	return (&g->img_s);
}

float	get_wall_y(t_ray *v)
{
	if (v->hit == 'N' || v->hit == 'S')
		return (v->rx - (int)v->rx);
	return (v->ry - (int)v->ry);
}

void	put_wall(t_game *g, t_ray *v, int idx, t_range r)
{
	t_image	*t;
	int		tx;
	float	wy;
	int		ty;
	int		bias;

	t = get_texture(g, v);
	wy = get_wall_y(v);
	ty = wy * t->width;
	bias = (r.realh - 1080) / 2 + 1;
	if (bias < 0)
		bias = 0;
	// tx = ((float)(r.i) + bias) / ((float)r.max
	// 		- ((1080 - 1 - r.realh) / 2)) * t->height;
	tx = ((float)(r.i) + bias) / ((float)((1080 - 1 - r.realh) / 2 + r.realh)
			- ((1080 - 1 - r.realh) / 2)) * t->height;
	put_pixels(g, idx, r.i + r.min,
		*(int *)(t->addr + (t->line_length * tx)
			+ (ty * (t->bits_per_pixel / 8))));
}
