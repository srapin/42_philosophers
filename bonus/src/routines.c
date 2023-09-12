/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:31:33 by srapin            #+#    #+#             */
/*   Updated: 2023/09/13 00:53:19 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void init_philo(t_philo *philo, t_data *data, int i)
{
    philo->id = i;
    philo->data = data;
    philo->state = thinking;
    philo->last_meal = -1;
    philo->just_took_a_fork = false;
    philo->fork_n = 0;
    philo->has_already_eaten = 0;
}

void	philosophe_routine(t_data *data, int i)
{
	t_philo	philo;
    init_philo(&philo, data, i);
    // printf("I'm philo %d\n", philo.id);
	// philo = args;
	// pthread_mutex_lock(&philo->data->starter_m);
	// pthread_mutex_unlock(&philo->data->starter_m);
	while (still_alive(&philo))
	{
		act(&philo);
		change_state(&philo);
	}
    exit(0);
	// print_state(philo);
	// drop_forks(philo);
	// return (NULL);
}

void	eat_enough_checker_routine(t_data *data)
{
    if (number_of_times_each_philosopher_must_eat_specified(data))
    {
        sem_wait(data->eat_enough);
        sem_post(data->end);
    }
    exit(0);
}

void end_check_routine(t_data *data)
{
    int pid;
    if (number_of_times_each_philosopher_must_eat_specified(data))
    {
        pid = fork();
        if (!pid)
            eat_enough_checker_routine(data);
    }
    // printf("------------lolfrom checkr\n");
    sem_wait(data->end);
    // printf("lolfrom checkr\n");
    if (number_of_times_each_philosopher_must_eat_specified(data))
        kill(pid, SIGKILL);
    exit(0);
}