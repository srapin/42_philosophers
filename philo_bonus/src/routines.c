/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:31:33 by srapin            #+#    #+#             */
/*   Updated: 2023/09/15 00:04:48 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philosophe_routine(t_data *data, int i)
{
	t_philo	philo;

	init_philo(&philo, data, i);
	while (!check_end())
	{
		act(&philo);
		change_state(&philo);
	}
	philo_exit(&philo);
	exit(0);
}

void	eat_enough_checker_routine(t_data *data)
{
	int	i;

	i = 0;
	if (max_meals_specified(data))
	{
		while (i < data->number_of_philosophers)
		{
			sem_wait(data->eat_enough);
			i++;
		}
		set_end(data);
	}
	exit(0);
}

bool	still_alive(t_philo *philo)
{
	bool	is_alive;

	is_alive = (get_relativ_ms_time(philo->data)
			- get_last_meal(philo) <= philo->data->time_to_die);
	if (!is_alive)
		philo_died(philo);
	return (is_alive && get_state(philo) != died);
}

void	*death_checker_routine(void *args)
{
	t_philo	*philo;

	philo = args;
	while (!check_end())
	{
		still_alive(philo);
		usleep(500);
	}
	return (NULL);
}
