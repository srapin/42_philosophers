/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 00:35:34 by srapin            #+#    #+#             */
/*   Updated: 2023/09/04 18:13:28 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void philo_eat(t_philo * philo)
{
	if (!philo->forks.prev || !philo->forks.next)
	{
		error_occured(eat_whit_not_enough_forks, philo);
		//return;
	}
	sleep(philo->data->time_to_eat * 0.01);
	pthread_mutex_unlock(&(philo->data->forks[get_prev_fork_id(philo)]));
	pthread_mutex_unlock(&(philo->data->forks[get_next_fork_id(philo)]));
	philo->forks.prev = false;
	philo->forks.next = false;

	//wait tine to eat sec
}

void philo_sleep(t_philo * philo)
{
	sleep(philo->data->time_to_sleep * 0.01);
	//wait tine for sleep sec 
}

void philo_think(t_philo * philo)
{
	pthread_mutex_lock(&(philo->data->forks[get_prev_fork_id(philo)]));
	philo->just_took_a_fork = true;
	philo->forks.prev = true;
	print_state(philo);
	pthread_mutex_lock(&(philo->data->forks[get_next_fork_id(philo)]));
	philo->just_took_a_fork = true;
	philo->forks.next = true;
	print_state(philo);
	philo->just_took_a_fork = false;
	if (!philo->forks.prev || !philo->forks.next)
	{
		error_occured(eat_whit_not_enough_forks, philo);
		return;
	}
	//waiting for forks	
	//check death while waiting
}



void act(t_philo *philo)
{
	print_state(philo);
	if (philo->state == sleeping)
		philo_sleep(philo);
	else if (philo->state == thinking)
		philo_think(philo);
	else if (philo->state == eating)
		philo_eat(philo);

}

void * philosophe(void *args)
{
	t_philo *p = args;
	// printf("heyyyy i m philo %d\n", p->i);
	// print_state(p);
	while(is_alive(p))
	{
		act(p);
		change_state(p);
	}
	//print_state(p);
	return(0);
}