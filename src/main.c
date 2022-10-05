/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:11:26 by gaubert           #+#    #+#             */
/*   Updated: 2022/10/05 13:33:04 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minimap.h"
#include "move.h"
#include "draw_all.h"
#include <math.h>

int	clean(char *err_msg, t_game *g)
{
	if (err_msg)
		printf("Error\n%s\n", err_msg);
	if (g->map->map)
		free(g->map->map);
	if (g->map != NULL)
		free(g->map);
	if (g->textures)
		free(g->textures);
	if (g->rays != NULL)
		free(g->rays);
	if (g->win != NULL)
		mlx_destroy_window(g->mlx, g->win);
	if (g->win2 != NULL)
		mlx_destroy_window(g->mlx, g->win2);
	exit (0);
}

int	quit_game(t_game *g)
{
	clean(NULL, g);
	return (0);
}

t_game	*init(t_game *g)
{
	g->state = starting;
	if (!g->map->map_started)
		clean("No valid map", g);
	g->map_height = g->map->max_row;
	g->map_width = g->map->max_col;
	g->p.x += .5;
	g->p.y += .5;
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
	mlx_hook(g->win, 17, 0, quit_game, g);
	mlx_key_hook(g->win2, key_hook, g);
	mlx_hook(g->win2, 17, 0, quit_game, g);
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

void	setup_textures(t_game *g)
{
	load_texture(g, &g->img_n, g->textures->tex_n);
	load_texture(g, &g->img_s, g->textures->tex_s);
	load_texture(g, &g->img_w, g->textures->tex_w);
	load_texture(g, &g->img_e, g->textures->tex_e);
}

int	main(int argc, char *argv[])
{
	t_game	g;
	int 	ret;
	
	ret = -1;
	if (argc == 2)
	{
		init_map(&g);
		init_textures(&g);
		ret = get_map(argv[1], &g);
		if (g.textures->tex_num != 4)
			clean("Textures missing", &g);
		if (g.sky_color == -1 || g.floor_color == -1)
			clean("One or more colors are missing", &g);
		if (ret == 1)
		{
			check_player(&g);
			setup_map(&g);
			check_borders(&g);
			init(&g);
			setup_textures(&g);
			g.state = playing;
			draw_all(&g);
			mlx_loop(g.mlx);
		}
	}
	return (ret);
}
