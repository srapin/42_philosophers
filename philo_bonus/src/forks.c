/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 22:53:12 by srapin            #+#    #+#             */
/*   Updated: 2023/09/15 00:48:13 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	take_fork(t_philo *philo)
{
	sem_wait(philo->data->forks);
	philo->fork_n++;
	if (check_end(philo->data))
		return ;
	philo->just_took_a_fork = true;
	print_state(philo);
}

void	drop_fork(t_philo *philo)
{
	if (philo->fork_n <= 0)
		return ;
	sem_post(philo->data->forks);
	philo->fork_n--;
}
