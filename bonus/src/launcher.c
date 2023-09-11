/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:26:36 by srapin            #+#    #+#             */
/*   Updated: 2023/09/12 01:54:07 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// void	launch_number_of_meal_checker(t_data *data)
// {
// 	if (data->number_of_times_each_philosopher_must_eat > 0)
// 		pthread_create(&data->number_of_meal_checker_thread, NULL,
// 			number_of_meal_checker_routine, data);
// }

void launch_philos(t_data *data, pid_t *pids)
{
    int i=0;

    while (i < data->number_of_philosophers)
    {
        pids[i] = fork();
        if (!pids[i])
        {
            free(pids);
            philosophe_routine(data, i);
            // return NULL;
        }
        i++;
    }
    // return pids;
    
}

void launch_end_check(t_data *data, pid_t *pids)
{
    pids[data->number_of_philosophers] = fork();
    if (!pids[data->number_of_philosophers])
    {
        free(pids);
        end_check_routine(data);
        // return NULL;
    }
}

pid_t *	lets_gow(t_data *data)
{
    pid_t *pids;
    pids = malloc(sizeof(pid_t) * data->number_of_philosophers + 1);
    if (!pids)
        return NULL;
    data->start = get_ms_time();
	launch_philos(data, pids);
    launch_end_check(data, pids);
    // sleep(5);
    // philosophe_routine(data, 4);
    return pids;
	// launch_number_of_meal_checker(data);
	// supervisor_routine(data);
}