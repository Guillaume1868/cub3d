/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:05:29 by ldominiq          #+#    #+#             */
/*   Updated: 2022/09/26 14:29:54 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"

void	parse_texture(t_game *game, t_data *img, char *line)
{
	char	*path;
	int		x;

	if (game->map->map_started == 1)
		clean("map is not the last info\n", game);
	path = ft_strtrim(line, " ");
	if (path == NULL)
		clean("ft_strtrim failed\n", game);
	x = ft_strlen(path);
	if (x > 4 && (path[x - 4] != '.' || path[x - 3] != 'x'
			|| path[x - 2] != 'p' || path[x - 1] != 'm'))
		clean(".xpm extension needed\n", game);
	else if (x < 4)
		clean("Invalid texture path\n", game);
	printf("path: %s\n", path);
	x = open(path, O_RDONLY);
	if (x < 0)
		clean("opening xpm file failed\n", game);
	img->img = mlx_xpm_file_to_image(game->mlx, \
				path, &img->width, &img->height);
	printf("0\n");
	if (!img->img)
		clean("xpm_to_image failed\n", game);
	printf("1\n");
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	printf("2\n");
	game->textures->tex_num = game->textures->tex_num + 1;
	printf("3\n");
	free(path);
	close(x);
}

static int	calculate_color_from_rgb(int r, int g, int b)
{
	int	rgb;

	rgb = 0;
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
		clean("invalid rgb values\n", game);
	while (ft_isdigit(line[*index]))
		(*index)++;
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
		clean("map is not the last info\n", game);
	info = *line;
	line++;
	while (ft_iswhitespace(*line))
		line++;
	index = 0;
	r = get_color(line, &index, game);
	g = get_color(line, &index, game);
	b = get_color(line, &index, game);
	if (info == 'F')
		game->map->floor_color = calculate_color_from_rgb(r, g, b);
	else if (info == 'C')
		game->map->ceiling_color = calculate_color_from_rgb(r, g, b);
}
