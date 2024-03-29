/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:22:30 by srapin            #+#    #+#             */
/*   Updated: 2023/09/18 19:29:40 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	change_state(t_philo *philo)
{
	t_state	state;

	state = get_state(philo);
	if (state == died || check_end(philo->data, philo->id))
	{
		return ;
	}
	if (state == eating)
		set_state(philo, sleeping);
	else if (state == sleeping)
		set_state(philo, thinking);
	else if (state == thinking)
		set_state(philo, eating);
}
