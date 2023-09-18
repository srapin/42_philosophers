/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:25:40 by srapin            #+#    #+#             */
/*   Updated: 2023/09/18 21:22:44 by srapin           ###   ########.fr       */
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


char *get_sem_end_access_name(int i)
{
	static char *base = "end_access_";
	char *number;
	char *name;
	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin(base, number);
	free(number);
	return name;
}

char *get_sem_end_name(int i)
{
	static char *base = "end_";
	char *number;
	char *name;
	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin(base, number);
	free(number);
	return name;
}

void init_sem_end_access(t_data *data)
{
	
	int i = 0;
	char *name;
	data->end_access = ft_calloc((data->number_of_philosophers + 1), sizeof(sem_t*));
	if (!data->end_access)
		data->error = alloc_error;
	data->end = ft_calloc((data->number_of_philosophers + 1), sizeof(sem_t*));
	if (!data->end)
	{
		free(data->end_access);
		data->error = alloc_error;
	}
	while (i < data->number_of_philosophers + 1 && !data->error)
	{
		name = get_sem_end_access_name(i);
		if (!name)
		{
			data->error = alloc_error;
			break;
		}
		sem_unlink(name);
		data->end_access[i] = sem_open(name, O_CREAT, 0644, 1);
		if (data->end_access[i] == SEM_FAILED)
			data->error = sem_error;
		free(name);
		name = get_sem_end_name(i);
		if (!name)
		{
			data->error = alloc_error;
			break;
		}
		sem_unlink(name);
		free(name);
		i++;
	}
}

void	check_sem(t_data *data)
{
	if (data->error)
		return;
	if (data->end == SEM_FAILED || data->forks == SEM_FAILED || (max_meals_specified(data) && data->eat_enough == SEM_FAILED))
		data->error = sem_error;
}

void	init_sem(t_data *data)
{
	unlink_sem();
	data->forks = sem_open("forks", O_CREAT, 0644,
			data->number_of_philosophers);
	init_sem_end_access(data);
	if (max_meals_specified(data))
		data->eat_enough = sem_open("eat_enough", O_CREAT, 0644,
				data->number_of_philosophers);
	check_sem(data);
	
}

void	init(int ac, char **av, t_data *data)
{
	data->error = none;
	set_param(ac, av, data);
	init_sem(data);
		
}
