/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:38:54 by gaubert           #+#    #+#             */
/*   Updated: 2022/07/01 15:40:24 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_LINE_H
# define DRAW_LINE_H

void	draw_line(t_game *g, t_point o, t_point i, int color);

typedef struct s_vars
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	error;
	int	e2;
}				t_vars;

#endif