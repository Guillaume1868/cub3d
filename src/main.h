/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaubert <gaubert@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:08:10 by gaubert           #+#    #+#             */
/*   Updated: 2022/06/30 13:13:06 by gaubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

typedef struct s_coord
{
	float		x;
	float		y;
}				t_coord;

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
	char		*map;
	int			map_width;
	int			map_height;
	t_coord		player_pos;
	t_state		state;
}				t_game;

#endif