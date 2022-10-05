/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_border_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:03:21 by lucas             #+#    #+#             */
/*   Updated: 2022/10/05 14:34:03 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"

static void	check_first_char(char *line, t_game *g)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		if (line[i] == '1')
			break ;
		if (line[i] == '0')
			clean("Map is not surrounded by walls\n", g);
	}
}

static void	check_last_char(char *line, t_game *g)
{
	int	i;

	i = g->map->max_col - 1;
	while (i > 0)
	{
		if (line[i] == ' ' || line[i] == '\0')
			i--;
		if (line[i] == '1')
			break ;
		if (line[i] == '0')
			clean("Map is not surrounded by walls\n", g);
	}
}

static void	check_inside(char *line, t_game *g, int y, int x)
{
	char	*tmp;

	tmp = NULL;
	while (line[++x])
	{
		if (line[x] == '0' || ft_strchr("NSEW", line[x]))
		{
			if (x - 1 < 0 || y - 1 < 0 || line[x - 1] == ' ' || \
				line[x + 1] == ' ')
				clean("Map is not surrounded by walls\n", g);
			if (y > 0)
			{
				tmp = &g->map->map[g->map->max_col * (y - 1)];
				if (tmp[x] == ' ')
					clean("Map is not surrounded by walls\n", g);
			}
			if (y < g->map->max_row - 1)
			{
				tmp = &g->map->map[g->map->max_col * (y + 1)];
				if (tmp[x] == ' ')
					clean("Map is not surrounded by walls\n", g);
			}
		}
	}
}

static void	check_last_row(char *line, t_game *g)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == ' ')
			i++;
		else
			clean("Map is not surrounded by walls\n", g);
	}
}

void	check_borders(t_game *g)
{
	int		i;
	char	*line;

	i = 0;
	while (i < g->map->max_row)
	{
		line = &g->map->map[g->map->max_col * i];
		check_first_char(line, g);
		check_last_char(line, g);
		check_inside(line, g, i, -1);
		i++;
	}
	line = &g->map->map[g->map->max_col * (g->map->max_row - 1)];
	check_last_row(line, g);
}
