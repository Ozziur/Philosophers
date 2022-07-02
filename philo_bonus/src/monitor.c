/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruizzo <mruizzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 16:13:56 by mruizzo           #+#    #+#             */
/*   Updated: 2022/07/02 20:14:27 by mruizzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*must_eat(void *rule)
{
	t_rule	*ru;
	int		i;

	ru = rule;
	i = 0;
	while (i < ru->num_philo)
	{
		sem_wait(ru->finish);
		i++;
	}
	i = 0;
	while (i < ru->num_philo)
	{
		kill(ru->philo[i].pid, SIGKILL);
		i++;
	}
	sem_post(ru->dead);
	return (NULL);
}

static int	finish(t_philo *ph)
{
	int	tmp;

	tmp = start_timer() - ph->rule->start_time;
	if (tmp - ph->strv > ph->rule->time_die)
	{
		sem_wait(ph->rule->msg);
		printf("%llu %d died\n", start_timer() - ph->rule->start_time, ph->id);
		sem_post(ph->rule->dead);
		//aggiungere ammazza processi
		return (1);
	}
	if (ph->n_eat == ph->rule->n_to_eat)
	{
		sem_post(ph->rule->finish);
		return (1);
	}
	return (0);
}

void	*monitor(void *philo)
{
	t_philo		*ph;

	ph = philo;
	while (1)
	{
		if (finish(ph) == 1)
			return (NULL);
	}
	return (NULL);
}
