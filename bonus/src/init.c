/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:25:40 by srapin            #+#    #+#             */
/*   Updated: 2023/09/12 01:55:44 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

void init_sem(t_data *data)
{
    sem_unlink("forks");
    sem_unlink("write_access");
    sem_unlink("end");
    sem_unlink("eat_enough");
    data->forks = sem_open("forks", O_CREAT, 0644, data->number_of_philosophers);
    data->write_access = sem_open("write_access", O_CREAT);
    data->end = sem_open("end", O_CREAT, 0644, 0);
    if (number_of_times_each_philosopher_must_eat_specified(data))
        data->eat_enough = sem_open("eat_enough", O_CREAT, 0644, data->number_of_times_each_philosopher_must_eat);
}

void	init(int ac, char **av, t_data *data)
{
	set_param(ac, av, data);
    init_sem(data);
	// init_mutexes(data); ->sem
}