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

t_philo *init_philo(t_data *data, int i)
{
	t_philo *philo;

	philo = malloc(1 * sizeof(t_philo));
	philo->i = i;
	philo->has_already_eaten = 0;
	philo->just_took_a_fork = false;
	philo->forks.prev = false;
	philo->forks.prev = false;
	philo->state = thinking;
	philo->data = data;
	pthread_create(&(philo->thread), NULL, philosophe, philo); //todo
	gettimeofday(&(philo->last_meal), NULL);
	return philo;
}

void init_data(t_data *data)
{
	int i;
	
	i = 0;
	pthread_mutex_init(&(data->can_write), NULL);
	data->forks = malloc(data->number_of_philosophers * sizeof(pthread_mutex_t));
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&(data->forks[i]) ,NULL);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philosophers[i] = init_philo(data, i);	
		i++;
	}
	
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philosophers[i]->thread, NULL);
		//²data->philosophers[i] = init_philo(data, i);	
		i++;
	}
	
}

void destroy_data()
{

}