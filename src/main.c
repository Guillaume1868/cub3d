/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:11:26 by gaubert           #+#    #+#             */
/*   Updated: 2022/10/03 14:57:53 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minimap.h"
#include "move.h"
#include "draw_all.h"
#include <math.h>
#define MAPSIZE 10

char	*fakemap(t_game *g)
{
	char	*map;
	int		i;

	i = -1;
	map = malloc(MAPSIZE * MAPSIZE * sizeof(char));
	while (++i < MAPSIZE * MAPSIZE)
	{
		if (i < MAPSIZE || i > (MAPSIZE * MAPSIZE - MAPSIZE)
			|| i % MAPSIZE == MAPSIZE - 1 || i % MAPSIZE == 0)
			map[i] = '1';
		else
			map[i] = '0';
	}
	map[13] = '1';
	map[42] = '1';
	map[23] = 'N';
	g->p.angle = 3 * PI / 2;
	g->p.x = 3.5;
	g->p.y = 5.5;
	g->p.dx = cos(g->p.angle) / 5;
	g->p.dy = sin(g->p.angle) / 5;
	load_texture(g, &g->img_s, "./img/east.xpm");
	load_texture(g, &g->img_n, "./img/north.xpm");
	load_texture(g, &g->img_e, "./img/tnt.xpm");
	load_texture(g, &g->img_w, "./img/debug.xpm");
	g->sky_color = 0x005050ff;
	g->floor_color = 0x00afafaf;
	return (map);
}

int	clean(t_game *g)
{
	if (g->map != NULL)
		free(g->map);
	if (g->rays != NULL)
		free(g->rays);
	if (g->win != NULL)
		mlx_destroy_window(g->mlx, g->win);
	if (g->win2 != NULL)
		mlx_destroy_window(g->mlx, g->win2);
	// if (g->img_w.addr != NULL)
	// 	mlx_destroy_image(g->mlx, &g->img_w);
	// if (g->img_e.addr != NULL)
	// 	mlx_destroy_image(g->mlx, &g->img_e);
	// if (g->img_s.addr != NULL)
	// 	mlx_destroy_image(g->mlx, &g->img_s);
	// if (g->img_n.addr != NULL)
	// 	mlx_destroy_image(g->mlx, &g->img_n);
	// if (g->img.addr != NULL)
	// 	mlx_destroy_image(g->mlx, &g->img);
	// if (g->img2.addr != NULL)
	// 	mlx_destroy_image(g->mlx, &g->img2);
	exit (0);
}

t_game	*init(t_game *g)
{
	g->map = NULL;
	g->state = starting;
	g->map_height = MAPSIZE;
	g->map_width = MAPSIZE;
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, g->map_width * MMS, g->map_height * MMS,
			"cub3D: minimap");
	g->win2 = mlx_new_window(g->mlx, 1920, 1080, "cub3D: game");
	g->map = fakemap(g);
	g->img.img = mlx_new_image(g->mlx, g->map_width * MMS, g->map_height * MMS);
	g->img.addr = mlx_get_data_addr(g->img.img, &g->img.bits_per_pixel,
			&g->img.line_length, &g->img.endian);
	g->img2.img = mlx_new_image(g->mlx, 1920, 1080);
	g->img2.addr = mlx_get_data_addr(g->img2.img, &g->img2.bits_per_pixel,
			&g->img2.line_length, &g->img2.endian);
	mlx_key_hook(g->win, key_hook, g);
	mlx_hook(g->win, 17, 0, clean, g);
	mlx_key_hook(g->win2, key_hook, g);
	mlx_hook(g->win2, 17, 0, clean, g);
	g->rays = malloc(sizeof(t_ray) * 1920);
	if (g->rays == NULL)
		clean(g);
	return (g);
}

int	main(void)
{
	t_game	g;

	init(&g);
	g.state = playing;
	draw_all(&g);
	mlx_loop(g.mlx);
}
