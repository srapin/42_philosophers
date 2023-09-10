/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mutex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 21:05:48 by srapin            #+#    #+#             */
/*   Updated: 2023/09/10 21:08:34 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_state	get_state(t_philo *philo)
{
	t_state	s;

	pthread_mutex_lock(&philo->state_access);
	s = philo->state;
	pthread_mutex_unlock(&philo->state_access);
	return (s);
}

int	get_has_already_eaten(t_philo *philo)
{
	int	has_already_eaten;

	pthread_mutex_lock(&philo->has_already_eaten_access);
	has_already_eaten = philo->has_already_eaten;
	pthread_mutex_unlock(&philo->has_already_eaten_access);
	return (has_already_eaten);
}

bool	check_end(t_data *data)
{
	bool	end;

	pthread_mutex_lock(&data->end_access);
	end = data->end;
	pthread_mutex_unlock(&data->end_access);
	return (end);
}

long long	get_last_meal(t_philo *philo)
{
	long long	lm;

	pthread_mutex_lock(&philo->last_meal_access);
	lm = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_access);
	return (lm);
}

void	take_fork(t_philo *philo, int fork_id, bool *flag)
{
	pthread_mutex_lock(&(philo->data->forks[fork_id]));
	philo->just_took_a_fork = true;
	*flag = true;
	print_state(philo);
}
