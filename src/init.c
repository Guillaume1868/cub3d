/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:46:23 by ldominiq          #+#    #+#             */
/*   Updated: 2022/09/22 13:04:47 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"

void	init_map(t_game *g)
{
	g->map = malloc(sizeof(t_map));
	if (!g->map)
		clean("Malloc failed\n", g);
	g->map->tmp = NULL;
	g->map->map_started = 0;
	g->map->max_row = 0;
	g->map->max_col = 0;
	g->map->floor_color = -1;
	g->map->ceiling_color = -1;
	g->p.is_player = 0;
}

void	init_textures(t_game *g)
{
	g->textures = malloc(sizeof(t_tex));
	if (!g->textures)
		clean("Malloc failed\n", g);
	g->textures->tex_num = 0;
	g->textures->tex_x = 0;
	g->textures->tex_y = 0;
	g->textures->width = 0;
	g->textures->height = 0;
	g->textures->wall_x = 0;
	g->textures->tex_pos = 0;
	g->textures->step = 0;
}
