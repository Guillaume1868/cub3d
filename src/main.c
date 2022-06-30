/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:11:26 by gaubert           #+#    #+#             */
/*   Updated: 2022/06/30 15:05:51 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minimap.h"

#define MAPSIZE 10

char	*fakemap(void)
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
	map[17] = 'N';
	return (map);
}

int	clean(t_game *g)
{
	free(g->map);
	mlx_destroy_window(g->mlx, g->win);
	exit (0);
}

int	key_hook(int keycode, t_game *g)
{
	printf("%d\n", g->state);
	(void) g;
	if (keycode == 13 && g->state == playing)
		write(1, "13\n", 3);
	else if (keycode == 0 && g->state == playing)
		write(1, "0\n", 2);
	else if (keycode == 1 && g->state == playing)
		write(1, "1\n", 2);
	else if (keycode == 2 && g->state == playing)
		write(1, "2\n", 2);
	else if (keycode == 53)
		clean(g);
	return (0);
}

t_game	*init(t_game *g)
{
	g->map = NULL;
	g->state = starting;
	g->map_height = MAPSIZE;
	g->map_width = MAPSIZE;
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, 1920, 1080, "cub3D");
	g->map = fakemap();
	g->img.img = mlx_new_image(g->mlx, 1920, 1080);
	g->img.addr = mlx_get_data_addr(g->img.img, &g->img.bits_per_pixel,
			&g->img.line_length, &g->img.endian);
	mlx_key_hook(g->win, key_hook, g);
	mlx_hook(g->win, 17, 0, clean, g);
	return (g);
}

int	main(void)
{
	t_game	g;

	setbuf(stdout, NULL);
	init(&g);
	g.state = playing;
	draw_minimap(&g);
	mlx_loop(g.mlx);
}
