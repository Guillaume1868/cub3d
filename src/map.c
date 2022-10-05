/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:57:19 by ldominiq          #+#    #+#             */
/*   Updated: 2022/10/05 14:31:50 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	fill_map(t_game *g, int i, int j, int k)
{
	g->map->map = ft_calloc((g->map->max_col * g->map->max_row) + 1, \
							sizeof(char));
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

void	setup_map(t_game *g)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	fill_map(g, i, j, k);
}
