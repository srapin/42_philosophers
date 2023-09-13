/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:55:49 by srapin            #+#    #+#             */
/*   Updated: 2023/09/13 00:47:08 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	time_for_task(t_philo *philo)
{
	long long	last_meal;
	t_state		state;

	state = get_state(philo);
	if (state == eating)
		return (philo->data->time_to_eat);
	if (state == sleeping)
		return (philo->data->time_to_sleep);
	if (state == thinking)
	{
		last_meal = philo->last_meal;
		// if (last_meal >= 0)
		// 	return ((philo->data->time_to_die - philo->data->time_to_eat
		// 			- philo->data->time_to_sleep) * 0.5);
		if (last_meal > 0)
			return ((philo->data->time_to_die - philo->data->time_to_eat
					- philo->data->time_to_sleep) * 0.5);
	}
	return (0);
}

long long get_ms_time()
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long get_relativ_ms_time(t_data *data)
{
	long long t = get_ms_time();
	return t - data->start;
}