/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruizzo <mruizzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:58:06 by mruizzo           #+#    #+#             */
/*   Updated: 2022/06/18 16:30:18 by mruizzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	dinner(void);
void		monitor(void *philo);

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
