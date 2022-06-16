/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruizzo <mruizzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:52:43 by mruizzo           #+#    #+#             */
/*   Updated: 2022/06/16 19:16:26 by mruizzo          ###   ########.fr       */
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

int	check(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) > 250 && i == 0)
			return (-1);
		if (ft_atoi(argv[i]) < 0 || check_digits(argv[i]))
			return (-1);
		i++;
	}
	return (0);
}
