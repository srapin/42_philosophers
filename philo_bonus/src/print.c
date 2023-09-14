/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:30:53 by srapin            #+#    #+#             */
/*   Updated: 2023/09/14 23:35:16 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_state(t_philo *p)
{
	t_state		state;
	char		*mess;
	long long	rel_time;

	mess = NULL;
	state = p->state;
	if (state == eating && p->fork_n == 2)
		mess = "is eating";
	else if (state == sleeping)
		mess = "is sleeping";
	else if (state == thinking)
		mess = "is thinking";
	else
		return ;
	if (p->just_took_a_fork)
		mess = "has taken a fork";
	sem_wait(p->data->write_access);
	rel_time = get_relativ_ms_time(p->data);
	if (mess && !check_end() && !check_print_end())
		printf("%lld %d %s\n", rel_time, get_philo_id(p), mess);
	if (state == eating)
		update_last_meal(p, rel_time);
	p->just_took_a_fork = false;
	sem_post(p->data->write_access);
}
