/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruizzo <mruizzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:09:57 by mruizzo           #+#    #+#             */
/*   Updated: 2022/06/16 19:27:17 by mruizzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philosophers(int argc, char **argv)
{
	t_rule	rule;

	rule.num_philo = ft_atoi(argv[1]);
	rule.time_die = ft_atoi(argv[2]);
	rule.time_eat = ft_atoi(argv[3]);
	rule.time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rule.n_to_eat = ft_atoi(argv[5]);
	else
		rule.n_to_eat = -1;
	rule.some_die = 0;
	rule.finished = 0;
	rule.start_time = start_timer();
	start(&rule);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("numero di argomenti insufficente");
		return (-1);
	}
	else
	{
		if (check(argc, argv))
		{
			printf("errore negli argomenti");
			return (-1);
		}
		philosophers(argc, argv);
	}
}
