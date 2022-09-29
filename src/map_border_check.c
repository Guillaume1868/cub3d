/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_border_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:03:21 by lucas             #+#    #+#             */
/*   Updated: 2022/09/26 11:32:53 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"

// static void	check_first_char(char *line, t_game *g)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == ' ')
// 			i++;
// 		if (line[i] == '1')
// 			break ;
// 		if (line[i] == '0')
// 			clean("Map is not surrounded by walls first\n", g);
// 	}
// }

// static void	check_last_char(char *line, t_game *g)
// {
// 	int	i;

// 	i = g->map->max_col;
// 	while (i > 0)
// 	{
// 		if (line[i] == ' ' || line[i] == '\0')
// 			i--;
// 		if (line[i] == '1')
// 			break ;
// 		if (line[i] == '0')
// 			clean("Map is not surrounded by walls last\n", g);
// 	}
// }

void	check_borders(t_game *g)
{
	int		i;
	char	*line;

	i = 0;
	while (i < g->map->max_row)
	{
		line = &g->map->map[g->map->max_col * i];
		printf("line[%d]: %s\n", i, line);
		printf("max_col: %d\n", g->map->max_col);
		//check_first_char(line, g);
		//check_last_char(line, g);
		i++;
	}
}