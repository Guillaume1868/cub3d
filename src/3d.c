/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:47:08 by gaubert           #+#    #+#             */
/*   Updated: 2022/07/26 15:26:21 by gaubert          ###   ########.fr       */
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

void	draw_column(t_game *g, t_rvars *v, int color)
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
	printf("%f\n", v->dist);
	while (++i < (1080 - 1 - lineh) / 2 + lineh)
	{
		put_pixels(g, v->r, i, color);
	}
}
