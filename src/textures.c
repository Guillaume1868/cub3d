/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:34:25 by gaubert           #+#    #+#             */
/*   Updated: 2022/10/05 14:07:41 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "textures.h"

void	load_texture(t_game *g, t_image *i, char *file)
{
	i->img = mlx_xpm_file_to_image(g->mlx, file, &i->width,
			&i->height);
	if (!i->img)
		clean("Error loading texture", g);
	i->addr = mlx_get_data_addr(i->img, &i->bits_per_pixel,
			&i->line_length, &i->endian);
}

void	setup_textures(t_game *g)
{
	load_texture(g, &g->img_n, g->textures->tex_n);
	load_texture(g, &g->img_s, g->textures->tex_s);
	load_texture(g, &g->img_w, g->textures->tex_w);
	load_texture(g, &g->img_e, g->textures->tex_e);
}
