/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruizzo <mruizzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:09:57 by mruizzo           #+#    #+#             */
/*   Updated: 2022/07/05 17:40:50 by mruizzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static sem_t	*sem_in(const char *name, unsigned int value)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (sem != SEM_FAILED)
		return (sem);
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0644, value));
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
	rule->msg = sem_in("/message", 1);
	rule->forks = sem_in("/forks", rule->num_philo);
	rule->finish = sem_in("/must_eat", 0);
	rule->dead = sem_in("/dead", 0);
	rule->philo = (t_philo *) malloc (sizeof(t_philo) * rule->num_philo);
	if (rule->philo == NULL)
		return (-1);
	return (0);
}

static void	init_philo(t_rule *rule)
{
	int	i;

	i = 0;
	while (i < rule->num_philo)
	{
		rule->philo[i].id = i + 1;
		rule->philo[i].n_eat = 0;
		rule->philo[i].rule = rule;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_rule	rule;

	if (argc < 5 || argc > 6)
	{
		printf("numero di argomenti erroneo\n");
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
