/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruizzo <mruizzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:18:08 by mruizzo           #+#    #+#             */
/*   Updated: 2022/07/15 17:55:17 by mruizzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo	*ph)
{
	pthread_mutex_lock(ph->left);
	if (check_mutex(0, ph))
		philo_msg(ph, ph->id, "has taken a fork");
	if (ph->rule->num_philo == 1)
		return (1);
	pthread_mutex_lock(ph->right);
	if (check_mutex(0, ph))
		philo_msg(ph, ph->id, "has taken a fork");
	return (0);
}

void	starving(t_philo *ph)
{
	pthread_mutex_lock(&ph->rule->philo_time);
	ph->strv = start_timer() - ph->rule->start_time;
	pthread_mutex_unlock(&ph->rule->philo_time);
}

void	routine(t_philo *ph)
{
	pthread_mutex_unlock(ph->right);
	pthread_mutex_unlock(ph->left);
	if (check_mutex(0, ph))
		philo_msg(ph, ph->id, "is sleeping");
	if (check_mutex(0, ph))
		my_sleep(ph->rule->time_sleep);
	if (check_mutex(0, ph))
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
