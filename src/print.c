/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 02:12:19 by srapin            #+#    #+#             */
/*   Updated: 2023/04/27 03:39:42 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


void change_state(t_philo *p, t_state new_state)
{
	//if (new_state == p->state)
		
}

bool check_if_alive()
{
	return false;
}

int time_for_task(t_philo *p)
{
	
}

void print_state(t_philo *p, bool took_a_fork)
{
	char *mess;
	

	
	if (took_a_fork)
		mess = "has taken a fork";
	else if (p->state == died)
		mess = "died";
	else if (p->state == eating)
		mess = "is eating";
	else if (p->state == sleeping)
		mess = "is sleeping";
	else if (p->state == thinking)
		mess = "is thinking";
	printf("%d %d %s", gettimeofday(), p->id, mess);
}