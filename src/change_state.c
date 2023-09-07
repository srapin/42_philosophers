/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 00:42:37 by srapin            #+#    #+#             */
/*   Updated: 2023/09/07 21:16:54 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int time_for_task(t_philo *philo)
{
	if (philo->state == eating)
		return philo->data->time_to_eat;
	if (philo->state == sleeping)
		return philo->data->time_to_sleep;
	if (philo->state == thinking)
		return (philo->data->time_to_die - philo->data->time_to_eat - philo->data->time_to_sleep) * 0.5;
	else
		return -1;
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
	if (!is_alive(philo))
		return;
	philo->state = eating;
	
}

void change_state(t_philo *philo)
{
	if (philo->state == eating)
		eat_to_sleep(philo);
	else if (philo->state == sleeping)
		sleep_to_think(philo);
	else if (philo->state == thinking)
		think_to_eat(philo);
}