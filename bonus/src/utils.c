/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:10:21 by srapin            #+#    #+#             */
/*   Updated: 2023/09/13 23:17:07 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


bool still_alive(t_philo *philo)
{
    bool is_alive = (get_relativ_ms_time(philo->data) - philo->last_meal <= philo->data->time_to_die);
    if (!is_alive)
    {
        philo_died(philo);
        
    }
    return (is_alive && philo->state!=died);
}

void	set_state(t_philo *philo, t_state s)
{
	philo->state = s;
}


t_state	get_state(t_philo *philo)
{
	t_state	s;

	s = philo->state;
	return (s);
}

int	get_has_already_eaten(t_philo *philo)
{
	int	has_already_eaten;

	has_already_eaten = philo->has_already_eaten;
	return (has_already_eaten);
}


long long	get_last_meal(t_philo *philo)
{
	long long	lm;

	lm = philo->last_meal;
	return (lm);
}

// void	take_fork(t_philo *philo, int fork_id, bool *flag)
// {
// 	pthread_mutex_lock(&(philo->data->forks[fork_id]));
// 	philo->just_took_a_fork = true;
// 	*flag = true;
// 	print_state(philo);
// }

void	update_has_already_eaten(t_philo *philo)
{
	philo->has_already_eaten++;
		// printf("incrementing %d %d %d\n",  philo->data->number_of_times_each_philosopher_must_eat, philo->has_already_eaten, philo->id );	
    if (philo->has_already_eaten == philo->data->number_of_times_each_philosopher_must_eat && number_of_times_each_philosopher_must_eat_specified(philo->data))
	{
		// printf("incrementing\n");	
        sem_post(philo->data->eat_enough);
	}
}

void	update_last_meal(t_philo *philo, long long rel_time)
{
	philo->last_meal = rel_time;
}

bool number_of_times_each_philosopher_must_eat_specified(t_data *data)
{
    return (data->number_of_times_each_philosopher_must_eat > -1);
}

