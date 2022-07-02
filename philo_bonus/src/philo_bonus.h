/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruizzo <mruizzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:07:47 by mruizzo           #+#    #+#             */
/*   Updated: 2022/07/02 18:35:01 by mruizzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo
{
	struct s_rule	*rule;
	int				id;
	int				n_eat;
	uint64_t		strv;
	pid_t			pid;
	pthread_t		death;

}				t_philo;

typedef struct s_rule
{
	long long	num_philo;
	uint64_t	time_die;
	uint64_t	time_eat;
	uint64_t	time_sleep;
	int			n_to_eat;
	uint64_t	start_time;
	t_philo		*philo;
	sem_t		*forks;
	sem_t		*msg;
	sem_t		*finish;
	sem_t		*dead;
	pthread_t	finish_eat;
}	t_rule;

int			check(int argc, char **argv);
long long	ft_atoi(const char *str);
uint64_t	start_timer(void);
void		start(t_rule *rule);
int			take_forks(t_philo	*ph);
void		routine(t_philo *ph);
void		my_sleep(uint64_t time, t_rule *rule);
void		philo_msg(t_philo *ph, int id, char *str);
void		*must_eat(void *rules);
void		*monitor(void *philo);

#endif