/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mutex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:44:45 by srapin            #+#    #+#             */
/*   Updated: 2023/09/10 21:10:27 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	update_end(t_data *data, bool value)
{
	pthread_mutex_lock(&data->end_access);
	data->end = value;
	pthread_mutex_unlock(&data->end_access);
}

void	update_has_already_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->has_already_eaten_access);
	philo->has_already_eaten++;
	pthread_mutex_unlock(&philo->has_already_eaten_access);
}

void	set_state(t_philo *philo, t_state s)
{
	pthread_mutex_lock(&philo->state_access);
	philo->state = s;
	pthread_mutex_unlock(&philo->state_access);
}

void	update_last_meal(t_philo *philo, long long rel_time)
{
	pthread_mutex_lock(&philo->last_meal_access);
	philo->last_meal = rel_time;
	pthread_mutex_unlock(&philo->last_meal_access);
}
