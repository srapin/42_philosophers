/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:25:40 by srapin            #+#    #+#             */
/*   Updated: 2023/10/11 16:39:13 by srapin           ###   ########.fr       */
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
	philo->monitor_id = 0;
	if (max_meals_specified(philo->data))
		sem_wait(data->eat_enough);
	if (!philo->last_meal_access || !philo->state_access)
	{
		set_local_end(data, data->number_of_philosophers);
		printf("sem error\n");
		exit(1);
	}
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

void	init_sem_end_access(t_data *data)
{
	int		i;
	char	*name;

	i = 0;
	data->end_access = ft_calloc((data->number_of_philosophers + 1),
			sizeof(sem_t *));
	data->end = ft_calloc((data->number_of_philosophers + 1), sizeof(sem_t *));
	while (i < data->number_of_philosophers + 1 && data->end_access)
	{
		name = get_sem_end_access_name(i);
		sem_unlink(name);
		data->end_access[i] = sem_open(name, O_CREAT, 0644, 1);
		if (!data->end_access[i])
		{
			i = 0;
			break;
		}
		free(name);
		name = get_sem_end_name(i);
		sem_unlink(name);
		free(name);
		i++;
	}
	if (!data->end || i < 0)
	{
		close_data_sem(data);
		free(data->end);
		free(data->end_access);
		printf("sem or alloc error\n");
		exit(1);
	}
}

void	init_sem(t_data *data)
{
	unlink_sem();
	data->forks = sem_open("forks", O_CREAT, 0644,
			data->number_of_philosophers);
	data->write_access = sem_open("write_access", O_CREAT, 0644, 1);
	if (max_meals_specified(data))
		data->eat_enough = sem_open("eat_enough", O_CREAT, 0644,
				data->number_of_philosophers);
	if (!data->forks || !data->write_access || (max_meals_specified(data) && !data->eat_enough))
	{
		close_data_sem(data);
		printf("sem error\n");
		exit(1);
	}
	init_sem_end_access(data);
}

void	init(int ac, char **av, t_data *data)
{
	set_param(ac, av, data);
	init_sem(data);
}
