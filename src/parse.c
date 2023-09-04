/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:29:58 by srapin            #+#    #+#             */
/*   Updated: 2023/09/04 19:01:01 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

bool	ft_strisint(char *str)
{
	bool	flag;
	int		i;

	i = 0;
	flag = true;
	if (!str)
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			flag = false;
		i++;
	}
	return (flag);
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f'
		|| c == '\r');
}

long int	ft_atoi(const char *nptr)
{
	int	i;
	int	neg;
	long int	number;

	i = 0;
	neg = 1;
	number = 0;
	if (!nptr)
		return (0);
	while (nptr[i] && is_whitespace(nptr[i]))
		i++;
	if (nptr[i] && (nptr[i] == '-' || nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			neg = -neg;
		i++;
	}
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		number = number * 10 + (nptr[i] - 48);
		i++;
	}
	return (neg * number);
}

bool	parse(int ac, char **av, t_data *data)
{
	int i;
	struct timeval t;
	
	if (ac != 5 && ac !=6 )
		return (false);
	i = 1;
	while (i < ac)
	{
		//printf("%d = %d\n", i, ft_atoi(av[i]));
		if (!ft_strisint(av[i]) || ft_atoi(av[i]) < 0)
			return false;
		i++;
	}
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	gettimeofday(&t, NULL);
	data->start = t.tv_usec;
	if (ac == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	return true;
}