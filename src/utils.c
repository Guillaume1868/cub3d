/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils 2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:26:39 by ldominiq          #+#    #+#             */
/*   Updated: 2022/09/01 11:54:37 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minimap.h"
#include <math.h>

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((char)s[i] == (char)c)
			return ((char *)s);
		i++;
	}
	return (NULL);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;

	ptr = NULL;
	if (c == 0)
		ptr = ft_strchr(s, c);
	while (*s)
	{
		if (*s == (char)c)
			ptr = (char *)s;
		s++;
	}
	return (ptr);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*result;

	result = (char *)haystack;
	j = 0;
	if (ft_strlen(needle) == 0)
		return (result);
	while (result[j] != '\0' && len >= ft_strlen(needle))
	{
		i = 0;
		while (result[j + i] == needle[i] && \
				result[j + i] != '\0' && needle[i] != '\0')
			i++;
		if (needle[i] == '\0')
			return (&result[j]);
		j++;
		len--;
	}
	return (NULL);
}

int	ft_iswhitespace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' \
		|| c == '\r' || c == ' ')
		return (1);
	return (0);
}

void	while_dof(t_game *g, t_rvars *v)
{
	while (v->dof < 8)
	{
		v->mx = (int)(v->rx);
		v->my = (int)(v->ry);
		v->mp = v->my * g->map_width + v->mx;
		if (v->mp > 0 && v->mp < g->map_width * g->map_height
			&& g->map->map[v->mp] == '1')
		{
			v->dof = 8;
		}
		else
		{
			v->rx += v->xo;
			v->ry += v->yo;
			v->dof += 1;
		}
		if (v->mp > 0 && v->mp < g->map_width * g->map_height)
			v->hit = g->map->map[v->mp];
	}
	if (v->hit == 'N' || v->hit == 'W' || v->hit == 'E' || v->hit == 'S')
		v->hit = '0';
}

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt(pow(bx - ax, 2) + pow(by - ay, 2)));
}
