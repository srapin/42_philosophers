/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:23:25 by srapin            #+#    #+#             */
/*   Updated: 2023/09/14 23:28:32 by srapin           ###   ########.fr       */
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
	sem_close(data->forks);
	sem_close(data->end);
	sem_close(data->write_access);
	sem_close(data->print_end);
	sem_close(data->eat_enough);
}

void	monitor_exit(t_data *data, pid_t *pids)
{
	wait_philos(data, pids);
	free(pids);
	close_data_sem(data);
	unlink_sem();
}
