/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruizzo <mruizzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:09:57 by mruizzo           #+#    #+#             */
/*   Updated: 2022/06/08 17:42:03 by mruizzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosophers(int argc, char **argv)
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
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (-1);
	else
	{
		if (check(argc, argv))
			return (-1);
		if (philosophers(argc, argv))
			return (-1);
	}
}
