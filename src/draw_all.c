/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:43:08 by gaubert           #+#    #+#             */
/*   Updated: 2022/09/26 16:30:53 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "threed.h"
#include "minimap.h"

void	draw_all(t_game *g)
{
	draw_minimap(g);
	ray_cast(g);
	draw_rays(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	mlx_put_image_to_window(g->mlx, g->win2, g->img2.img, 0, 0);
	mlx_put_image_to_window(g->mlx, g->win, g->img_w.img, 0, 0);
	mlx_put_image_to_window(g->mlx, g->win, g->img_s.img, 128, 0);
	mlx_put_image_to_window(g->mlx, g->win, g->img_n.img, 0, 128);
	mlx_put_image_to_window(g->mlx, g->win, g->img_e.img, 128, 128);
	clear_image(g, 1920, 1080);
}
