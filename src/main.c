/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:29:53 by srapin            #+#    #+#             */
/*   Updated: 2023/09/04 18:00:21 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int main(int ac, char **av)
{
	printf("before\n");
	t_data data;
	pthread_t thread;
	// char *test = "test";
	void *res;

	if (!parse(ac, av, &data))
		return error_occured(parse_error, NULL);
	init_data(&data);
	
	printf("before\n");
	// pthread_create(&thread, NULL, &philo, test);
	printf("between\n");
	//pthread_join(thread, &res);
	printf("after\n");
}