/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:46:54 by apena-ba          #+#    #+#             */
/*   Updated: 2022/10/13 12:12:03 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo
{
	int				state;
	int				forked;
	int				index;
	int				eaten;
	pid_t			process;
	long long		meal_limit;
	pthread_t		execute;
	struct s_data	*info;
}					t_philo;

typedef struct s_data
{
	int				nthreads;
	int				run;
	int				timeto_eat;
	long long		timeto_die;
	int				timeto_sleep;
	int				numof_eat;
	long long		time;
	sem_t			*writing;
	sem_t			*fork;
	t_philo			*philo;
}					t_data;

int					parser(int argc, char **argv, t_data *info);
int					philo_init(t_data *info);
int					ft_isdigit_str(const char *str);
long				ft_atol(const char *str);
char				*ft_itoa(int n);
char				*ft_strjoin(const char *str1, const char *str2);
int					routine(t_philo	*philo);
long long			get_time(void);
void				*execution(void *param);
int					print_action(t_philo *philo, const char *s);

#endif