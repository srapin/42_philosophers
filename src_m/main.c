/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:29:53 by srapin            #+#    #+#             */
/*   Updated: 2023/09/09 21:27:35 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int main(int ac, char **av)
{
	t_data data;
	// pthread_t thread;
	// void *res;

	if (!check_args(ac, av))
		return error_occured(parse_error, NULL);
	init_data(ac, av, &data);
	lets_gow(&data);
	ft_exit(&data);
}