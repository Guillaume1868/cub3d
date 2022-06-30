/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:08:10 by gaubert           #+#    #+#             */
/*   Updated: 2022/06/30 14:18:39 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

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

char	*get_next_line(int fd);
char	*ft_free(char *str);
int		ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);

#endif