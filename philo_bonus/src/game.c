/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruizzo <mruizzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:58:06 by mruizzo           #+#    #+#             */
/*   Updated: 2022/07/02 19:00:00 by mruizzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	dinner(void *philo)
{
	t_philo		*ph;

	ph = philo;
	ph->rule->start_time = start_timer();
	ph->strv = start_timer() - ph->rule->start_time;
	pthread_create(&ph->death, NULL, monitor, ph);
	while (1)
	{
		sem_wait(ph->rule->forks);
		philo_msg(ph, ph->id, "has taken a fork");
		sem_wait(ph->rule->forks);
		philo_msg(ph, ph->id, "has taken a fork");
		philo_msg(ph, ph->id, "is eating");
		ph->n_eat++;
		ph->strv = start_timer() - ph->rule->start_time;
		my_sleep(ph->rule->time_eat, ph->rule);
		sem_post(ph->rule->forks);
		sem_post(ph->rule->forks);
		philo_msg(ph, ph->id, "is sleeping");
		my_sleep(ph->rule->time_sleep, ph->rule);
		philo_msg(ph, ph->id, "is thinking");
	}
	exit (0);
}

void	start(t_rule *rule)
{
	int			i;

	i = 0;
	rule->start_time = start_timer();
	pthread_create(&rule->finish_eat, NULL, must_eat, rule);
	while (i < rule->num_philo)
	{
		rule->philo[i].pid = fork();
		if (rule->philo[i].pid == 0)
			dinner(&rule->philo[i]);
		i++;
	}
	sem_wait(rule->dead);
	exit (0);
}
