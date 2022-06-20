/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruizzo <mruizzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:18:08 by mruizzo           #+#    #+#             */
/*   Updated: 2022/06/20 17:28:09 by mruizzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo	*ph)
{
	if (ph->id == ph->rule->num_philo)
	{
		pthread_mutex_lock(ph->left);
		ft_philo_msg(ph, ph->id, "has taken a fork");
		pthread_mutex_lock(ph->right);
		ft_philo_msg(ph, ph->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(ph->right);
		ft_philo_msg(ph, ph->id, "has taken a fork");
		pthread_mutex_lock(ph->left);
		ft_philo_msg(ph, ph->id, "has taken a fork");
	}
	return (0);
}
