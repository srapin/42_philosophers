/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srapin <srapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 00:42:37 by srapin            #+#    #+#             */
/*   Updated: 2023/09/10 20:36:35 by srapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	change_state(t_philo *philo)
{
	t_state	state;

	state = get_state(philo);
	if (state == eating && get_prev_fork_id(philo) != get_next_fork_id(philo))
		set_state(philo, sleeping);
	else if (state == sleeping)
		set_state(philo, thinking);
	else if (state == thinking)
		set_state(philo, eating);
}
