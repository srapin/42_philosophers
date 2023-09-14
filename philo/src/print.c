/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 02:12:19 by srapin            #+#    #+#             */
/*   Updated: 2023/09/14 22:50:40 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_mess(t_philo *p, t_state state, char *mess)
{
	long long	rel_time;
	static bool	somebody_died;

	pthread_mutex_lock(&(p->data->can_write));
	p->just_took_a_fork = false;
	rel_time = get_relativ_ms_time(p->data);
	if (!somebody_died && mess && (!check_end(p->data) || state == died))
		printf("%lld %d %s\n", rel_time, get_philo_id(p), mess);
	if (state == died)
		somebody_died = true;
	if (state == eating)
		update_last_meal(p, rel_time);
	pthread_mutex_unlock(&(p->data->can_write));
}

void	print_state(t_philo *p)
{
	char	*mess;
	t_state	state;

	mess = NULL;
	state = get_state(p);
	if (state == eating && p->forks.prev && p->forks.next)
		mess = "is eating";
	else if (state == eating)
		return ;
	else if (state == died)
		mess = "died";
	else if (p->just_took_a_fork)
		mess = "has taken a fork";
	else if (state == sleeping)
		mess = "is sleeping";
	else if (state == thinking && get_last_meal(p) >= 0)
		mess = "is thinking";
	print_mess(p, state, mess);
}
