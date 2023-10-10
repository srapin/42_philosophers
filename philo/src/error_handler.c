/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:59:44 by srapin            #+#    #+#             */
/*   Updated: 2023/10/10 17:23:14 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	error_occured(t_error e, bool need_to_ask, pthread_mutex_t *can_write)
{
	char	*mess;

	mess = "unknown error";
	if (e == parse_error)
		mess = "usage : ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n\
All args must be positive integers";
	if (need_to_ask)
		pthread_mutex_lock(can_write);
	printf("%s\n", mess);
	if (need_to_ask)
		pthread_mutex_unlock(can_write);
	return (1);
}
