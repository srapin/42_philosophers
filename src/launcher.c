/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:59:39 by srapin            #+#    #+#             */
/*   Updated: 2023/09/10 20:54:24 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	launch_philos(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->starter_m);
	while (i < data->number_of_philosophers)
	{
		pthread_create(&data->philosophers[i].thread_id, NULL,
			philosophe_routine, data->philosophers + i);
		i++;
	}
	data->start = get_ms_time();
	pthread_mutex_unlock(&data->starter_m);
}

void	launch_number_of_meal_checker(t_data *data)
{
	if (data->number_of_times_each_philosopher_must_eat > 0)
		pthread_create(&data->number_of_meal_checker_thread, NULL,
			number_of_meal_checker_routine, data);
}

void	lets_gow(t_data *data)
{
	launch_philos(data);
	launch_number_of_meal_checker(data);
	supervisor_routine(data);
}
