/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:19:40 by srapin            #+#    #+#             */
/*   Updated: 2023/09/20 14:49:48 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h> /* For O_* constants */
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h> /* For mode constants */
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
#include <stdint.h>

// typedef enum e_error
// {
// 	none,
// 	parse_error,
// 	alloc_error,
// 	sem_error,
// 	fork_error
// }					t_error;

typedef enum e_state
{
	died,
	eating,
	sleeping,
	thinking
}				t_state;

typedef struct s_fork
{
	bool		prev;
	bool		next;
}				t_fork;

struct	s_philo;

typedef struct s_data
{
	int			number_of_philosophers;
	int			number_of_times_each_philosopher_must_eat;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	long long	start;
	sem_t		*forks;
	sem_t		*eat_enough;
	sem_t		**end_access;
	sem_t		**end;
	sem_t		*write_access;
	// t_error		error;
}				t_data;

typedef struct s_philo
{
	int			id;
	t_data		*data;
	t_state		state;
	int			has_already_eaten;
	long long	last_meal;
	bool		just_took_a_fork;
	int			fork_n;
	sem_t		*last_meal_access;
	sem_t		*state_access;
	pthread_t	monitor_id;
}				t_philo;

//act
void			act(t_philo *philo);
void			philo_wait(t_philo *philo);

//change_state
void			change_state(t_philo *philo);

//end_philo
void			philo_wait_death(t_philo *philo);
void			philo_died(t_philo *philo);
void			philo_exit(t_philo *philo);

//error
// int				parse_error(void);
// int				alloc_error(void);

// exit
void			monitor_exit(t_data *data, pid_t *pids);
void			close_data_sem(t_data *data);
//forks
void			drop_fork(t_philo *philo);
void			take_fork(t_philo *philo);

//ft_itoa
char	*ft_itoa(int n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strjoin(const char *s1, const char *s2);

//id_getter
int				get_philo_id(t_philo *philo);

//init
void			init(int ac, char **av, t_data *data);
void			init_philo(t_philo *philo, t_data *data, int i);
char *get_sem_end_name(int i);
char *get_sem_end_access_name(int i);
//launcher
pid_t			*lets_gow(t_data *data);

//main
int				main(int ac, char **av);

//monitor
void			monitor(t_data *data, pid_t *pids);

//parse
bool			check_args(int ac, char **av);
long int		ft_atoi(const char *nptr);

//print
void			print_state(t_philo *p);

//routines
void			philosophe_routine(t_data *data, int i);
void			eat_enough_checker_routine(t_data *data);
void			*death_checker_routine(void *args);

//time
long long		get_relativ_ms_time(t_data *data);
long long		get_ms_time(void);
int				time_for_task(t_philo *p);

//utlis_end
void			set_end(t_data *data, int i);
bool			check_end(t_data *data, int i);
bool			check_print_end(t_data *data);
void			set_print_end(t_data *data);

//utils_getter
long long		get_last_meal(t_philo *philo);
int				get_has_already_eaten(t_philo *philo);
t_state			get_state(t_philo *philo);

//utils
void			update_last_meal(t_philo *philo, long long rel_time);
bool			update_has_already_eaten(t_philo *philo);
void			set_state(t_philo *philo, t_state s);
bool			max_meals_specified(t_data *data);
void			unlink_sem(void);
#endif

/*
recuperer itoa

initaliser une semaphore par philo? ->pas d init car check avec open
creer un tableau dans data (enfait 2, celle d acces au check et celle pour pourvoir essayer d ouvrir)
check end devient ->
wait (data->sem_end[i])
sem_open (name + itoa)
post (data->sem_end[i])

set end devient ->
while (i)
	wait (data->sem_end[i])  //esperer que c est assez rapide
	
while (i)
	sem_open (name + itoa)
while (i)
	post (data->sem_end[i])

idem print end ->relou ->essayer sans print end
*/