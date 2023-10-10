/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:27:27 by srapin            #+#    #+#             */
/*   Updated: 2023/10/10 22:21:20 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	pid_t	*pids;

	if (!check_args(ac, av))
	{
		printf("usage : ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n\
All args must be positive integers\n");
		return (1);
	}
	init(ac, av, &data);
	pids = lets_gow(&data);
	if (!pids)
		return (0);
	monitor(&data, pids);
}
