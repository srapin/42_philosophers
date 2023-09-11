/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:19:40 by srapin            #+#    #+#             */
/*   Updated: 2023/09/12 01:03:59 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
       
typedef enum e_error
{
	none,
	parse_error
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

struct	s_philo;

typedef struct s_data
{
	int				number_of_philosophers;
	int				number_of_times_each_philosopher_must_eat;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		start;
    sem_t *         forks;
    sem_t *         write_access;
    sem_t *         end;
    sem_t *         eat_enough;
	// pthread_mutex_t	can_write;
	// pthread_mutex_t	*forks;
	// pthread_mutex_t	starter_m;
	// pthread_mutex_t	end_access;
	// pthread_t		number_of_meal_checker_thread;
	// bool			end;
	// struct s_philo	*philosophers;
}					t_data;

typedef struct s_philo
{
	int				id;
	t_data			*data;
    
	// pthread_t		thread_id;
	t_state			state;
	int				has_already_eaten;
	long long		last_meal;
	bool			just_took_a_fork;
	int			    fork_n;
	// pthread_mutex_t	state_access;
	// pthread_mutex_t	last_meal_access;
	// pthread_mutex_t	has_already_eaten_access;
}					t_philo;

//act
void				act(t_philo *philo);
void philo_died(t_philo *philo);
//change_state
void				change_state(t_philo *philo);
//error
int	error_occured(t_error e, bool need_to_ask, sem_t *can_write);
// exit
// void				ft_exit(t_data *data);
//id_getter
// int					get_next_fork_id(t_philo *philo);
// int					get_prev_fork_id(t_philo *philo);
int					get_philo_id(t_philo *philo);
//init_mutexes
void				init_mutexes(t_data *data);
//init
void				init(int ac, char **av, t_data *data);
//launcher
pid_t *				lets_gow(t_data *data);
//main
int					main(int ac, char **av);
//parse
bool				check_args(int ac, char **av);
long int	ft_atoi(const char *nptr);
//print
void				print_state(t_philo *p);
//routines
void	philosophe_routine(t_data *data, int i);
// void				*number_of_meal_checker_routine(void *arg);
// void				*supervisor_routine(void *args);
//time
long long			get_relativ_ms_time(t_data *data);
long long			get_ms_time(void);
int					time_for_task(t_philo *p);
//utils
long get_sem_val(sem_t s);
bool some_philo_died(t_data *data);
bool still_alive(t_philo *philo);
void	set_state(t_philo *philo, t_state s);
long long			get_last_meal(t_philo *philo);
int					get_has_already_eaten(t_philo *philo);
t_state				get_state(t_philo *philo);
// void				take_fork(t_philo *philo, int fork_id, bool *flag);
void				update_has_already_eaten(t_philo *philo);
void				set_state(t_philo *philo, t_state s);
void				update_last_meal(t_philo *philo, long long rel_time);

bool number_of_times_each_philosopher_must_eat_specified(t_data *data);
void end_check_routine(t_data *data);
#endif