/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruizzo <mruizzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:07:47 by mruizzo           #+#    #+#             */
/*   Updated: 2022/06/06 18:56:48 by mruizzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

typedef struct s_rule
{
	int			num_philo;
	long long	time_die;
	long long	time_eat;
	long long	time_sleep;
	int			times_to_eat;
	int			some_die;
	int			finished;
	long long	start_time;
}	t_rule;

int	check(int argc, char **argv);
int	ft_atoi(const char *str);

#endif