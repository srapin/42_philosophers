/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 21:00:55 by srapin            #+#    #+#             */
/*   Updated: 2023/09/10 21:01:42 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	drop_forks(t_philo *philo)
{
	if (philo->forks.prev)
	{
		pthread_mutex_unlock(&philo->data->forks[get_prev_fork_id(philo)]);
		philo->forks.prev = false;
	}
	if (philo->forks.next)
	{
		pthread_mutex_unlock(&philo->data->forks[get_next_fork_id(philo)]);
		philo->forks.next = false;
	}
}

void	*philosophe_routine(void *args)
{
	t_philo	*philo;

	philo = args;
	pthread_mutex_lock(&philo->data->starter_m);
	pthread_mutex_unlock(&philo->data->starter_m);
	while (!check_end(philo->data))
	{
		act(philo);
		change_state(philo);
	}
	print_state(philo);
	drop_forks(philo);
	return (NULL);
}

void	*number_of_meal_checker_routine(void *arg)
{
	t_data	*data;
	int		is_not_hungry_anymore;
	int		i;

	data = arg;
	while (!check_end(data))
	{
		is_not_hungry_anymore = 0;
		i = 0;
		while (i < data->number_of_philosophers)
		{
			if (get_has_already_eaten(data->philosophers
					+ i) >= data->number_of_times_each_philosopher_must_eat)
				is_not_hungry_anymore++;
			i++;
		}
		if (is_not_hungry_anymore == data->number_of_philosophers)
			update_end(data, true);
		usleep(500);
	}
	return (NULL);
}

bool	is_alive(t_philo *philo)
{
	long long	last_meal;

	last_meal = get_last_meal(philo);
	if (last_meal < 0)
		last_meal = 0;
	if (philo->data->time_to_die > get_relativ_ms_time(philo->data) - last_meal)
		return (true);
	set_state(philo, died);
	return (false);
}

void	*supervisor_routine(void *arg)
{
	t_data	*data;
	t_philo	*current;
	int		i;

	data = arg;
	while (!check_end(data))
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			current = data->philosophers + i;
			if (!is_alive(current))
			{
				update_end(data, true);
				break ;
			}
			i++;
		}
		usleep(500);
	}
	return (NULL);
}
