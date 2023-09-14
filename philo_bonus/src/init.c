/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:25:40 by srapin            #+#    #+#             */
/*   Updated: 2023/09/15 00:01:36 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_philo(t_philo *philo, t_data *data, int i)
{
	philo->id = i;
	philo->data = data;
	philo->state = thinking;
	philo->last_meal = -1;
	philo->just_took_a_fork = false;
	philo->fork_n = 0;
	philo->has_already_eaten = 0;
	philo->last_meal_access = sem_open("last_meal_access", O_CREAT, 0644, 1);
	philo->state_access = sem_open("state_access", O_CREAT, 0644, 1);
	if (max_meals_specified(philo->data))
		sem_wait(data->eat_enough);
	pthread_create(&(philo->monitor_id), NULL, death_checker_routine, philo);
}

void	set_param(int ac, char **av, t_data *data)
{
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
}

void	init_sem(t_data *data)
{
	unlink_sem();
	data->end = NULL;
	data->print_end = NULL;
	data->forks = sem_open("forks", O_CREAT, 0644,
			data->number_of_philosophers);
	data->write_access = sem_open("write_access", O_CREAT, 0644, 1);
	if (max_meals_specified(data))
		data->eat_enough = sem_open("eat_enough", O_CREAT, 0644,
				data->number_of_philosophers);
}

void	init(int ac, char **av, t_data *data)
{
	set_param(ac, av, data);
	init_sem(data);
}
