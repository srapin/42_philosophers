/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:23:25 by srapin            #+#    #+#             */
/*   Updated: 2023/09/20 15:03:22 by srapin           ###   ########.fr       */
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
	// (void) data;
	int i;
	
	i = 0;
	sem_close(data->forks);
	if (max_meals_specified(data))
		sem_close(data->eat_enough);
	sem_close(data->write_access);
	while (i <= data->number_of_philosophers)
	{
		if (data->end[i])
			sem_close(data->end[i]);
		sem_close(data->end_access[i]);
		i++;
	}
}

void	monitor_exit(t_data *data, pid_t *pids)
{
	// printf("end monitor exit\n");
	wait_philos(data, pids);
	free(pids);
	close_data_sem(data);
	unlink_sem();
	free(data->end);
	free(data->end_access);
}
