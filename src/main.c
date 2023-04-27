/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:29:53 by srapin            #+#    #+#             */
/*   Updated: 2023/04/27 03:38:17 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int main(int ac, char **av)
{
	t_data data;
	pthread_t thread;
	char *test = "test";
	void *res;

	if (!parse(ac, av, &data))
		return error_occured(parse_error);
	printf("before\n");
	pthread_create(&thread, NULL, &philo, test);
	printf("between\n");
	pthread_join(thread, &res);
	printf("after\n");
}