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

// t_philo *init_philo(t_data *data, int i)
// {
// 	t_philo *philo;

// 	philo = malloc(1 * sizeof(t_philo));
// 	philo->id = i;
// 	philo->has_already_eaten = 0;
// 	philo->just_took_a_fork = false;
// 	philo->forks.prev = false;
// 	philo->forks.next = false;
// 	philo->state = thinking;
// 	philo->data = data;
// 	// gettimeofday(&(philo->last_meal), NULL);
// 	// pthread_create(&(philo->thread_id), NULL, philosophe_routine, philo); //todo
// 	return philo;
// }

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

void launch_philos(t_data *data)
{
	int i; 
	t_philo *current_philo;

	// data->philosophers = malloc(data->number_of_philosophers * sizeof(void *));
	i = 0;
	// philosophe_routine(data->philosophers[i]);
	while (i < data->number_of_philosophers)
	{
		// printf("\nlol %d \n", i);
		current_philo = data->philosophers[i];
		pthread_create(&(current_philo->thread_id), NULL, &philosophe_routine, current_philo);
		i++;
	}
}

void launch_supervisor(t_data *data)
{

}

bool	set_param(int ac, char **av, t_data *data)
{
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	return true;
}



void set_start_time(t_data *data)
{
	struct timeval t;
	int i = -1;

	gettimeofday(&t, NULL);
	data->start = t.tv_usec;
	while (i <= data->number_of_philosophers)
	{
		data->philosophers[i]->last_meal = t;
	}	
}

void lets_gow(t_data *data)
{
	launch_philos(data);
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
		init_one_philo_mutexes(data->philosophers[i]);
		i++;
	}

}

void init_mutexes(t_data *data)
{
	init_forks(data);
	init_philos_mutexes(data);
	pthread_mutex_init(&(data->can_write), NULL);
}



t_philo *create_philo(t_data *data, int i)
{
	t_philo *philo;

	philo = malloc(1 * sizeof(t_philo));
	philo->id = i;
	philo->has_already_eaten = 0;
	philo->just_took_a_fork = false;
	philo->forks.prev = false;
	philo->forks.next = false;
	philo->state = thinking;
	philo->data = data;
	// pthread_create(&(philo->thread), NULL, philosophe_routine, philo); //todo
	return philo;
}

void init_philos(t_data *data)
{
	int i = 0;
	data->philosophers = malloc(data->number_of_philosophers * sizeof(t_philo *));
	while (i < data->number_of_philosophers)
	{

		data->philosophers[i] = create_philo(data, i);
		// printf("\n philo %d creat\n", i);
		i++;
	}
}


void init_data(int ac, char **av, t_data *data)
{
	int i; 
	
	set_param(ac, av, data);
	init_philos(data);
	init_mutexes(data);
	// launch_philos(data);	

	//not sure about that
	// while (i < data->number_of_philosophers)
	// {
	// 	pthread_join(data->philosophers[i]->thread, NULL);
	// 	//²data->philosophers[i] = init_philo(data, i);	
	// 	i++;
	// }
	
}

void destroy_data()
{

}