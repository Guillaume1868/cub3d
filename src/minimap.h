/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:12:21 by gaubert           #+#    #+#             */
/*   Updated: 2022/09/26 13:47:40 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H
# include "main.h"
# define MMS 64

void	draw_minimap(t_game *g);
void	draw_rays(t_game *g);
void	ray_cast(t_game *g);

typedef struct s_vars2
{
	int		x;
	int		y;
	int		a;
	int		b;
	t_point	end;
	t_point	start;
}				t_vars2;

typedef struct s_rvars
{
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	atan;
	float	hx;
	float	hy;
	float	vx;
	float	vy;
	float	dish;
	float	disv;
	float	dist;
	char	hit;
	char	hitv;
	char	hith;
	t_point	s;
	t_point	e;
}				t_rvars;

void	draw_column(t_game *g, t_ray *v, int color, int idx);

#endif