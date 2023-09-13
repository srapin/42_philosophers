/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:31:33 by srapin            #+#    #+#             */
/*   Updated: 2023/09/14 00:46:08 by srapin           ###   ########.fr       */
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
    sem_wait(data->end);
    if (number_of_times_each_philosopher_must_eat_specified(philo->data))
        sem_wait(data->eat_enough);
}

void	philosophe_routine(t_data *data, int i)
{
	t_philo	philo;
    init_philo(&philo, data, i);
	// philo = args;
	// pthread_mutex_lock(&philo->data->starter_m);
	// pthread_mutex_unlock(&philo->data->starter_m);
	while (still_alive(&philo))
	{
    // printf("I'm philo before act%d\n", philo.id);
		act(&philo);
    // printf("I'm philo after act%d\n", philo.id);
		change_state(&philo);
	}
    printf("end of routine for phil %d\n", get_philo_id(&philo));
    exit(0);
	// print_state(philo);
	// drop_forks(philo);
	// return (NULL);
}

void	eat_enough_checker_routine(t_data *data)
{
    int i = 0;
    
    if (number_of_times_each_philosopher_must_eat_specified(data))
    {
        // printf("------------lolfrom num meal\n");
        while(i < data->number_of_philosophers)
        {
        sem_wait(data->eat_enough);
        // printf("someone eat enough%lld\n", get_relativ_ms_time(data));
        i++;    
        }
        // printf("everybody eat enough %lld\n", get_relativ_ms_time(data));
        sem_post(data->end);
    }
    exit(0);
}

void end_check_routine(t_data *data)
{
    int pid;
    usleep(2000);
    if (number_of_times_each_philosopher_must_eat_specified(data))
    {
        pid = fork();
        if (!pid)
            eat_enough_checker_routine(data);
    }
    sem_wait(data->end);
    if (number_of_times_each_philosopher_must_eat_specified(data))
    {
        kill(pid, SIGKILL);
        waitpid(pid, NULL, 0);
    }
    // printf("end got info %lld\n", get_relativ_ms_time(data));
    exit(0);
}