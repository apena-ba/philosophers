/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:07:46 by apena-ba          #+#    #+#             */
/*   Updated: 2022/10/12 13:45:48 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*super_unlocker(t_data *info)
{
	int	i;

	i = 0;
	while (i < info->nthreads)
		unlocker(&info->philo[i++]);
	return (NULL);
}

static int	full_belly(t_philo *philo)
{
	if (philo->info->numof_eat < 0)
		return (0);
	if (philo->eaten >= philo->info->numof_eat)
	{
		philo->state = 0;
		unlocker(philo);
		return (1);
	}
	return (0);
}

static int	eaten_check(t_data *info)
{
	int	i;

	i = 0;
	while (i < info->nthreads)
	{
		if (info->philo[i].state)
			return (0);
		i++;
	}
	return (1);
}

static int	death_check(t_philo *philo)
{
	if ((get_time() > philo->meal_limit) && philo->state == 1)
	{
		philo->info->run = 0;
		unlocker(philo);
		pthread_mutex_lock(&philo->info->writing);
		printf("%lli Philo %d died\n", get_time() - philo->info->time,
			philo->index + 1);
		pthread_mutex_unlock(&philo->info->writing);
		return (1);
	}
	return (0);
}

void	*execution(void *param)
{
	int		i;
	int		flag;
	int		finished;
	t_data	*info;

	flag = 1;
	finished = 0;
	info = param;
	while (1)
	{
		i = 0;
		while (i < info->nthreads)
		{
			full_belly(&info->philo[i]);
			if (death_check(&info->philo[i]) || eaten_check(info))
			{
				info->run = 0;
				return (super_unlocker(info));
			}
			i++;
		}
		usleep(235);
	}
	return (NULL);
}
