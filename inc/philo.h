/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 00:35:46 by srapin            #+#    #+#             */
/*   Updated: 2023/04/27 02:21:47 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum e_error
{
	none,
	parse_error
}	t_error;

typedef enum e_state
{
	died,
	eating,
	sleeping,
	thinking
}	t_state;


typedef struct s_param
{
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
} t_param;

typedef struct s_fork
{
	bool left;
	bool right;
}	t_fork;

typedef struct s_philo
{
	int id;
	int has_already_eaten;
	t_fork forks;
	t_state state;
	int start_state_time;
}	t_philo;




//parse
//bool	ft_strisint(char *str);
bool	parse(int ac, char **av, t_param *param);

//error_handler
int		error_occured(t_error e);

#endif