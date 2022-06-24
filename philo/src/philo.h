/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruizzo <mruizzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:07:47 by mruizzo           #+#    #+#             */
/*   Updated: 2022/06/24 16:13:38 by mruizzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	struct s_rule	*rule;
	int				id;
	int				n_eat;
	int				end;
	uint64_t		strv;
	pthread_t		thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	philo_time;

}				t_philo;

typedef struct s_rule
{
	int				num_philo;
	uint64_t		time_die;
	uint64_t		time_eat;
	uint64_t		time_sleep;
	int				n_to_eat;
	int				some_die;
	int				finished;
	uint64_t		start_time;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	die_mutex;
	pthread_mutex_t	lock;
}	t_rule;

int			check(int argc, char **argv);
long long	ft_atoi(const char *str);
uint64_t	start_timer(void);
void		start(t_rule *rule);
void		starving(t_philo *ph);
int			check_mutex(int flag, t_philo *ph);
int			take_forks(t_philo	*ph);
void		routine(t_philo *ph);
void		my_sleep(uint64_t time);
void		philo_msg(t_philo *ph, int id, char *str);
void		monitor(t_rule *rule);

#endif