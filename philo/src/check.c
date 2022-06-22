/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruizzo <mruizzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:52:43 by mruizzo           #+#    #+#             */
/*   Updated: 2022/06/22 18:16:19 by mruizzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (i == 0 && str[i] == '+')
			i++;
		if (str[i] < 48 || str[i] > 57)
			return (-1);
		i++;
	}
	return (0);
}

static int	ft_limits(long long nb)
{
	if (nb < 0 || nb > 2147483647)
		return (1);
	return (0);
}

int	check(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (check_digits(argv[i]) || ft_limits(ft_atoi(argv[i])))
			return (-1);
		i++;
	}
	if (ft_atoi(argv[1]) == 0)
		return (-1);
	return (0);
}
