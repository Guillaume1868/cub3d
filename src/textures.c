/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:34:25 by gaubert           #+#    #+#             */
/*   Updated: 2022/10/01 15:56:44 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "textures.h"

void	load_texture(t_game *g, t_image *i, char *file)
{
	i->img = mlx_xpm_file_to_image(g->mlx, file, &i->width,
			&i->height);
	if (!i->img)
		clean(g);
	i->addr = mlx_get_data_addr(i->img, &i->bits_per_pixel,
			&i->line_length, &i->endian);
}
