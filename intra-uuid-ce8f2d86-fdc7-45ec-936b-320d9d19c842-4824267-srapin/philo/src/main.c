/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:29:53 by srapin            #+#    #+#             */
/*   Updated: 2023/09/10 20:52:47 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (!check_args(ac, av))
		return (error_occured(parse_error, false, NULL));
	init(ac, av, &data);
	lets_gow(&data);
	ft_exit(&data);
}
