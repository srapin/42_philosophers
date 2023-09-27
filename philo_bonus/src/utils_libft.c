/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:23:26 by srapin            #+#    #+#             */
/*   Updated: 2023/09/27 19:28:17 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

char	*ft_strdup(const char *src)
{
	size_t	len_src;
	char	*cpy;

	len_src = 0;
	while (src[len_src])
		len_src++;
	cpy = (char *)ft_calloc(len_src + 1, sizeof(char));
	if (!cpy)
		return (NULL);
	ft_memcpy(cpy, src, len_src);
	return (cpy);
}

static char	*ft_strcat(char *dest, char const *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	size_t	lenght;

	lenght = 0;
	while (s[lenght])
		lenght++;
	return (lenght);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	join = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!join)
		return (NULL);
	ft_strcat(join, s1);
	ft_strcat(join, s2);
	return (join);
}
