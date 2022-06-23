/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruizzo <mruizzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:58:06 by mruizzo           #+#    #+#             */
/*   Updated: 2022/06/23 20:15:39 by mruizzo          ###   ########.fr       */
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

void	monitor(t_rule *rule)
{
	t_philo		*ph;
	int			i;
	uint64_t	tmp;

	ph = rule->philo;
	usleep(50);
	while (1)
	{
		i = 0;
		while (i < rule->num_philo)
		{
			pthread_mutex_lock(&ph[i].philo_time);
			tmp = start_timer() - ph->rule->start_time - ph->strv;
			pthread_mutex_unlock(&ph[i].philo_time);
			if (tmp > ph->rule->time_die)
			{
				pthread_mutex_lock(&rule->lock);
				rule->some_die = 0;
				pthread_mutex_unlock(&rule->lock);
				pthread_mutex_unlock(&rule->die_mutex);
				usleep(500);
					philo_msg(&ph[i], ph[i].id, "died");
				return ;
			}
		i++;
		}
	}
}

static void	*dinner(void *philo)
{
	t_philo	*ph;

	ph = philo;
	starving(ph);
	while (check_mutex(0, ph))
	{	
		take_forks(ph);
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
