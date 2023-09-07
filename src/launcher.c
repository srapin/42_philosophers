/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:59:39 by srapin            #+#    #+#             */
/*   Updated: 2023/09/07 21:00:47 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


void set_start_time(t_data *data)
{
	int i = -1;

	data->start = get_ms_time();
	while (i <= data->number_of_philosophers)
	{
		data->philosophers[i].last_meal = data->start;
		i++;
	}	
}

void launch_philos(t_data *data)
{
	int i; 
	t_philo *current_philo;

	i = 0;
	pthread_mutex_lock(&data->starter_m);
	while (i < data->number_of_philosophers)
	{
		current_philo = &(data->philosophers[i]);
		pthread_create(&data->philosophers[i].thread_id, NULL, philosophe_routine, data->philosophers + i);
		i++;
	}
	set_start_time(data);
	pthread_mutex_unlock(&data->starter_m);
}

void lets_gow(t_data *data)
{
	launch_philos(data);
	supervisor_routine(data);
}