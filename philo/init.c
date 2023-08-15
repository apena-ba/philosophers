/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 16:38:19 by apena-ba          #+#    #+#             */
/*   Updated: 2022/10/09 18:24:06 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_write(t_data *info, int i)
{
	int	x;

	x = 0;
	while (x < i)
		pthread_mutex_destroy(&info->fork[x++]);
	write(2, "Error while creating mutexes\n", 30);
	return (1);
}

static int	mutexes_init(t_data *info)
{
	int	i;

	i = 0;
	while (i < info->nthreads)
	{
		info->philo[i].index = i;
		info->philo[i].state = 1;
		info->philo[i].eaten = 0;
		info->philo[i].meal_limit = info->time + info->timeto_die;
		info->philo[i].info = info;
		if (i != info->nthreads - 1)
		{
			info->philo[i].left_fork = i;
			info->philo[i].right_fork = i + 1;
		}
		if (pthread_mutex_init(&info->fork[i], NULL))
			return (i);
		i++;
	}
	return (0);
}

int	philo_init(t_data *info)
{
	int	error;

	info->fork = malloc(sizeof(pthread_mutex_t) * (info->nthreads + 1));
	info->philo = malloc(sizeof(t_philo) * (info->nthreads + 1));
	pthread_mutex_init(&info->writing, NULL);
	error = mutexes_init(info);
	if (error)
		return (ft_write(info, error));
	info->philo[info->nthreads - 1].left_fork = info->nthreads - 1;
	info->philo[info->nthreads - 1].right_fork = 0;
	return (0);
}
