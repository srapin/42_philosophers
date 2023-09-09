/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:59:39 by srapin            #+#    #+#             */
/*   Updated: 2023/09/09 20:48:33 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


void set_start_time(t_data *data)
{
	data->start = get_ms_time();
}

void launch_philos(t_data *data)
{
	int i; 
	// t_philo *current_philo;

	i = 0;
	pthread_mutex_lock(&data->starter_m);
	while (i < data->number_of_philosophers)
	{
		pthread_create(&data->philosophers[i].thread_id, NULL, philosophe_routine, data->philosophers + i);
		i++;
	}
	set_start_time(data);
	pthread_mutex_unlock(&data->starter_m);
}

void *number_of_meal_checker_routine(void *arg)
{
	t_data *data = arg;
	int is_not_hungry_anymore;
	int i;

	while (!check_end(data))
	{
		is_not_hungry_anymore = 0;
		i = 0;
		while(i< data->number_of_philosophers)
		{
			if (get_has_already_eaten(data->philosophers + i) >= data->number_of_times_each_philosopher_must_eat)
				is_not_hungry_anymore++;
			i++;
		}
		if (is_not_hungry_anymore == data->number_of_philosophers)
			update_end(data, true);
		usleep(500);
	}
	return NULL; 
}

void launch_number_of_meal_checker(t_data *data)
{
	if (data->number_of_times_each_philosopher_must_eat > 0)
		pthread_create(&data->number_of_meal_checker_thread, NULL, number_of_meal_checker_routine, data);
	
}

void lets_gow(t_data *data)
{
	launch_philos(data);
	launch_number_of_meal_checker(data); 
	supervisor_routine(data);
}