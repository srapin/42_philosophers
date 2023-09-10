/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 00:42:37 by srapin            #+#    #+#             */
/*   Updated: 2023/09/10 19:26:19 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int time_for_task(t_philo *philo)
{
	long long last_meal;
	t_state state = get_state(philo);
	
	if (state == eating)
		return philo->data->time_to_eat;
	if (state == sleeping)
		return philo->data->time_to_sleep;
	if (state == thinking)
	{
		pthread_mutex_lock(&philo->last_meal_access); 
		last_meal = philo->last_meal;
		pthread_mutex_unlock(&philo->last_meal_access);
		if (last_meal >= 0)
			return ((philo->data->time_to_die - philo->data->time_to_eat - philo->data->time_to_sleep) * 0.5);
		else if (philo->id % 2)//premiere iteration +hpilo inpair
				return ((philo->data->time_to_die - philo->data->time_to_eat - philo->data->time_to_sleep) * 0.4);			
	}
	return 0;
}


void change_state(t_philo *philo)
{
	t_state state = get_state(philo);
	if (state == eating && get_prev_fork_id(philo) != get_next_fork_id(philo))
		set_state(philo, sleeping);
	else if (state == sleeping)
		set_state(philo, thinking);
	else if (state == thinking)
		set_state(philo, eating);
}