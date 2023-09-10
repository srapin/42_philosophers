/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 00:35:34 by srapin            #+#    #+#             */
/*   Updated: 2023/09/10 20:34:03 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_wait(t_philo *philo)
{
	long long	task_time;
	int			sleep_base;
	long long	target;

	task_time = time_for_task(philo);
	sleep_base = 100;
	target = get_relativ_ms_time(philo->data) + task_time;
	while (get_relativ_ms_time(philo->data) < target)
	{
		if (get_state(philo) == died)
			return ;
		usleep(sleep_base);
	}
}

void	philo_eat(t_philo *philo)
{
	philo_wait(philo);
	if (philo->forks.prev && philo->forks.next)
		update_has_already_eaten(philo);
	if (philo->forks.prev)
	{
		pthread_mutex_unlock(&(philo->data->forks[get_prev_fork_id(philo)]));
		philo->forks.prev = false;
	}
	if (philo->forks.next)
	{
		pthread_mutex_unlock(&(philo->data->forks[get_next_fork_id(philo)]));
		philo->forks.next = false;
	}
}

void	philo_sleep(t_philo *philo)
{
	philo_wait(philo);
}

void	philo_think(t_philo *philo)
{
	int	prev_fork_id;
	int	next_fork_id;

	prev_fork_id = get_prev_fork_id(philo);
	next_fork_id = get_next_fork_id(philo);
	philo_wait(philo);
	if (philo->id % 2)
	{
		take_fork(philo, prev_fork_id, &philo->forks.prev);
		if (prev_fork_id != next_fork_id)
			take_fork(philo, next_fork_id, &philo->forks.next);
	}
	else
	{
		take_fork(philo, next_fork_id, &philo->forks.next);
		if (prev_fork_id != next_fork_id)
			take_fork(philo, prev_fork_id, &philo->forks.prev);
	}
}

void	act(t_philo *philo)
{
	t_state	state;

	print_state(philo);
	state = get_state(philo);
	if (state == sleeping)
		philo_sleep(philo);
	else if (state == thinking)
		philo_think(philo);
	else if (state == eating)
		philo_eat(philo);
}
