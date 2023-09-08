/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 03:37:33 by srapin            #+#    #+#             */
/*   Updated: 2023/04/28 02:53:28by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"



void init_forks(t_data *data)
{
	int i;
	i = 0;
	data->forks = malloc(data->number_of_philosophers  * sizeof(pthread_mutex_t));
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&(data->forks[i]) ,NULL);
		i++;
	}

}

void	set_param(int ac, char **av, t_data *data)
{
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->end = false;
	if (ac == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
}

void init_one_philo_mutexes(t_philo *philo)
{
	pthread_mutex_init(&(philo->state_access), NULL);
	pthread_mutex_init(&(philo->last_meal_access), NULL);
}

void init_philos_mutexes(t_data *data)
{
	int i = 0;

	while (i < data->number_of_philosophers)
	{
		init_one_philo_mutexes(&(data->philosophers[i]));
		i++;
	}

}

void init_mutexes(t_data *data)
{
	init_forks(data);
	init_philos_mutexes(data);
	pthread_mutex_init(&(data->can_write), NULL);
	pthread_mutex_init(&(data->starter_m), NULL);
}

void init_philo(t_data * data, t_philo *philo, int i)
{
	philo->id = i;
	philo->has_already_eaten = 0;
	philo->just_took_a_fork = false;
	philo->forks.prev = false;
	philo->forks.next = false;
	philo->state = thinking;
	philo->data = data;
	philo->last_meal = 0;
}

void init_philos(t_data *data)
{
	int i = 0;
	data->philosophers = malloc((data->number_of_philosophers) * sizeof(t_philo));
	while (i < data->number_of_philosophers)
	{

		init_philo(data, &(data->philosophers[i]), i);
		i++;
	}
}

void init_data(int ac, char **av, t_data *data)
{
	// int i; 
	
	set_param(ac, av, data);
	init_philos(data);
	init_mutexes(data);
}
