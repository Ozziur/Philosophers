/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruizzo <mruizzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:18:08 by mruizzo           #+#    #+#             */
/*   Updated: 2022/06/22 18:41:42 by mruizzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo	*ph)
{
	if (ph->id == ph->rule->num_philo)
	{
		pthread_mutex_lock(ph->left);
		philo_msg(ph, ph->id, "has taken a fork");
		pthread_mutex_lock(ph->right);
		philo_msg(ph, ph->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(ph->right);
		philo_msg(ph, ph->id, "has taken a fork");
		pthread_mutex_lock(ph->left);
		philo_msg(ph, ph->id, "has taken a fork");
	}
	return (0);
}

void	starving(t_philo *ph)
{
	pthread_mutex_lock(&ph->philo_time);
	ph->strv = start_timer() - ph->rule->start_time;
	pthread_mutex_unlock(&ph->philo_time);
}

void	routine(t_philo *ph)
{
	my_sleep(ph->rule->time_eat);
	pthread_mutex_unlock(ph->right);
	pthread_mutex_unlock(ph->left);
	philo_msg(ph, ph->id, "is sleeping");
	my_sleep(ph->rule->time_sleep);
	philo_msg(ph, ph->id, "is thinking");
}

int	check_mutex(int flag, t_philo *ph)
{
	int	tmp;

	tmp = 0;
	if (flag == 0)
	{
		pthread_mutex_lock(&ph->rule->die_mutex);
		tmp = ph->rule->some_die;
		pthread_mutex_unlock(&ph->rule->die_mutex);
	}
	else if (flag == 1)
	{
		pthread_mutex_lock(&ph->rule->eat_mutex);
		tmp = ph->end;
		pthread_mutex_unlock(&ph->rule->eat_mutex);
	}
	return (tmp);
}
