/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:05:29 by ldominiq          #+#    #+#             */
/*   Updated: 2022/10/05 12:33:53 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"

void	parse_texture(t_game *game, char c, char *line)
{
	char	*path;
	int		x;

	if (game->map->map_started == 1)
		clean("Map is not the last info", game);
	path = ft_strtrim(line, " ");
	if (path == NULL)
		clean("ft_strtrim failed", game);
	printf("path: %s\n", path);
	x = open(path, O_RDONLY);
	if (x < 0)
		clean("Opening xpm file failed", game);
	if (c == 'N')
		game->textures->tex_n = ft_strdup(path);
	else if (c == 'S')
		game->textures->tex_s = ft_strdup(path);
	else if (c == 'W')
		game->textures->tex_w = ft_strdup(path);
	else if (c == 'E')
		game->textures->tex_e = ft_strdup(path);
	game->textures->tex_num = game->textures->tex_num + 1;
	free(path);
	close(x);
}

static int	calculate_color_from_rgb(int r, int g, int b)
{
	int	rgb;

	rgb = r;
	rgb = (rgb << 8) + g;
	rgb = (rgb << 8) + b;
	return (rgb);
}

static	int	get_color(char *line, int *index, t_game *game)
{
	int	color;

	color = ft_atoi(line + *index);
	if (color < 0 || color > 255)
		clean("Invalid rgb values", game);
	while (ft_isdigit(line[*index]))
		(*index)++;
	while (ft_strchr(", ", line[*index]))
		(*index)++;
	return (color);
}

void	parse_color(t_game *game, char *line)
{
	char	info;
	int		r;
	int		g;
	int		b;
	int		index;

	if (game->map->map_started == 1)
		clean("The map is not the last info", game);
	info = *line;
	line++;
	while (ft_iswhitespace(*line))
		line++;
	index = 0;
	r = get_color(line, &index, game);
	g = get_color(line, &index, game);
	b = get_color(line, &index, game);
	if (info == 'F')
		game->floor_color = calculate_color_from_rgb(r, g, b);
	else if (info == 'C')
		game->sky_color = calculate_color_from_rgb(r, g, b);
}
