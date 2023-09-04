/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_getter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:44:45 by srapin            #+#    #+#             */
/*   Updated: 2023/09/04 18:57:46 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/philo.h"


int get_next_neighbours_id(t_philo *philo)
{
	if (philo->id == philo->data->number_of_philosophers - 1)
		return 0; 
	return philo->id + 1;
}

int get_prev_neighbours_id(t_philo *philo)
{
	if (philo->id == 0)
		return philo->data->number_of_philosophers - 1;
	return philo->id - 1;
}


int get_next_fork_id(t_philo *philo)
{
	if (philo->id == philo->data->number_of_philosophers - 1)
		return 0;
	return philo->id;
}

int get_prev_fork_id(t_philo *philo)
{
	
	if (philo->id == 0)
		return philo->data->number_of_philosophers - 1;
	return philo->id - 1;
}

int get_philo_id(t_philo *philo)
{
	return philo->id + 1;
}