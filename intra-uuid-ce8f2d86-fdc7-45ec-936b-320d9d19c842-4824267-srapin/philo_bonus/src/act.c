/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:21:34 by srapin            #+#    #+#             */
/*   Updated: 2023/09/18 19:29:27 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philo_wait(t_philo *philo)
{
	long long	task_time;
	int			sleep_base;
	long long	target;

	task_time = time_for_task(philo);
	sleep_base = 500;
	target = get_relativ_ms_time(philo->data) + task_time;
	while (get_relativ_ms_time(philo->data) < target)
	{
		usleep(sleep_base);
		if (check_end(philo->data, philo->id))
			return ;
	}
}

void	philo_eat(t_philo *philo)
{
	while (philo->fork_n < 2)
		philo_wait_death(philo);
	philo_wait(philo);
	if (philo->fork_n == 2)
	{
		update_has_already_eaten(philo);
	}
	drop_fork(philo);
	drop_fork(philo);
}

void	philo_sleep(t_philo *philo)
{
	philo_wait(philo);
}

void	philo_think(t_philo *philo)
{
	philo_wait(philo);
	take_fork(philo);
	if (philo->data->number_of_philosophers > 1)
		take_fork(philo);
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
