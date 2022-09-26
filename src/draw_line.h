/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:38:54 by gaubert           #+#    #+#             */
/*   Updated: 2022/09/26 13:15:19 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_LINE_H
# define DRAW_LINE_H
# include "main.h"

void	draw_line(t_game *g, t_point o, t_point i, int color);
void	draw_map_ray(t_game *g, t_ray *v, int color);

typedef struct s_vars
{
	int		dx;
	int		sx;
	int		dy;
	int		sy;
	int		error;
	int		e2;
	t_game	*g;
}				t_vars;

#endif