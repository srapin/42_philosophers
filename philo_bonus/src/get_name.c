/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:19:35 by srapin            #+#    #+#             */
/*   Updated: 2023/10/11 00:53:55 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

char	*get_sem_end_access_name(int i)
{
	char		*base;
	char		*number;
	char		*name;

	base = "end_access_";
	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin(base, number);
	free(number);
	return (name);
}

char	*get_sem_end_name(int i)
{
	char		*base;
	char		*number;
	char		*name;

	base = "end_";
	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin(base, number);
	free(number);
	return (name);
}
