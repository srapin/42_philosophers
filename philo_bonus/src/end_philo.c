/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 22:56:58 by srapin            #+#    #+#             */
/*   Updated: 2023/09/18 20:59:32 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	close_philo_sem(t_philo *philo)
{
	(void)	philo;
	// sem_close(philo->last_meal_access);
	// sem_close(philo->state_access);
	// sem_close(philo->data->forks);
	// sem_close(philo->data->end_access);
	// sem_close(philo->data->eat_enough);
	// sem_close(philo->data->print_end_access);
	// if (philo->data->end)
	// 	sem_close(philo->data->end);
	// if (philo->data->print_end)
	// 	sem_close(philo->data->print_end);
	// sem_unlink("last_meal_access");
	// sem_unlink("state_access");
}

void	philo_wait_death(t_philo *philo)
{
	usleep((philo->data->time_to_die + philo->last_meal
				- get_relativ_ms_time(philo->data) + 1) * 1000);
}

void	philo_died(t_philo *philo)
{
	set_end(philo->data, philo->id);
	// set_print_end(philo->data);
	return ;
}

void	philo_exit(t_philo *philo)
{
	while (philo->fork_n)
		drop_fork(philo);
	pthread_join(philo->monitor_id, NULL);
	// close_philo_sem(philo);
}
