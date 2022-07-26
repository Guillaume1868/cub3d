/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:47:08 by gaubert           #+#    #+#             */
/*   Updated: 2022/07/18 18:32:44 by gaubert          ###   ########.fr       */
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
	float	lineh;
	int		i;

	v->dist = v->dist * cos(g->p.angle - v->ra);
	lineh = (1080) / v->dist + 1.0f;
	if (lineh > 1080)
		lineh = 1080;
	i = (1080 - 1 - lineh) / 2;
	printf("i:%d", i);
	while (++i < (1080 - 1 - lineh) / 2 + lineh)
	{
		put_pixels(g, v->r, i, color);
	}
}
