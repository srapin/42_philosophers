/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:59:44 by srapin            #+#    #+#             */
/*   Updated: 2023/04/27 02:05:48 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int		error_occured(t_error e, t_philo *p)
{
	char *mess;
	
	if (e == none)
		mess = "error occured but wich one";
	if (e == parse_error)
		mess = "parse error";
	if (e == eat_whit_not_enough_forks)
		mess = "philo try to eat but has not enough forks";
	if (p)
	{
		pthread_mutex_lock(&(p->data->can_write));
		printf("%s by %d \n", mess, get_philo_id(p));
		pthread_mutex_unlock(&(p->data->can_write));
	}
	else
	{
		printf("%s\n", mess);
	}
	return e;
}