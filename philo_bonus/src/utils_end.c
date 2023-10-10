/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 23:15:23 by srapin            #+#    #+#             */
/*   Updated: 2023/10/11 00:47:27 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	check_end(t_data *data, int i)
{
	bool	flag;
	char	*name;

	flag = true;
	sem_wait(data->end_access[i]);
	name = get_sem_end_name(i);
	if (!name)
	{	
		sem_post(data->end_access[i]);
		return (true);
	}
	if (!data->end[i])
	{
		data->end[i] = sem_open(name, 0);
		flag = data->end[i];
		// sem_close(data->end[i]);
		// data->end[i] = NULL;
	}
	flag = data->end[i];
	sem_post(data->end_access[i]);
	free(name);
	return (flag);
}

bool	check_end_whitout_waiting(t_data *data)
{
	bool	flag;
	char	*end_name;

	end_name = get_sem_end_name(data->number_of_philosophers);
	data->end[data->number_of_philosophers] = sem_open(end_name, 0);
	flag = data->end[data->number_of_philosophers];
	if (flag)
	{
		sem_close(data->end[data->number_of_philosophers]);
		data->end[data->number_of_philosophers] = NULL;
	}
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

void	set_local_end(t_data *data, int id)
{
	char	*end_name;

	sem_wait(data->end_access[data->number_of_philosophers]);
	if (!check_end_whitout_waiting(data))
	{
		end_name = get_sem_end_name(data->number_of_philosophers);
		data->end[data->number_of_philosophers] = sem_open(end_name, O_CREAT, 0644, 0);
		free(end_name);
		usleep(500);
		if (id < data->number_of_philosophers)
		{
			sem_wait(data->write_access);
			printf("%lld %d died\n", get_relativ_ms_time(data), id + 1);
			sem_post(data->write_access);
		}
	}
	sem_post(data->end_access[data->number_of_philosophers]);
}

void	set_end(t_data *data)
{
	int		i;
	char	*end_name;

	i = 0;
	act_on_end_sem(data, &sem_wait);
	while (i < data->number_of_philosophers)
	{
		end_name = get_sem_end_name(i);
		data->end[i] = sem_open(end_name, O_CREAT, 0644, 0);
		sem_close(data->end[i]);
		free(end_name);
		i++;
	}
	act_on_end_sem(data, &sem_post);
}
