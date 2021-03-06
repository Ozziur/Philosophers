/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruizzo <mruizzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:54:46 by mruizzo           #+#    #+#             */
/*   Updated: 2022/07/05 17:53:33 by mruizzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	ret;

	i = 0;
	sign = 1;
	ret = 0;
	while ((*(str + i) > 8 && *(str + i) < 14) || *(str + i) == 32)
		i++;
	if (*(str + i) == 43 || *(str + i) == 45)
	{
		if (*(str + i) == 45)
			sign *= -1;
		i++;
	}
	if (*(str + i) == 43 || *(str + i) == 45)
		return (0);
	while (*(str + i) > 47 && *(str + i) < 58)
	{
		ret = (ret * 10) + (*(str + i) - 48);
		i++;
	}
	return (ret * sign);
}

void	my_sleep(uint64_t time)
{
	uint64_t	tmp;

	tmp = start_timer();
	usleep(time * 1000 - 20000);
	while (start_timer() < tmp + time)
		continue ;
}

void	philo_msg(t_philo *ph, int id, char *str)
{
	sem_wait(ph->rule->msg);
	printf("%llu", start_timer() - ph->rule->start_time);
	printf(" %d %s\n", id, str);
	sem_post(ph->rule->msg);
}
