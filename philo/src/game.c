/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruizzo <mruizzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:58:06 by mruizzo           #+#    #+#             */
/*   Updated: 2022/06/20 20:00:48 by mruizzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		monitor(void *philo);

static void	*dinner(void *philo)
{
	t_philo	*ph;

	ph = philo;
	starving(ph);
	while (check_mutex(0, ph))
	{
		take_forks(ph);
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
	monitor(rule->philo);
	i = 0;
	while (i < rule->num_philo)
		pthread_join(rule->philo[i++].thread, NULL);
	clean();
}
