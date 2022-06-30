/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:11:26 by gaubert           #+#    #+#             */
/*   Updated: 2022/06/30 13:39:28 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include <stdlib.h>
#include "main.h"
#include <unistd.h>
#include <printf.h>
#define MAPSIZE 5

char	*fakemap(void)
{
	char	*map;
	int		i;

	i = -1;
	map = malloc(MAPSIZE * MAPSIZE * sizeof(char));
	while (++i < MAPSIZE * MAPSIZE)
	{
		if (i < MAPSIZE || i > (MAPSIZE * MAPSIZE - MAPSIZE)
			|| i % MAPSIZE == 1 || i % MAPSIZE == 0)
			map[i] = '1';
		else
			map[i] = '0';
	}
	map[13] = '1';
	map[17] = 'N';
	return (map);
}

int	clean(t_game *g)
{
	free(g->map);
	//mlx_destroy_window(g->mlx, g->win);
	//free (g);
	exit (0);
}

int	key_hook(int keycode, t_game *g)
{
	printf("%d\n", g->state);
	(void) g;
	if (keycode == 13 && g->state == playing)
		write(1, "13", 2);
	else if (keycode == 0 && g->state == playing)
		write(1, "0", 1);
	else if (keycode == 1 && g->state == playing)
		write(1, "1", 1);
	else if (keycode == 2 && g->state == playing)
		write(1, "2", 1);
	else if (keycode == 53)
		clean(g);
	return (0);
}

t_game	*init(t_game *g)
{
	g->state = starting;
	g->map_height = MAPSIZE;
	g->map_width = MAPSIZE;
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, 1920, 1080, "cub3D");
	g->map = fakemap();
	mlx_key_hook(g->win, key_hook, &g);
	mlx_hook(g->win, 17, 0, clean, &g);
	return (g);
}

int	main(void)
{
	t_game	g;

	init(&g);
	g.state = playing;
	mlx_loop(g.mlx);
}
