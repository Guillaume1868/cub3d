/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:11:26 by gaubert           #+#    #+#             */
/*   Updated: 2022/09/29 17:03:12 by ldominiq         ###   ########.fr       */
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
		printf("Error\n%s\n", err_msg);
	if (g->map->map)
		free(g->map->map);
	if (g->map)
		free(g->map);
	if (g->textures)
		free(g->textures);
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	exit (0);
}

t_game	*init(t_game *g)
{
	g->state = starting;
	if (!g->map->map_started)
		clean("No valid map", g);
	g->map_height = g->map->max_row;
	g->map_width = g->map->max_col;
	printf("map_h: %d\n", g->map_height);
	printf("map_w: %d\n", g->map_width);
	//g->p.angle = 2 * PI / 2;
	g->p.x += .5;
	g->p.y += .5;
	printf("p.x = %f\n", g->p.x);
	printf("p.y = %f\n", g->p.y);
	g->p.dx = cos(g->p.angle) / 5;
	g->p.dy = sin(g->p.angle) / 5;
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
	
	g->map->map = malloc((g->map->max_col * g->map->max_row) + 1);
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
					g->map->map[g->map->max_col * i + j] = 0;
					printf("tmp[k]: %c\n", g->map->tmp[k]);
					k++;
					break ;
				}
				g->map->map[g->map->max_col * i + j] = g->map->tmp[k];
				printf("g->map->map[%d * %d + %d]: %c | g->map->max_col * i + j: %d | g->map->tmp[%d]: %c\n", g->map->max_col, i, j, g->map->map[g->map->max_col * i + j], g->map->max_col * i + j, k, g->map->tmp[k]);
				j++;
				k++;
			}
			i++;
		}
		g->map->map[g->map->max_col * (i - 1) + j] = 0;
		printf("g->map->map[g->map->max_col * %d + %d]: %d\n", (i - 1), j, g->map->map[g->map->max_col * (i - 1) + j]);
	}
	printf("map: %s\n", g->map->map);
	printf("tmp: %s\n", g->map->tmp);
	//free(g->map->tmp);
}

void	check_player(t_game *g)
{
	if (g->p.is_player == 0)
		clean("No player found", g);
	else if (g->p.is_player > 1)
		clean("Multiple players found", g);
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
		//init_textures(&g);
		ret = get_map(argv[1], &g);
		printf("ret: %d\n", ret);
		if (ret == 1)
		{
			check_player(&g);
			setup_map(&g);
			check_borders(&g);
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
