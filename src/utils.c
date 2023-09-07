/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:44:45 by srapin            #+#    #+#             */
/*   Updated: 2023/09/07 21:16:00 by srapin           ###   ########.fr       */
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