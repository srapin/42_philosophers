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
	// print_state(p);
	while(!p->data->end)
	{
		// print_state(p);
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
	while (!data->end)
	{
		i = 0;
		while(i< data->number_of_philosophers)
		{
			current = data->philosophers + i;
			if (!is_alive(current))
			{

				data->end = true;
				break;
			}
			i++;
		}
	}
	return NULL;
}