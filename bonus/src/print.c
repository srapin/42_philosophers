/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:30:53 by srapin            #+#    #+#             */
/*   Updated: 2023/09/13 00:48:08 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_state(t_philo *p)
{
  t_state state = p->state;
  char *mess;
  long long rel_time;

  mess = NULL;
  if (state == eating)
    mess = "is eating";
	else if (state == sleeping)
		mess = "is sleeping";
	else if (state == thinking)
		mess = "is thinking";
  else
    return;
  if (p->just_took_a_fork)
    mess = "has taken a fork";
  p->just_took_a_fork = false;
  sem_wait(p->data->write_access);
  rel_time = get_relativ_ms_time(p->data);
	if (mess)
		printf("%lld %d %s\n", rel_time, get_philo_id(p), mess);
  if (state == eating)
    update_last_meal(p, rel_time);
  sem_post(p->data->write_access);
}