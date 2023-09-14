/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:26:36 by srapin            #+#    #+#             */
/*   Updated: 2023/09/14 23:34:52 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	launch_philos(t_data *data, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pids[i] = fork();
		if (!pids[i])
		{
			free(pids);
			philosophe_routine(data, i);
		}
		i++;
	}
}

void	launch_meals_check(t_data *data, pid_t *pids)
{
	pids[data->number_of_philosophers] = fork();
	if (!pids[data->number_of_philosophers])
	{
		free(pids);
		eat_enough_checker_routine(data);
	}
}

pid_t	*lets_gow(t_data *data)
{
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * data->number_of_philosophers + 1);
	if (!pids)
		return (NULL);
	data->start = get_ms_time();
	launch_philos(data, pids);
	launch_meals_check(data, pids);
	return (pids);
}
