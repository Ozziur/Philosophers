/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruizzo <mruizzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:13:56 by mruizzo           #+#    #+#             */
/*   Updated: 2022/06/29 14:46:30 by mruizzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	kill(t_rule *rule)
{
	pthread_mutex_lock(&rule->die_mutex);
	rule->some_die = 0;
	pthread_mutex_unlock(&rule->die_mutex);
}

static int	second_monitor(t_rule *rule, int *check)
{
	if (*check >= rule->num_philo)
	{
		kill(rule);
		rule->finished = 0;
		return (1);
	}
	else
		*check = 0;
	return (0);
}

static int	real_monitor(t_rule *rule, t_philo *ph, int i, uint64_t tmp)
{	
	int			check;

	check = 0;
	while (i < rule->num_philo)
	{
		pthread_mutex_lock(&ph[i].philo_time);
		tmp = start_timer() - ph->rule->start_time - ph->strv;
		pthread_mutex_unlock(&ph[i].philo_time);
		if (tmp > ph->rule->time_die)
		{
			kill(rule);
			usleep(400);
			philo_msg(&ph[i], ph[i].id, "died");
			return (1);
		}
		if (check_mutex(1, &ph[i]))
			check++;
		i++;
	}
	if (second_monitor(rule, &check))
		return (1);
	return (0);
}

void	monitor(t_rule *rule)
{
	t_philo		*ph;
	int			i;
	uint64_t	tmp;

	i = 0;
	tmp = 0;
	ph = rule->philo;
	usleep(50);
	while (1)
	{
		if (real_monitor(rule, ph, i, tmp))
			return ;
	}
}
