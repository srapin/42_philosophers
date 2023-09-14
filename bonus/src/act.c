/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:21:34 by srapin            #+#    #+#             */
/*   Updated: 2023/09/14 02:26:50 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
void    drop_fork(t_philo *philo)
{
	// printf("droped fork\n");
	if (philo->fork_n <= 0)
		return;
    sem_post(philo->data->forks);
    philo->fork_n--;
    
}
void philo_died(t_philo *philo)
{
    while(philo->fork_n)
	{

        drop_fork(philo);
	}

    set_state(philo, died);
    sem_wait(philo->data->write_access);
	printf("%lld %d died\n", get_relativ_ms_time(philo->data), get_philo_id(philo));
    sem_post(philo->data->end);
    exit(1);
}

void	philo_wait(t_philo *philo)
{
	long long	task_time;
	int			sleep_base;
	long long	target;

	task_time = time_for_task(philo);
	sleep_base = 500;
	target = get_relativ_ms_time(philo->data) + task_time;
	while (get_relativ_ms_time(philo->data) < target)
	{
		usleep(sleep_base);
        if (!still_alive(philo))
            return;
	}
}

void	philo_wait_death(t_philo *philo)
{
	usleep((philo->data->time_to_die + philo->last_meal - get_relativ_ms_time(philo->data) + 1) * 1000);
}



void	philo_eat(t_philo *philo)
{
	while (philo->fork_n < 2)
		philo_wait_death(philo);
		// return;

	philo_wait(philo);
	if (philo->fork_n == 2)
    {
		update_has_already_eaten(philo);
              
    }
    drop_fork(philo);
    // if (philo->data->number_of_philosophers <= 1)
    //     return;
    drop_fork(philo);
	// if (philo->forks.prev)
	// {
	// 	pthread_mutex_unlock(&(philo->data->forks[get_prev_fork_id(philo)]));
	// 	philo->forks.prev = false;
	// }
	// if (philo->forks.next)
	// {
	// 	pthread_mutex_unlock(&(philo->data->forks[get_next_fork_id(philo)]));
	// 	philo->forks.next = false;
	// }
}

void	philo_sleep(t_philo *philo)
{
	philo_wait(philo);
}

// void check_death_while_waiting_for_forks(t_philo *philo)
// {
// 	// sem_close(philo->data->forks);
// 	philo_wait_death(philo);
// 	printf("philo should be dead %d %lld\n",get_philo_id(philo), get_relativ_ms_time(philo->data));
// 	// philo_died(philo);
// 	// sem_wait(philo->data->write_access);
// 	// printf("philo should be dead %d %lld\n",get_philo_id(philo), get_relativ_ms_time(philo->data));
// 	int i = -1;
// 		// printf("philo %d, %ld\n", philo->id, get_sem_val);
// 	// sem_post(philo->data->end);
// 	while(i++<philo->data->number_of_philosophers)
// 	{
// 		sem_post(philo->data->forks);
// 		sem_post(philo->data->forks);
// 	}
// 	// printf("%lld %d died, frm child\n", get_relativ_ms_time(philo->data), get_philo_id(philo));
// 	// usleep(5000);
// 	exit(1);
// }


void *death_while_wait_checker(void *args)
{
	t_philo *philo = philo;

	philo_wait_death(philo);
	still_alive(philo);
	// philo_died(philo);
	return NULL;
}

void take_fork(t_philo *philo)
{
	int status;
	pthread_t thread_id;

		
		// &data->philosophers[i].thread_id, NULL,	philosophe_routine, data->philosophers + i);
	// pthread_create(&thread_id, NULL, death_while_wait_checker, philo);
	// pthread_detach(thread_id);
	sem_wait(philo->data->forks);
	still_alive(philo);
    philo->fork_n++;
    philo->just_took_a_fork = true;
    print_state(philo);
}

void	philo_think(t_philo *philo)
{
	philo_wait(philo);
    take_fork(philo);
    if (philo->data->number_of_philosophers > 1)
        take_fork(philo);
}

void	act(t_philo *philo)
{
	t_state	state;

	print_state(philo);
	state = get_state(philo);
	if (state == sleeping)
		philo_sleep(philo);
	else if (state == thinking)
		philo_think(philo);
	else if (state == eating)
		philo_eat(philo);
}