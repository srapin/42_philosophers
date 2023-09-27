/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_getter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 23:17:54 by srapin            #+#    #+#             */
/*   Updated: 2023/09/27 19:17:50 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_state	get_state(t_philo *philo)
{
	t_state	s;

	sem_wait(philo->state_access);
	s = philo->state;
	sem_post(philo->state_access);
	return (s);
}

int	get_has_already_eaten(t_philo *philo)
{
	int	has_already_eaten;

	has_already_eaten = philo->has_already_eaten;
	return (has_already_eaten);
}

long long	get_last_meal(t_philo *philo)
{
	long long	lm;

	sem_wait(philo->last_meal_access);
	lm = philo->last_meal;
	sem_post(philo->last_meal_access);
	return (lm);
}
