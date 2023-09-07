/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 02:12:19 by srapin            #+#    #+#             */
/*   Updated: 2023/09/07 19:56:13 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"



bool is_alive(t_philo *philo)
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	if (philo->data->time_to_die > time.tv_usec - philo->last_meal.tv_usec)
		return true;
	//todo
	philo->state = died;
	philo->data->end = true;
	print_state(philo);
	return false; //exit?????
}



void print_state(t_philo *p)
{
	char *mess;
	struct timeval time;
	static bool	somebody_died;

	mess = NULL;
	if (p->state == died)
		mess = "died";
	else if (p->just_took_a_fork) //check 2 fourchette
		mess = "has taken a fork";
	else if (p->state == eating)
		mess = "is eating";
	else if (p->state == sleeping)
		mess = "is sleeping";
	else if (p->state == thinking)
		mess = "is thinking";
	p->just_took_a_fork = false;
	pthread_mutex_lock(&(p->data->can_write));
	gettimeofday(&time ,NULL);
	if (!somebody_died)
		printf("%ld %d %s\n", (time.tv_usec * (10^(3)) - p->data->start * (10^(3))) ,get_philo_id(p), mess);
	if (p->state == died)
		somebody_died = true;
	pthread_mutex_unlock(&(p->data->can_write));
}