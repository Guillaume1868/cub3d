/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:15:08 by ldominiq          #+#    #+#             */
/*   Updated: 2022/06/30 15:46:00 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"

int	check_map_name(char *str)
{
	char	*ext;
	char	*vext;

	vext = ".cub";
	if (!ft_strrchr(str, '.'))
		return (0);
	ext = ft_strrchr(str, '.');
	if (ft_strnstr(ext, vext, ft_strlen(ext))
		&& ft_strlen(ext) == ft_strlen(vext))
		return (1);
	return (0);
}

int	open_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (!check_map_name(file_name))
	{
		printf("Error\nMap extension is incorrect. (.cub)\n");
		return (-1);
	}
	if (fd == -1)
	{
		printf("Error\nAn error occurred when opening the map file.\n");
		return (fd);
	}
	return (fd);
}

void	get_map_size()
{

}

void	set_map(int fd, char *map)
{
	char	*tmp;
	int		x;
	int		y;
	int		height;
	int		width;

	y = 0;
	height = 0;
	width = 0;
	tmp = get_next_line(fd);
	while (tmp != NULL)
	{
		x = 0;
		while (tmp[x])
		{
			while (tmp[x] == ' ')
				x++;
			map[(y * width) + x] = tmp[x];
			x++;
		}
		y++;
		tmp = get_next_line(fd);
	}
}