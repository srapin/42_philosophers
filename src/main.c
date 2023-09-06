/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:29:53 by srapin            #+#    #+#             */
/*   Updated: 2023/09/05 20:50:34 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int main(int ac, char **av)
{
	// printf("before\n");
	t_data data;
	pthread_t thread;
	// char *test = "test";
	void *res;

	if (!check_args(ac, av))
		return error_occured(parse_error, NULL);
	printf("before\n");
	init_data(ac, av, &data);
	printf("before\n");
	lets_gow(&data);
	printf("before\n");
		
	// printf("before\n");
	// // pthread_create(&thread, NULL, &philo, test);
	// printf("between\n");
	// //pthread_join(thread, &res);
	// printf("after\n");
}