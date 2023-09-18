/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:00:40 by srapin            #+#    #+#             */
/*   Updated: 2023/09/18 19:13:24 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*mem_zon;
	size_t			i;

	mem_zon = s;
	i = 0;
	while (i < n)
	{
		mem_zon[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (dest || src))
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;

	if (size && SIZE_MAX / size < nmemb)
		return (0);
	tab = malloc(nmemb * size);
	if (!tab)
		return (0);
	ft_memset(tab, 0, nmemb * size);
	return (tab);
}

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

static char	*ft_filltab(unsigned int nb, int lenght, int sign)
{
	char	*number;

	number = ft_calloc(sizeof(char), lenght + 1);
	if (!number)
		return (NULL);
	if (sign < 0)
		number[0] = '-';
	while (nb)
	{
		number[--lenght] = nb % 10 + 48;
		nb /= 10;
	}
	return (number);
}

char	*ft_itoa(int n)
{
	long int	nb;
	int			s;
	int			l;

	s = 1;
	l = 1;
	nb = n;
	if (nb == 0)
		return (ft_strdup("0"));
	if (nb < 0)
	{
		s = -1;
		nb *= -1;
	}
	while (nb > 9)
	{
		nb /= 10;
		l++;
	}
	return (ft_filltab(n * s, l + (s < 0), s));
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