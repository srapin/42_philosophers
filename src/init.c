/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:49:44 by srapin            #+#    #+#             */
/*   Updated: 2023/09/10 20:50:22 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	set_param(int ac, char **av, t_data *data)
{
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->end = false;
	if (ac == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
}

void	init_philo(t_data *data, t_philo *philo, int i)
{
	philo->id = i;
	philo->has_already_eaten = 0;
	philo->just_took_a_fork = false;
	philo->forks.prev = false;
	philo->forks.next = false;
	philo->state = thinking;
	philo->data = data;
	philo->last_meal = -1;
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philosophers = malloc((data->number_of_philosophers)
			* sizeof(t_philo));
	while (i < data->number_of_philosophers)
	{
		init_philo(data, &(data->philosophers[i]), i);
		i++;
	}
}

void	init(int ac, char **av, t_data *data)
{
	set_param(ac, av, data);
	init_philos(data);
	init_mutexes(data);
}
