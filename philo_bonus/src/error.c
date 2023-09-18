/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:22:52 by srapin            #+#    #+#             */
/*   Updated: 2023/09/18 21:02:20 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	parse_error(void)
{
	printf("parse error\n argument must be positiv int\n");
	return (1);
}

int	alloc_error(void)
{
	printf("allocation error\n");
	return (1);
}
