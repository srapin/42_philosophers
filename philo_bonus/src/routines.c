/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:31:33 by srapin            #+#    #+#             */
/*   Updated: 2023/10/11 16:11:56 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	philosophe_routine(t_data *data, int i)
{
	t_philo	philo;
	bool	flag;

	init_philo(&philo, data, i);
	while (get_ms_time() < data->start)
		usleep(100);
	while (!check_end(data, i))
	{
		act(&philo);
		change_state(&philo);
	}
	while (philo.fork_n)
		drop_fork(&philo);
	flag = false;
	while (!flag)
		flag = update_has_already_eaten(&philo);
	philo_exit(&philo);
	exit(0);
}

void	eat_enough_checker_routine(t_data *data)
{
	int	i;

	i = 0;
	while (get_ms_time() < data->start + data->time_to_eat)
		usleep(100);
	if (max_meals_specified(data))
	{
		while (i < data->number_of_philosophers) //&& !check_end(data, data->number_of_philosophers))
		{
			sem_wait(data->eat_enough);
			i++;
		}
		set_local_end(data, data->number_of_philosophers);
		if (data->end[data->number_of_philosophers])
			sem_close(data->end[data->number_of_philosophers]);
	}
	else
	{
		while (!check_end(data, data->number_of_philosophers))
			usleep(500);
	}
	close_data_sem(data);
	free(data->end);
	free(data->end_access);
	exit(0);
}

bool	still_alive(t_philo *philo)
{
	bool	is_alive;

	is_alive = (get_relativ_ms_time(philo->data)
			- get_last_meal(philo) <= philo->data->time_to_die);
	if (!is_alive)
	{
		philo_died(philo);
		sem_wait(philo->data->end_access[philo->id]);
		if (philo->data->end[philo->id])
		{
			sem_close(philo->data->end[philo->id]);
			philo->data->end[philo->id] = NULL;
		}
		sem_post(philo->data->end_access[philo->id]);
	}
	return (is_alive && get_state(philo) != died);
}

void	*death_checker_routine(void *args)
{
	t_philo	*philo;

	philo = args;
	while (get_ms_time() < philo->data->start + philo->data->time_to_die / 2)
		usleep(100);
	while (!check_end(philo->data, philo->id) && still_alive(philo))
	{
		usleep(500);
	}
	return (NULL);
}
