/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 02:12:19 by srapin            #+#    #+#             */
/*   Updated: 2023/04/28 02:23:03 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"



bool check_death(t_philo *philo)
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	if (philo->data->time_to_die < time.tv_usec - philo->last_meal.tv_usec)
		return false;
	//todo
	philo->state = died;
	print_state(philo);
	return true; //exit?????
}



void print_state(t_philo *p)
{
	char *mess;
	struct timeval time;
	
	if (p->just_took_a_fork) //check 2 fourchette
		mess = "has taken a fork";
	else if (p->state == died)
		mess = "died";
	else if (p->state == eating)
		mess = "is eating";
	else if (p->state == sleeping)
		mess = "is sleeping";
	else if (p->state == thinking)
		mess = "is thinking";
	// else if (p->state == thinking_whit_a_fork)
	// 	mess = "has taken a fork";
	p->just_took_a_fork = false;
	gettimeofday(&time ,NULL);
	printf("%ld %d %s", time.tv_usec ,get_philo_id(p), mess);
}