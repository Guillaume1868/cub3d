/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:08:10 by gaubert           #+#    #+#             */
/*   Updated: 2022/07/18 15:17:53 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <unistd.h>
# include <printf.h>
# include "../mlx/mlx.h"
# include <stdlib.h>
# define PI 3.1415926535
# define P2 1.57079632675
# define P3 4.71238898025
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define DR 0.0174533

typedef struct s_coord
{
	float		x;
	float		y;
}				t_coord;

typedef struct s_player
{
	float		x;
	float		y;
	float		dx;
	float		dy;
	float		angle;
}				t_player;

typedef struct s_point
{
	int		x;
	int		y;
}				t_point;

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_data;

typedef enum e_state {starting, playing, won, lost}	t_state;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*win2;
	char		*map;
	t_data		img;
	t_data		img2;
	int			map_width;
	int			map_height;
	t_player	p;
	t_state		state;
}				t_game;

int	clean(t_game *g);

#endif