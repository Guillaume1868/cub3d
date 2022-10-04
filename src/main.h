/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:08:10 by gaubert           #+#    #+#             */
/*   Updated: 2022/10/04 17:36:29 by ldominiq         ###   ########.fr       */
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
# include <errno.h>
# include <printf.h>
#include <sys/types.h>
#include <sys/uio.h>
# include "../mlx/mlx.h"
# define PI 3.1415926535
# define P2 1.57079632675
# define P3 4.71238898025
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define DR 0.0004848
# include "textures.h"

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
	int			is_player;
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

typedef struct s_tex
{
	char		*tex_n;
	char		*tex_s;
	char		*tex_w;
	char		*tex_e;
	int			tex_num;
}				t_tex;

typedef struct s_map {
	int			map_started;
	int			floor_color;
	int			ceiling_color;
	char		*map;
	char		*tmp;
	int			max_row;
	int			max_col;
}				t_map;

typedef struct s_ray
{
	int		mp;
	float	rx;
	float	ry;
	float	ra;
	float	dist;
	char	hit;
}				t_ray;

typedef struct s_range
{
	int		min;
	int		max;
	int		i;
	int		realh;
}				t_range;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_tex		*textures;
	void		*win2;
	t_data		img;
	t_data		img2;
	int			map_width;
	int			map_height;
	t_player	p;
	t_state		state;
	t_ray		*rays;
	t_image		img_n;
	t_image		img_s;
	t_image		img_e;
	t_image		img_w;
	int			sky_color;
	int			floor_color;
}				t_game;

char	*get_next_line(int fd);
char	*ft_free(char *str);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int		get_map(char *file, t_game *game);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_iswhitespace(int c);
int		clean(char *err_msg, t_game *g);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strdup(const char *src);
void	parse_texture(t_game *game, char c, char *line);
void	parse_color(t_game *game, char *line);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	init_map(t_game *g);
void	init_textures(t_game *g);
void	check_borders(t_game *g);
void	load_texture(t_game *g, t_image *i, char *file);

#endif