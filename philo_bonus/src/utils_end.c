/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 23:15:23 by srapin            #+#    #+#             */
/*   Updated: 2023/09/15 00:58:39 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	check_end(t_data *data)
{
	bool	flag;
	(void)data;
	sem_wait(data->end_access);
	flag = (sem_open("end", 0) != SEM_FAILED);
	sem_post(data->end_access);
	return (flag);
}

void	set_end(t_data *data)
{
	sem_wait(data->end_access);
	data->end = sem_open("end", O_CREAT, 0644, 0);
	sem_post(data->end_access);
}

bool	check_print_end(t_data *data)
{
	bool	flag;

	sem_wait(data->print_end_access);
	flag =  (sem_open("print_end", 0) != SEM_FAILED);
	sem_post(data->print_end_access);
	return (flag);
}

void	set_print_end(t_data *data)
{
	sem_wait(data->print_end_access);
	data->print_end = sem_open("print_end", O_CREAT, 0644, 0);
	sem_post(data->print_end_access);
}
