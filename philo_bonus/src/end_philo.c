/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 22:56:58 by srapin            #+#    #+#             */
/*   Updated: 2023/10/11 16:25:48 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	close_philo_sem(t_philo *philo)
{
	int	i;

	if (max_meals_specified(philo->data))
		sem_close(philo->data->eat_enough);
	if (philo->last_meal_access)
		sem_close(philo->last_meal_access);
	if (philo->state_access)
		sem_close(philo->state_access);
	sem_close(philo->data->write_access);
	sem_close(philo->data->forks);
	i = 0;
	while (i <= philo->data->number_of_philosophers)
	{
		sem_close(philo->data->end_access[i]);
		i++;
	}
	sem_close(philo->data->end[philo->id]);
	if (philo->data->end[philo->data->number_of_philosophers])
		sem_close(philo->data->end[philo->data->number_of_philosophers]);
	sem_unlink("last_meal_access");
	sem_unlink("state_access");
}

void	philo_wait_death(t_philo *philo)
{
	usleep((philo->data->time_to_die + philo->last_meal
			- get_relativ_ms_time(philo->data) + 1) * 1000);
}

void	philo_died(t_philo *philo)
{
	set_local_end(philo->data, philo->id);
	return ;
}

void	philo_exit(t_philo *philo)
{
	sem_post(philo->data->eat_enough);
	pthread_join(philo->monitor_id, NULL);
	usleep(500);
	close_philo_sem(philo);
	free(philo->data->end);
	free(philo->data->end_access);
	exit(0);
}
