/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_getter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:44:45 by srapin            #+#    #+#             */
/*   Updated: 2023/04/28 00:50:10 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/philo.h"


int get_next_neighbours_id(t_philo *philo)
{
	if (philo->i == philo->data->number_of_philosophers - 1)
		return 0; 
	return philo->i + 1;
}

int get_prev_neighbours_id(t_philo *philo)
{
	if (philo->i == 0)
		return philo->data->number_of_philosophers - 1;
	return philo->i - 1;
}


int get_next_fork_id(t_philo *philo)
{
	if (philo->i == philo->data->number_of_philosophers - 1)
		return 0;
	return philo->i;
}

int get_prev_fork_id(t_philo *philo)
{
	
	if (philo->i == 0)
		return philo->data->number_of_philosophers - 1;
	return philo->i - 1;
}

int get_philo_id(t_philo *philo)
{
	return philo->i + 1;
}