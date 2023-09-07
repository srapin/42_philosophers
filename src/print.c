/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 02:12:19 by srapin            #+#    #+#             */
/*   Updated: 2023/09/07 21:16:41 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"



bool is_alive(t_philo *philo)
{
	if (philo->data->time_to_die > get_relativ_ms_time(philo->data) - get_last_meal(philo))
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
	long long rel_time = get_relativ_ms_time(p->data);
	if (!somebody_died)
		printf("%lld %d %s\n", rel_time ,get_philo_id(p), mess);
	if (p->state == died)
		somebody_died = true;
	pthread_mutex_unlock(&(p->data->can_write));
	if (p->state == eating)
		update_last_meal(p, rel_time);
}