/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:46:23 by ldominiq          #+#    #+#             */
/*   Updated: 2022/10/06 14:17:29 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"
#include "minimap.h"
#include "move.h"
#include <math.h>

void	init_map(t_game *g)
{
	g->map = malloc(sizeof(t_map));
	if (!g->map)
		clean("Malloc failed\n", g);
	g->map->tmp = NULL;
	g->map->map = NULL;
	g->map->map_started = 0;
	g->map->max_row = 0;
	g->map->max_col = 0;
	g->p.is_player = 0;
	g->rays = NULL;
	g->win = NULL;
	g->win2 = NULL;
}

void	init_textures(t_game *g)
{
	g->textures = malloc(sizeof(t_tex));
	if (!g->textures)
		clean("Malloc failed\n", g);
	g->textures->tex_num = 0;
	g->textures->tex_n = NULL;
	g->textures->tex_s = NULL;
	g->textures->tex_w = NULL;
	g->textures->tex_e = NULL;
	g->floor_color = -1;
	g->sky_color = -1;
}

static void	setup_player(t_game *g)
{
	g->p.x += .5;
	g->p.y += .5;
	g->p.dx = cos(g->p.angle) / 5;
	g->p.dy = sin(g->p.angle) / 5;
}

void	init_player(t_game *g, char c, int x, int *y)
{
	g->p.is_player++;
	g->p.x = x;
	g->p.y = *y;
	(void) c;
	if (c == 'S')
		g->p.angle = 1 * PI / 2;
	else if (c == 'W')
		g->p.angle = 2 * PI / 2;
	else if (c == 'N')
		g->p.angle = 3 * PI / 2;
	else if (c == 'E')
		g->p.angle = 4 * PI / 2;
}

t_game	*init(t_game *g)
{
	g->state = starting;
	if (!g->map->map_started)
		clean("No valid map", g);
	g->map_height = g->map->max_row;
	g->map_width = g->map->max_col;
	setup_player(g);
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, g->map_width * MMS, g->map_height * MMS,
			"cub3D: minimap");
	g->win2 = mlx_new_window(g->mlx, 1920, 1080, "cub3D: game");
	g->img.img = mlx_new_image(g->mlx, g->map_width * MMS, g->map_height * MMS);
	g->img.addr = mlx_get_data_addr(g->img.img, &g->img.bits_per_pixel,
			&g->img.line_length, &g->img.endian);
	g->img2.img = mlx_new_image(g->mlx, 1920, 1080);
	g->img2.addr = mlx_get_data_addr(g->img2.img, &g->img2.bits_per_pixel,
			&g->img2.line_length, &g->img2.endian);
	mlx_hook(g->win, 17, 0, quit_game, g);
	mlx_hook(g->win2, 2, 0,key_hook, g);
	mlx_hook(g->win, 2, 0,key_hook, g);
	mlx_hook(g->win2, 17, 0, quit_game, g);
	g->rays = malloc(sizeof(t_ray) * 1920);
	if (g->rays == NULL)
		clean("Malloc error", g);
	return (g);
}
