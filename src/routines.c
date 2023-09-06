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
	printf("heyyyy i m philo %d\n", p->id);
	// print_state(p);
	// while(is_alive(p))
	// {
	// 	act(p);
	// 	change_state(p);
	// }
	// //print_state(p);
	// return(0);
}


void *supervisor_routine(void *arg)
{
	t_data *data;
	bool	end;
	int		i = 0;
	data = arg;
	while(i ++ < data->number_of_philosophers)
	{
		while (!end)
		{
		
		}
	}
}