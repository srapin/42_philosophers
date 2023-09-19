/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:27:27 by srapin            #+#    #+#             */
/*   Updated: 2023/09/19 17:45:03 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int  do_someting()
{
	return 1;
}

int	main(int ac, char **av)
{
	t_data	data;
	pid_t	*pids;

	if (!check_args(ac, av))
		return 1;
		// return (parse_error());
	init(ac, av, &data);
	// if (data.error)
	// 	return do_someting();
	pids = lets_gow(&data);
	if (!pids)
		return (0);
	monitor(&data, pids);
}
