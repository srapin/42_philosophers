/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 02:12:19 by srapin            #+#    #+#             */
/*   Updated: 2023/09/10 19:34:40 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"



bool is_alive(t_philo *philo)
{
	long long last_meal;

	last_meal = get_last_meal(philo);
	if (last_meal < 0)
		last_meal = 0;
	if (philo->data->time_to_die > get_relativ_ms_time(philo->data) - last_meal)
		return true;
	set_state(philo, died);
	// print_state(philo);
	return false; //exit?????
}

t_state get_state(t_philo *philo)
{
	t_state s;

	pthread_mutex_lock(&philo->state_access);
	s = philo->state;
	pthread_mutex_unlock(&philo->state_access);
	return s;
}

void set_state(t_philo *philo, t_state s)
{
	pthread_mutex_lock(&philo->state_access);
	philo->state = s;
	pthread_mutex_unlock(&philo->state_access);
}




void print_state(t_philo *p)
{
	char *mess;
	static bool	somebody_died;

	mess = NULL;
	t_state state = get_state(p);
	if (state == eating && p->forks.prev && p->forks.next)
		mess = "is eating";
	else if (state == eating)
		return;
	else if (state == died)
		mess = "died";
	else if (p->just_took_a_fork) //check 2 fourchette
		mess = "has taken a fork";
	else if (state == sleeping)
		mess = "is sleeping";
	else if (state == thinking)
		mess = "is thinking";
	pthread_mutex_lock(&(p->data->can_write));
	p->just_took_a_fork = false;
	long long rel_time = get_relativ_ms_time(p->data);
	if (!somebody_died)
		printf("%lld %d %s\n", rel_time ,get_philo_id(p), mess);
	if (state == died)
		somebody_died = true;
	if (state == eating)
		update_last_meal(p, rel_time);
	pthread_mutex_unlock(&(p->data->can_write));
}