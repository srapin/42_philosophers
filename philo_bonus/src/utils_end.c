/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 23:15:23 by srapin            #+#    #+#             */
/*   Updated: 2023/09/14 23:38:01 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	check_end(void)
{
	return (sem_open("end", 0) != SEM_FAILED);
}

void	set_end(t_data *data)
{
	data->end = sem_open("end", O_CREAT, 0644, 0);
}

bool	check_print_end(void)
{
	return (sem_open("print_end", 0) != SEM_FAILED);
}

void	set_print_end(t_data *data)
{
	data->print_end = sem_open("print_end", O_CREAT, 0644, 0);
}
