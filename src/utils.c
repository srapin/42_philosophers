/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:44:45 by srapin            #+#    #+#             */
/*   Updated: 2023/09/09 21:12:27 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/philo.h"

long long get_last_meal(t_philo *philo)
{
	long long lm;
	
	pthread_mutex_lock(&philo->last_meal_access);
	lm = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_access);
	return lm;
}

bool check_end(t_data *data)
{
	bool end;
	pthread_mutex_lock(&data->end_access);
	end = data->end;
	pthread_mutex_unlock(&data->end_access);
	return end;
}

void update_end(t_data *data, bool value)
{
	pthread_mutex_lock(&data->end_access);
	data->end = value;
	pthread_mutex_unlock(&data->end_access);
}

int get_has_already_eaten(t_philo *philo)
{
	int has_already_eaten;
	
	pthread_mutex_lock(&philo->has_already_eaten_access);
	has_already_eaten = philo->has_already_eaten;
	pthread_mutex_unlock(&philo->has_already_eaten_access);
	return has_already_eaten;
}

void update_has_already_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->has_already_eaten_access);
	philo->has_already_eaten++;
	pthread_mutex_unlock(&philo->has_already_eaten_access);
}

