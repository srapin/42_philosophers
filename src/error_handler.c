/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 01:59:44 by srapin            #+#    #+#             */
/*   Updated: 2023/04/27 02:05:48 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int		error_occured(t_error e)
{
	char *mess;
	
	if (e == none)
		mess = "error occured but wich one?";
	if (e == parse_error)
		mess = "parse error";
	printf("%s", mess);
	return e;
}