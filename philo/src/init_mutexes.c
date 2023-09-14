/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:48:21 by srapin            #+#    #+#             */
/*   Updated: 2023/09/10 20:50:25 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(data->number_of_philosophers
			* sizeof(pthread_mutex_t));
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&(data->forks[i]), NULL);
		i++;
	}
}

void	init_one_philo_mutexes(t_philo *philo)
{
	pthread_mutex_init(&(philo->state_access), NULL);
	pthread_mutex_init(&(philo->last_meal_access), NULL);
	pthread_mutex_init(&(philo->has_already_eaten_access), NULL);
}

void	init_philos_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		init_one_philo_mutexes(&(data->philosophers[i]));
		i++;
	}
}

void	init_mutexes(t_data *data)
{
	init_forks(data);
	init_philos_mutexes(data);
	pthread_mutex_init(&(data->can_write), NULL);
	pthread_mutex_init(&(data->starter_m), NULL);
	pthread_mutex_init(&(data->end_access), NULL);
}
