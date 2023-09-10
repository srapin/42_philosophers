/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 20:49:48 by srapin            #+#    #+#             */
/*   Updated: 2023/09/10 20:45:17 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	wait_other_threads(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	if (data->number_of_times_each_philosopher_must_eat > 0)
		pthread_join(data->number_of_meal_checker_thread, NULL);
	while (i < data->number_of_philosophers)
	{
		ret = pthread_join(data->philosophers[i].thread_id, NULL);
		if (ret)
		{
			pthread_mutex_lock(&data->can_write);
			printf("some prob errcode = %d\n", ret);
			pthread_mutex_unlock(&data->can_write);
		}
		i++;
	}
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->end_access);
	pthread_mutex_destroy(&data->can_write);
	pthread_mutex_destroy(&data->starter_m);
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philosophers[i].state_access);
		pthread_mutex_destroy(&data->philosophers[i].last_meal_access);
		pthread_mutex_destroy(&data->philosophers[i].has_already_eaten_access);
		i++;
	}
}

void	ft_exit(t_data *data)
{
	wait_other_threads(data);
	destroy_mutexes(data);
	free(data->philosophers);
	free(data->forks);
}
