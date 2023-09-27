/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 23:15:23 by srapin            #+#    #+#             */
/*   Updated: 2023/09/27 19:17:38 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	check_end(t_data *data, int i)
{
	bool	flag;
	char	*end_name;

	end_name = get_sem_end_name(i);
	if (!end_name)
		return (1);
	sem_wait(data->end_access[i]);
	data->end[i] = sem_open(end_name, 0);
	flag = data->end[i];
	if (flag)
		sem_close(data->end[i]);
	sem_post(data->end_access[i]);
	free(end_name);
	return (flag);
}

bool	check_end_whitout_waiting(t_data *data, int i)
{
	bool	flag;
	char	*end_name;

	end_name = get_sem_end_name(i);
	data->end[i] = sem_open(end_name, 0);
	flag = data->end[i];
	free(end_name);
	return (flag);
}

void	act_on_end_sem(t_data *data, int foo(sem_t *))
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers + 1)
	{
		foo(data->end_access[i]);
		i++;
	}
}

void	set_end(t_data *data, int id)
{
	int		i;
	char	*end_name;

	i = 0;
	act_on_end_sem(data, &sem_wait);
	if (id < data->number_of_philosophers && !check_end_whitout_waiting(data,
			id))
	{
		sem_wait(data->write_access);
		printf("%lld %d died\n", get_relativ_ms_time(data), id + 1);
		sem_post(data->write_access);
	}
	i = 0;
	while (i < data->number_of_philosophers + 1)
	{
		end_name = get_sem_end_name(i);
		data->end[i] = sem_open(end_name, O_CREAT, 0644, 0);
		free(end_name);
		i++;
	}
	act_on_end_sem(data, &sem_post);
}
