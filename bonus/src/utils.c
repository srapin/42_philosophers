/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:10:21 by srapin            #+#    #+#             */
/*   Updated: 2023/09/12 01:37:24 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// long get_sem_val(sem_t s)
// {
//     return s.__align;
// }

// bool some_philo_died(t_data *data)
// {
//     return get_sem_val(*data->end)  >= 0;
// }

bool still_alive(t_philo *philo)
{
    bool is_alive = (get_relativ_ms_time(philo->data) - philo->last_meal < philo->data->time_to_die);
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

// bool	check_end(t_data *data)
// {
// 	bool	end;

// 	pthread_mutex_lock(&data->end_access);
// 	end = data->end;
// 	pthread_mutex_unlock(&data->end_access);
// 	return (end);
// }

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
    if (philo->has_already_eaten == philo->data->number_of_times_each_philosopher_must_eat)
        sem_post(philo->data->eat_enough);
}

void	update_last_meal(t_philo *philo, long long rel_time)
{
	philo->last_meal = rel_time;
}

bool number_of_times_each_philosopher_must_eat_specified(t_data *data)
{
    return (data->number_of_times_each_philosopher_must_eat > -1);
}

