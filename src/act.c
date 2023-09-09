/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 00:35:34 by srapin            #+#    #+#             */
/*   Updated: 2023/09/09 21:11:02 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_sleep(t_philo *philo)
{
	long long task_time = time_for_task(philo);
	int sleep_base = 100;
	long long target = get_relativ_ms_time(philo->data) + task_time;
	while (get_relativ_ms_time(philo->data) < target)
	{
		if (!is_alive(philo))
			return ;
		usleep(sleep_base);
	}
}

void philo_eat(t_philo * philo)
{
	ft_sleep(philo);
	pthread_mutex_unlock(&(philo->data->forks[get_prev_fork_id(philo)]));
	philo->forks.prev = false;
	if (get_prev_fork_id(philo) != get_next_fork_id(philo))
	{
		pthread_mutex_unlock(&(philo->data->forks[get_next_fork_id(philo)]));
		philo->forks.next = false;
		update_has_already_eaten(philo);
	}
}

void philo_sleep(t_philo * philo)
{
	ft_sleep(philo);
}

void philo_think(t_philo * philo)
{
	ft_sleep(philo);
	pthread_mutex_lock(&(philo->data->forks[get_prev_fork_id(philo)]));
	philo->just_took_a_fork = true;
	philo->forks.prev = true;
	
	print_state(philo);
	if (get_next_fork_id(philo) != get_prev_fork_id(philo))
	{
		pthread_mutex_lock(&(philo->data->forks[get_next_fork_id(philo)]));
		philo->just_took_a_fork = true;
		philo->forks.next = true;
		print_state(philo);
	}
}



void act(t_philo *philo)
{
	print_state(philo);
	pthread_mutex_lock(&philo->state_access);
	t_state state = philo->state;
	pthread_mutex_unlock(&philo->state_access);
	if (state == sleeping)
		philo_sleep(philo);
	else if (state == thinking)
		philo_think(philo);
	else if (state == eating)
		philo_eat(philo);
}