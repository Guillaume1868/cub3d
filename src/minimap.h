/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:12:21 by gaubert           #+#    #+#             */
/*   Updated: 2022/07/11 13:00:31 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H
# include "main.h"
# define MMS 64

void	draw_minimap(t_game *g);

typedef struct s_vars2
{
	int		x;
	int		y;
	int		a;
	int		b;
	t_point	end;
	t_point	start;
}				t_vars2;

#endif