/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruizzo <mruizzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:58:06 by mruizzo           #+#    #+#             */
/*   Updated: 2022/06/24 16:14:11 by mruizzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean(t_rule *rule)
{
	int		i;
	t_philo	*philo;

	philo = rule->philo;
	i = 0;
	while (i < rule->num_philo)
	{
		pthread_mutex_destroy(&rule->forks[i]);
		pthread_mutex_destroy(&rule->philo[i].philo_time);
		i++;
	}
	pthread_mutex_destroy(&rule->lock);
	pthread_mutex_destroy(&rule->die_mutex);
	pthread_mutex_destroy(&rule->eat_mutex);
	free(philo);
	free(rule->forks);
}

static void	*dinner(void *philo)
{
	t_philo	*ph;

	ph = philo;
	starving(ph);
	while (check_mutex(0, ph))
	{	
		if (take_forks(ph))
			return (NULL);
		if (check_mutex(0, ph))
			philo_msg(ph, ph->id, "is eating");
		starving(ph);
		ph->n_eat++;
		if (ph->n_eat == ph->rule->n_to_eat)
		{
			pthread_mutex_lock(&ph->rule->eat_mutex);
			ph->end = 1;
			pthread_mutex_unlock(&ph->rule->eat_mutex);
		}
		routine(ph);
	}
	return (NULL);
}

void	start(t_rule *rule)
{
	int	i;

	i = -1;
	rule->start_time = start_timer();
	while (++i < rule->num_philo)
		pthread_create(&rule->philo[i].thread, NULL, dinner, &rule->philo[i]);
	i = 0;
	monitor(rule);
	while (i < rule->num_philo)
	{
		pthread_join(rule->philo[i].thread, NULL);
		i++;
	}
	clean(rule);
}
