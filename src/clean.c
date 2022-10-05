/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:57:57 by ldominiq          #+#    #+#             */
/*   Updated: 2022/10/05 13:58:18 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
