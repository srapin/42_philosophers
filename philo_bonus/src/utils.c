/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:10:21 by srapin            #+#    #+#             */
/*   Updated: 2023/09/15 00:03:06 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	set_state(t_philo *philo, t_state s)
{
	sem_wait(philo->state_access);
	philo->state = s;
	sem_post(philo->state_access);
}

void	update_has_already_eaten(t_philo *philo)
{
	philo->has_already_eaten++;
	if (philo->has_already_eaten
		== philo->data->number_of_times_each_philosopher_must_eat
		&& max_meals_specified(philo->data))
	{
		sem_post(philo->data->eat_enough);
	}
}

void	update_last_meal(t_philo *philo, long long rel_time)
{
	sem_wait(philo->last_meal_access);
	philo->last_meal = rel_time;
	sem_post(philo->last_meal_access);
}

bool	max_meals_specified(t_data *data)
{
	return (data->number_of_times_each_philosopher_must_eat > -1);
}

void	unlink_sem(void)
{
	sem_unlink("forks");
	sem_unlink("write_access");
	sem_unlink("end");
	sem_unlink("print_end");
	sem_unlink("eat_enough");
}
