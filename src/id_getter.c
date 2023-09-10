/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_getter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:44:45 by srapin            #+#    #+#             */
/*   Updated: 2023/09/10 20:45:44 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	get_next_fork_id(t_philo *philo)
{
	int	fork;

	fork = philo->id + 1;
	if (fork > philo->data->number_of_philosophers - 1)
		return (0);
	return (fork);
}

int	get_prev_fork_id(t_philo *philo)
{
	return (philo->id);
}

int	get_philo_id(t_philo *philo)
{
	return (philo->id + 1);
}
