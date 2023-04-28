/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 00:35:46 by srapin            #+#    #+#             */
/*   Updated: 2023/04/28 02:46:23by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef enum e_error
{
	none,
	parse_error,
	state_equale_new_state
}					t_error;

typedef enum e_state
{
	died,
	eating,
	sleeping,
	thinking
}					t_state;

typedef struct s_fork
{
	bool			prev;
	bool			next;
}					t_fork;

struct s_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	int				number_of_times_each_philosopher_must_eat;
	suseconds_t		time_to_die;
	suseconds_t		time_to_eat;
	suseconds_t		time_to_sleep;
	pthread_mutex_t can_write;
	pthread_mutex_t *forks;
	struct s_philo	*philosophers;
}					t_data;

typedef struct s_philo
{
	int				i;
	int				has_already_eaten;
	struct timeval	last_meal;
	bool			just_took_a_fork;
	t_fork			forks;
	t_state			state;
	t_data			*data;
	pthread_t		thread;
}					t_philo;

//change_state
int					time_for_task(t_philo *p);
void				change_state(t_philo *philo);

//id_getter
int					get_next_neighbours_id(t_philo *philo);
int					get_prev_neighbours_id(t_philo *philo);
int					get_next_fork_id(t_philo *philo);
int					get_prev_fork_id(t_philo *philo);
int					get_philo_id(t_philo *philo);

//init
void init_data(t_data *data);

//parse
//bool	ft_strisint(char *str);
bool				parse(int ac, char **av, t_data *data);

//philo
void				*philosophe(void *args);

//print
void				print_state(t_philo *p);
bool				check_death(t_philo *philo);

//error_handler
int					error_occured(t_error e);

#endif