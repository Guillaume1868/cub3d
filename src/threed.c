/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threed.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:47:08 by gaubert           #+#    #+#             */
/*   Updated: 2022/09/27 16:09:03 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minimap.h"
#include "put_wall.h"
#include "pixel_put.h"
#include <math.h>

void	put_pixels(t_game *g, int x, int y, int color)
{
	if ((x < 1920) && (y < 1080) && ! (x < 0
			|| y < 0))
		my_mlx_pixel_put(&g->img2, x, y, color);
}

void	clear_image(t_game *g, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < x)
	{
		j = -1;
		while (++j < y)
			put_pixels(g, i, j, 0x00000000);
	}
}

void	remove_fisheye(t_game *g, t_ray *v)
{
	float	ca;

	ca = g->p.angle - v->ra;
	if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	v->dist = v->dist * cos(ca);
}

void	draw_column(t_game *g, t_ray *v, int idx)
{
	float			lineh;
	int				j;
	t_range			r;

	remove_fisheye(g, v);
	lineh = (1080) / v->dist;
	if (lineh > 1080)
		lineh = 1080;
	r.i = -1;
	r.min = (1080 - 1 - lineh) / 2;
	r.max = (1080 - 1 - lineh) / 2 + lineh;
	j = -1;
	while (++j < r.min)
		put_pixels(g, idx, j, g->sky_color);
	while (r.min + ++r.i < r.max)
		put_wall(g, v, idx, r);
	r.i--;
	while (r.min + ++r.i < 1080)
		put_pixels(g, idx, r.min + r.i, g->floor_color);
}
