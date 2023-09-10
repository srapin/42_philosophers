/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:11:23 by srapin            #+#    #+#             */
/*   Updated: 2023/09/05 19:13:36by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void drop_forks(t_philo * philo)
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

void *philosophe_routine(void *args)
{
	t_philo *philo = args;
	pthread_mutex_lock(&philo->data->starter_m);
	pthread_mutex_unlock(&philo->data->starter_m);
	
	while(!check_end(philo->data))
	{
		act(philo);
		change_state(philo);
	}
	print_state(philo);
	drop_forks(philo);
	// pthread_mutex_lock(&p->data->can_write);
	// printf("philo nb %d exit\n", p->id);
	// pthread_mutex_unlock(&p->data->can_write);

	return NULL;
}

void *supervisor_routine(void *arg)
{
	t_data *data;
	t_philo *current;

	int		i;
	data = arg;
	while (!check_end(data))
	{
		i = 0;
		while(i< data->number_of_philosophers)
		{
			current = data->philosophers + i;
			if (!is_alive(current))
			{
				update_end(data, true);
				break;
			}
			i++;
		}
		usleep(500); //todel
	}
	return NULL;
}