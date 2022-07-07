/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruizzo <mruizzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:13:56 by mruizzo           #+#    #+#             */
/*   Updated: 2022/07/07 18:54:01 by mruizzo          ###   ########.fr       */
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

static int	real_monitor(t_rule *rule, t_philo *ph, int i, long long tmp)
{	
	int			check;

	check = 0;
	tmp = 0;
	while (i < rule->num_philo)
	{
		pthread_mutex_lock(&rule->philo_time);
		tmp = start_timer() - rule->start_time - ph[i].strv;
		pthread_mutex_unlock(&rule->philo_time);
		if (tmp > (long long) ph->rule->time_die)
		{
			kill(ph[i].rule);
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
	long long	tmp;

	i = 0;
	tmp = 0;
	ph = rule->philo;
	while (1)
	{
		if (real_monitor(rule, ph, i, tmp) == 1)
			break ;
	}
}
