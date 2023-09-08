/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 20:55:49 by srapin            #+#    #+#             */
/*   Updated: 2023/09/08 19:56:26 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
	
void update_last_meal(t_philo * philo, long long rel_time)
{
	// pthread_mutex_lock(&philo->data->can_write);
	printf("updating last meal %lld\n philo nb %d\n", rel_time,  philo->id);
	// pthread_mutex_unlock(&philo->data->can_write);
			
	// pthread_mutex_lock(&philo->last_meal_access);
	// philo->last_meal = rel_time;
	// pthread_mutex_unlock(&philo->last_meal_access);
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