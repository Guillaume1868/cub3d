/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:11:26 by gaubert           #+#    #+#             */
/*   Updated: 2022/10/04 12:52:49 by ldominiq         ###   ########.fr       */
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

int	clean(char *err_msg, t_game *g)
{
	if (err_msg)
		printf("Error\n%s\n", err_msg);
	if (g->map->map)
		free(g->map->map);
	if (g->map != NULL)
		free(g->map);
	// if (g->textures)
	// 	free(g->textures);
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
	g->state = starting;
	if (!g->map->map_started)
		clean("No valid map", g);
	g->map_height = g->map->max_row;
	g->map_width = g->map->max_col;
	printf("map_h: %d\n", g->map_height);
	printf("map_w: %d\n", g->map_width);
	g->p.x += .5;
	g->p.y += .5;
	printf("p.x = %f\n", g->p.x);
	printf("p.y = %f\n", g->p.y);
	g->p.dx = cos(g->p.angle) / 5;
	g->p.dy = sin(g->p.angle) / 5;
	g->sky_color = 0x005050ff;
	g->floor_color = 0x00afafaf;
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
	g->rays = malloc(sizeof(t_ray) * 1920);
	if (g->rays == NULL)
		clean("Malloc error", g);
	return (g);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char*)s;
	if (n == 0)
		return ;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void *ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, size * count);
	return (ptr);
}

void	setup_map(t_game *g)
{
	int	i;
	int	j;
	int	k;
	
	g->map->map = ft_calloc((g->map->max_col * g->map->max_row) + 1, sizeof(char));
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
				printf("g->map->map[%d * %d + %d]: %c | g->map->max_col * i + j: %d | g->map->tmp[%d]: %c\n", g->map->max_col, i, j, g->map->map[g->map->max_col * i + j], g->map->max_col * i + j, k, g->map->tmp[k]);
				j++;
				k++;
			}
			i++;
		}
	}
	free(g->map->tmp);
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
			load_texture(&g, &g.img_s, "./img/east.xpm");
			load_texture(&g, &g.img_n, "./img/north.xpm");
			load_texture(&g, &g.img_e, "./img/tnt.xpm");
			load_texture(&g, &g.img_w, "./img/debug.xpm");
			g.state = playing;
			draw_all(&g);
			mlx_loop(g.mlx);
		}
	}
	return (ret);
}
