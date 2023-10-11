/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:23:25 by srapin            #+#    #+#             */
/*   Updated: 2023/10/11 16:40:43 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	wait_philos(t_data *data, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		waitpid(pids[i], NULL, WNOHANG);
		i++;
	}
}

void	close_data_sem(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks)
		sem_close(data->forks);
	if (max_meals_specified(data) && data->eat_enough)
		sem_close(data->eat_enough);
	if (data->write_access)
		sem_close(data->write_access);
	while (i <= data->number_of_philosophers && data->end_access)
	{
		if (data->end_access[i])
			sem_close(data->end_access[i]);
		else
			break;
		i++;
	}
}

void	monitor_exit(t_data *data, pid_t *pids)
{
	wait_philos(data, pids);
	free(pids);
	close_data_sem(data);
	unlink_sem();
	free(data->end);
	free(data->end_access);
}
