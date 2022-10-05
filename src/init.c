/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:46:23 by ldominiq          #+#    #+#             */
/*   Updated: 2022/10/05 12:14:23 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"

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
