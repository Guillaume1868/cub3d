/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:11:26 by gaubert           #+#    #+#             */
/*   Updated: 2022/09/01 12:27:50 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minimap.h"
#include "move.h"
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
	map[23] = 'N';
	g->p.angle = 3 * PI / 2;
	g->p.x = 3.5;
	g->p.y = 5.5;
	g->p.dx = cos(g->p.angle) / 5;
	g->p.dy = sin(g->p.angle) / 5;
	return (map);
}

int	clean(char *err_msg, t_game *g)
{
	if (err_msg)
		printf("%s", err_msg);
	free(g->map);
	free(g->textures);
	mlx_destroy_window(g->mlx, g->win);
	exit (0);
}

t_game	*init(t_game *g)
{
	g->state = starting;
	g->map_height = g->map->max_row;
	g->map_width = g->map->max_col;
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
	mlx_key_hook(g->win, key_hook, g);
	mlx_hook(g->win, 17, 0, clean, g);
	mlx_key_hook(g->win2, key_hook, g);
	mlx_hook(g->win2, 17, 0, clean, g);
	return (g);
}

void	setup_map(t_game *g)
{
	int	i;
	int	j;
	int	k;

	g->map->map = malloc(g->map->max_col * g->map->max_row);
	if (g->map->map != NULL)
	{
		i = 0;
		k = 0;
		while (i < g->map->max_row)
		{
			j = 0;
			while (j < g->map->max_col)
			{
				if (g->map->tmp[k] == '\n' || g->map->tmp[k] == 0)
				{
					k++;
					break ;
				}
				g->map->map[g->map->max_col * i + j] = g->map->tmp[k];
				j++;
				k++;
			}
			i++;
		}
	}
}

int	main(int argc, char *argv[])
{
	t_game	g;
	int 	ret;
	// int x;
	// x = open("./src/textures/grass.xpm", O_RDONLY);
	// printf("open: %d\n", x);
	ret = -1;
	if (argc == 2)
	{
		init_map(&g);
		init_textures(&g);
		ret = get_map(argv[1], &g);
		printf("ret: %d\n", ret);
		if (ret == 1)
		{
			setup_map(&g);
			init(&g);
			g.state = playing;
			draw_minimap(&g);
			mlx_loop(g.mlx);
		}
	}
	// printf("tmp: %s\n", g.map->tmp);
	// printf("map: %s\n", g.map->map);
	// printf("map + (34 * 5 + 0): %s\n", g.map->map + 170);
	// printf("map + (34 * 13 + 0): %s\n", g.map->map + 442);
	// printf("map[34 * 5 + 10]: %c\n", (char)g.map->map[34 * 5 + 9]);
	// printf("map width: %d\n", g.map->max_col);
	//printf("map height: %d\n", g.map->max_row);
	//printf("%d\n", g.map->ceiling_color);
	//printf("%d\n", g.map->floor_color);
	return (ret);
}
