/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 00:42:37 by srapin            #+#    #+#             */
/*   Updated: 2023/09/09 20:17:39 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int time_for_task(t_philo *philo)
{
	long long last_meal;
	t_state state;
	
	pthread_mutex_lock(&philo->state_access);
	state = philo->state;
	pthread_mutex_unlock(&philo->state_access);
	if (state == eating)
		return philo->data->time_to_eat;
	if (state == sleeping)
		return philo->data->time_to_sleep;
	if (state == thinking)
	{
		pthread_mutex_lock(&philo->last_meal_access); 
		last_meal = philo->last_meal;
		pthread_mutex_unlock(&philo->last_meal_access);
		if (last_meal >= 0) //apres le premier repas
		{
			// pthread_mutex_lock(&philo->data->can_write);
			// printf("after first meal\n philo nb %d\n", philo->id);
			// pthread_mutex_unlock(&philo->data->can_write);
			return ((philo->data->time_to_die - philo->data->time_to_eat - philo->data->time_to_sleep) * 0.5);
		}
		else //premiere iteration
		{
			if (philo->id % 2) //philo pair
				return ((philo->data->time_to_die - philo->data->time_to_eat - philo->data->time_to_sleep) * 0.4);
		}
			
	}
	return 0;
}

void eat_to_sleep(t_philo *philo)
{
	//unlock
	philo->state = sleeping;
}

void sleep_to_think(t_philo *philo)
{
	philo->state = thinking;
	//wait_for_forks(philo);
}



void think_to_eat(t_philo *philo)
{
	// if (!is_alive(philo))
	// 	return;
	philo->state = eating;
	
}

void change_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->state_access);
	if (philo->state == eating && get_prev_fork_id(philo) != get_next_fork_id(philo))
		eat_to_sleep(philo);
	else if (philo->state == sleeping)
		sleep_to_think(philo);
	else if (philo->state == thinking)
		think_to_eat(philo);
	pthread_mutex_unlock(&philo->state_access);
}