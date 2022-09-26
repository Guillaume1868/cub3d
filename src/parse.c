/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:15:08 by ldominiq          #+#    #+#             */
/*   Updated: 2022/09/22 13:32:52 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"

static int	check_map_name(char *str)
{
	char	*ext;
	char	*vext;

	vext = ".cub";
	if (!ft_strrchr(str, '.'))
		return (0);
	ext = ft_strrchr(str, '.');
	if (ft_strnstr(ext, vext, ft_strlen(ext)) && \
		ft_strlen(ext) == ft_strlen(vext))
		return (1);
	return (0);
}

int	open_file(char *file_name, t_game *g)
{
	int		fd;

	if (!check_map_name(file_name))
		clean("Map extension is incorrect. (.cub)", g);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		return (fd);
	}
	return (fd);
}

void	init_player(t_game *g, char c, int x, int y)
{
	g->p.is_player++;
	g->p.x = x;
	g->p.y = y;
	(void) c;
	if (c == 'S')
		g->p.angle = 1 * PI / 2;
	else if (c == 'W')
		g->p.angle = 2 * PI / 2;
	else if (c == 'N')
		g->p.angle = 3 * PI / 2;
	else if (c == 'E')
		g->p.angle = 4 * PI / 2;
}

void	parse_map(t_game *game, char *line, int y)
{
	int		i;

	game->map->map_started = 1;
	i = 0;
	while (line[i])
	{
		if (ft_strchr("01NSEW 	\n", line[i]) == NULL)
		{
			printf("line: %s\n", line);
			free(line);
			clean("Invalid char inside map", game);
		}
		if (ft_strchr("NSEW", line[i]))
			init_player(game, line[i], i, y);
		i++;
	}
	if (line[i - 1] == '\n')
		line[i - 1] = 0;
	if (game->map->max_col < (int)ft_strlen(line))
		game->map->max_col = (int)ft_strlen(line);
	game->map->tmp = ft_strjoin(game->map->tmp, line);
	game->map->max_row++;
}

static void	parse_line(t_game *game, char *line, int i, int y)
{
	while (ft_iswhitespace(line[i]))
		i++;
	if (line[i] == '\0' && game->map->map_started == 1)
		clean("Empty line inside or after map", game);
	else if (line[i] == '\0' && game->map->map_started == 0)
		return ;
	else if (line[i] == 'N' && line[i + 1] == 'O')
		parse_texture(game, &game->textures->tex[0], line + i + 2);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		parse_texture(game, &game->textures->tex[1], line + i + 2);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		parse_texture(game, &game->textures->tex[2], line + i + 2);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		parse_texture(game, &game->textures->tex[3], line + i + 2);
	else if (line[i] == 'F' || line[i] == 'C')
		parse_color(game, line + i);
	else if (line[i] == '1' || line[i] == '0')
		parse_map(game, line, y);
	else if ((line[i] && line[i] != '\0'))
		clean("Unknown identifier", game);
}

int	get_map(char *file, t_game *game)
{
	int		fd;
	char	*line;
	int		y;

	fd = open_file(file, game);
	line = "";
	if (fd == -1)
		return (-1);
	y = 0;
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		else
			parse_line(game, line, 0, y);
		printf("%s\n", line);
		free(line);
		y++;
	}
	close (fd);
	return (1);
}
