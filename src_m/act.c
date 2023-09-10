/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 00:35:34 by srapin            #+#    #+#             */
/*   Updated: 2023/09/10 19:25:19 by srapin           ###   ########.fr       */
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
		if (get_state(philo) == died)
			return ;
		usleep(sleep_base);
	}
}

void philo_eat(t_philo * philo)
{
	ft_sleep(philo);
	if (philo->forks.prev &&philo->forks.next)
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
	//todo
}

void philo_sleep(t_philo * philo)
{
	ft_sleep(philo);
}


void take_fork(t_philo *philo, int fork_id, bool *flag)
{
	pthread_mutex_lock(&(philo->data->forks[fork_id]));
	philo->just_took_a_fork = true;
	*flag = true;
	print_state(philo);
}

void philo_think(t_philo * philo)
{
	int prev_fork_id = get_prev_fork_id(philo);
	int next_fork_id =get_next_fork_id(philo) ;
	ft_sleep(philo);

	// pthread_mutex_lock(&philo->data->can_write);
	// printf(philo)
	// pthread_mutex_unlock(&philo->data->can_write);
	
	
	if (philo->id % 2)
	{
		take_fork(philo, prev_fork_id, &philo->forks.prev);
		if (prev_fork_id == next_fork_id) //seulement 1 philo
			return;
		take_fork(philo, next_fork_id,&philo->forks.next);
	}
	else
	{
		take_fork(philo, next_fork_id,&philo->forks.next);
		if (prev_fork_id == next_fork_id) //seulement 1 philo
			return;
		take_fork(philo, prev_fork_id, &philo->forks.prev);
		
	}
	// if (prev_fork_id == next_fork_id) //seulement 1 philo
		// return;

}



void act(t_philo *philo)
{
	print_state(philo);
	t_state state = get_state(philo);
	if (state == sleeping)
		philo_sleep(philo);
	else if (state == thinking)
		philo_think(philo);
	else if (state == eating)
		philo_eat(philo);
}