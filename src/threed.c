/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threed.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:47:08 by gaubert           #+#    #+#             */
/*   Updated: 2022/09/26 11:27:34 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minimap.h"
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

void	draw_column(t_game *g, t_ray *v, int color, int idx)
{
	float			lineh;
	int				i;
	float			ca;

	ca = g->p.angle - v->ra;
	if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	v->dist = v->dist * cos(ca);
	lineh = (1080) / v->dist;
	if (lineh > 1080)
		lineh = 1080;
	i = (1080 - 1 - lineh) / 2 - 1;
	while (++i < (1080 - 1 - lineh) / 2 + lineh)
		put_pixels(g, idx, i, color);
}
