/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                          :+:      :+:    :+:   */
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

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt(pow(bx - ax, 2) + pow(by - ay, 2)));
}

void	store_ray(t_game *g, t_rvars *v)
{
	t_ray	*ray;

	ray = &g->rays[v->r];
	ray->dist = v->dist;
	ray->hit = v->hit;
	ray->mp = v->mp;
	ray->ra = v->ra;
	ray->rx = v->rx;
	ray->ry = v->ry;
}

void	anti_bad(t_ray *rays)
{
	int	column;

	column = 0;
	while (++column < 1919)
	{
		if (rays[column - 1].hit == rays[column + 1].hit
			&& rays[column].hit != rays[column - 1].hit)
			rays[column].hit = rays[column + 1].hit;
		if (rays[column].dist - 0.1 >= rays[column + 1].dist && \
			rays[column].dist - 0.1 >= rays[column - 1].dist)
		{
			rays[column].dist = rays[column + 1].dist;
			rays[column].rx = rays[column + 1].rx;
			rays[column].ry = rays[column + 1].ry;
		}
	}
}
