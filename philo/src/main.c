/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruizzo <mruizzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:09:57 by mruizzo           #+#    #+#             */
/*   Updated: 2022/06/22 19:08:47 by mruizzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_rule *rule)
{
	int	i;

	i = 0;
	pthread_mutex_init(&rule->lock, NULL);
	pthread_mutex_init(&rule->die_mutex, NULL);
	pthread_mutex_init(&rule->eat_mutex, NULL);
	rule->forks = (pthread_mutex_t *) malloc
		(sizeof(pthread_mutex_t) * rule->num_philo);
	if (rule->forks == NULL)
		return (-1);
	while (i < rule->num_philo)
		pthread_mutex_init(&rule->forks[i++], NULL);
	return (0);
}

static int	init_rules(int argc, char **argv, t_rule *rule)
{
	rule->num_philo = ft_atoi(argv[1]);
	rule->time_die = ft_atoi(argv[2]);
	rule->time_eat = ft_atoi(argv[3]);
	rule->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rule->n_to_eat = ft_atoi(argv[5]);
	else
		rule->n_to_eat = -1;
	rule->some_die = 1;
	rule->finished = 1;
	rule->start_time = start_timer();
	rule->philo = (t_philo *) malloc (sizeof(t_philo) * rule->num_philo);
	if (rule->philo == NULL)
		return (-1);
	if (init_mutex(rule))
		return (-1);
	return (0);
}

void	init_philo(t_rule *rule)
{
	int	i;

	i = 0;
	while (i < rule->num_philo)
	{
		rule->philo[i].id = i + 1;
		rule->philo[i].n_eat = 0;
		rule->philo[i].end = 0;
		rule->philo[i].rule = rule;
		pthread_mutex_init(&rule->philo[i].philo_time, NULL);
		rule->philo[i].left = &rule->forks[i];
		rule->philo[i].right = &rule->forks[i + 1];
		if (i == rule->num_philo - 1)
			rule->philo[i].right = &rule->forks[0];
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_rule	rule;

	if (argc < 5 || argc > 6)
	{
		printf("numero di argomenti insufficente\n");
		return (-1);
	}
	else
	{
		if (check(argc, argv) || init_rules(argc, argv, &rule))
		{
			printf("errore negli argomenti\n");
			return (-1);
		}
		init_philo(&rule);
		start(&rule);
	}
}
