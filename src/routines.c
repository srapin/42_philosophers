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

void *philosophe_routine(void *args)
{
	t_philo *p = args;
	pthread_mutex_lock(&p->data->starter_m);
	pthread_mutex_unlock(&p->data->starter_m);
	
	while(!check_end(p->data))
	{
		act(p);
		change_state(p);
	}
	print_state(p);
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