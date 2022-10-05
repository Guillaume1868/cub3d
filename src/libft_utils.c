/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldominiq <ldominiq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:37:55 by ldominiq          #+#    #+#             */
/*   Updated: 2022/10/05 14:39:33 by ldominiq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
