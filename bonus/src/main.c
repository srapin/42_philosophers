/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:27:27 by srapin            #+#    #+#             */
/*   Updated: 2023/09/12 01:56:39 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void kill_all_philos(t_data *data, pid_t *pids)
{
    int i = 0;
    while( i < data->number_of_philosophers)
    {
        kill(pids[i], 130);
        i++;
    }
}

void monitor(t_data *data, pid_t *pids)
{
    int status;
    int checker_pid = pids[data->number_of_philosophers];
    pid_t waitpid(pid_t pid, int *status, int options);
    waitpid(checker_pid, NULL, 0);
    kill_all_philos(data, pids);
    printf("lol\n");
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!check_args(ac, av))
		return (error_occured(parse_error, false, NULL));
	init(ac, av, &data);
	pid_t * pids = lets_gow(&data);
    if (!pids)
        return (0);
    monitor(&data,pids );
	// ft_exit(&data);
}