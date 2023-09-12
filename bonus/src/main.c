/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:27:27 by srapin            #+#    #+#             */
/*   Updated: 2023/09/13 00:48:57 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void kill_all_philos(t_data *data, pid_t *pids)
{
    int i = 0;
    while( i < data->number_of_philosophers)
    {
        kill(pids[i], SIGKILL);
        i++;
    }
}


int wait_philos(t_data *data, pid_t *pids)
{
    int i = 0;
    int status;
    int dead_philo = -1;
    
    while(i < data->number_of_philosophers)
    {
        
        waitpid(pids[i], &status, WNOHANG);
        if (WIFEXITED(status))
			if (WEXITSTATUS(status) == 1)
				dead_philo = i + 1;
        i++;
    }
    return dead_philo;
}

void print_end(t_data * data, int dead_philo)
{
    if (dead_philo < 0)
        return;
    sem_wait(data->write_access);
	// if (!some_philo_died(philo->data))
	printf("%lld %d died\n", get_relativ_ms_time(data), dead_philo);
    sem_post(data->write_access);
}
void monitor(t_data *data, pid_t *pids)
{
    int status;
    int checker_pid = pids[data->number_of_philosophers];
    pid_t waitpid(pid_t pid, int *status, int options);
    waitpid(checker_pid, NULL, 0);
    sleep(1);
    kill_all_philos(data, pids);
    sleep(1);
    print_end(data, wait_philos(data, pids));
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