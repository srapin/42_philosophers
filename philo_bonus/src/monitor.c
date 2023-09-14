/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 23:12:50 by srapin            #+#    #+#             */
/*   Updated: 2023/09/14 23:32:41 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	monitor(t_data *data, pid_t *pids)
{
	int	checker_pid;

	checker_pid = pids[data->number_of_philosophers];
	waitpid(checker_pid, NULL, 0);
	while (!check_end())
		usleep(500);
	monitor_exit(data, pids);
}
