/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:11:26 by gaubert           #+#    #+#             */
/*   Updated: 2022/10/05 14:30:15 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "draw_all.h"

int	quit_game(t_game *g)
{
	clean(NULL, g);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_game	g;
	int		ret;

	ret = -1;
	if (argc == 2)
	{
		init_map(&g);
		init_textures(&g);
		ret = get_map(argv[1], &g);
		pre_check(&g);
		if (ret == 1)
		{
			check_player(&g);
			setup_map(&g);
			check_borders(&g);
			init(&g);
			setup_textures(&g);
			g.state = playing;
			draw_all(&g);
			mlx_loop(g.mlx);
		}
	}
	return (ret);
}
