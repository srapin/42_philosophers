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
# include <unistd.h>


typedef enum e_error
{
	none,
	parse_error,
	state_equale_new_state,
	eat_whit_not_enough_forks
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
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		start;
	pthread_mutex_t can_write;
	pthread_mutex_t *forks;
	pthread_mutex_t starter_m;
	pthread_mutex_t end_access;
	pthread_t		number_of_meal_checker_thread;
	bool			end;
	struct s_philo	*philosophers;
}					t_data;

typedef struct s_philo
{
	int				id;
	t_data			*data;
	pthread_t		thread_id;
	t_state		state;
	int				has_already_eaten;
	long long	last_meal; //probleme de calcule?
	bool			just_took_a_fork;
	t_fork			forks;
	pthread_mutex_t state_access;
	pthread_mutex_t last_meal_access;
	pthread_mutex_t has_already_eaten_access;
}					t_philo;
//act
void act(t_philo *philo);

//change_state
int					time_for_task(t_philo *p);
void				change_state(t_philo *philo);

//error_handler
int		error_occured(t_error e, t_philo *p);
// exit
void ft_exit(t_data *data);

//id_getter
int					get_next_neighbours_id(t_philo *philo);
int					get_prev_neighbours_id(t_philo *philo);
int					get_next_fork_id(t_philo *philo);
int					get_prev_fork_id(t_philo *philo);
int					get_philo_id(t_philo *philo);

//init
void init_data(int ac, char **av, t_data *data);
void set_start_time(t_data *data);


//launcher
void lets_gow(t_data *data);


//main
int main(int ac, char **av);


//parse
bool	check_args(int ac, char ** av);

//time
long long get_relativ_ms_time(t_data *data);
long long get_ms_time();
void update_last_meal(t_philo * philo, long long rel_time);






//bool	ft_strisint(char *str);
// bool				parse(int ac, char **av, t_data *data);

//philo

//print
void				print_state(t_philo *p);
bool				is_alive(t_philo *philo);

//error_handler
int					error_occured(t_error e, t_philo *p);

//routines
void				*philosophe_routine(void *args);
void				*supervisor_routine(void *args);

//util

long long get_last_meal(t_philo *philo);
void update_end(t_data *data, bool value);
bool check_end(t_data *data);
void update_has_already_eaten(t_philo *philo);
int get_has_already_eaten(t_philo *philo);
long int ft_atoi(const char *);
void set_state(t_philo *philo, t_state s);
t_state get_state(t_philo *philo);
#endif