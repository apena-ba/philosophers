/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:34:18 by apena-ba          #+#    #+#             */
/*   Updated: 2022/10/13 12:11:39 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	poster(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo->forked)
	{
		sem_post(philo->info->fork);
		philo->forked--;
	}
}

void	*execution(void *param)
{
	t_philo	*philo;

	philo = param;
	while (1)
	{
		if (philo->info->numof_eat > 0
			&& philo->eaten >= philo->info->numof_eat)
		{
			philo->state = 0;
			poster(philo);
			exit(0);
		}
		if (get_time() > philo->meal_limit)
		{
			sem_wait(philo->info->writing);
			printf("%lli Philo %d died\n", get_time() - philo->info->time,
				philo->index + 1);
			philo->info->run = 0;
			exit(1);
		}
		usleep(235);
	}
}

static void	time_control(t_philo *philo, long long wait)
{
	long long	time;

	time = get_time() + wait;
	while (get_time() < time)
	{
		if (!philo->info->run)
			return ;
		usleep(235);
	}
}

int	philo_eats(t_philo *philo)
{
	if (!philo->info->run || !philo->state)
		return (1);
	sem_wait(philo->info->fork);
	philo->forked++;
	if (!philo->info->run || !philo->state)
		return (sem_post(philo->info->writing));
	print_action(philo, "has taken a fork\n");
	sem_wait(philo->info->fork);
	philo->forked++;
	if (!philo->info->run || !philo->state)
		return (sem_post(philo->info->writing));
	print_action(philo, "has taken a fork\n");
	philo->meal_limit = (get_time() + philo->info->timeto_die);
	print_action(philo, "is eating\n");
	if (philo->eaten >= 0)
		philo->eaten++;
	if (!philo->info->run || !philo->state)
		return (sem_post(philo->info->writing));
	time_control(philo, philo->info->timeto_eat);
	sem_post(philo->info->fork);
	philo->forked--;
	sem_post(philo->info->fork);
	philo->forked--;
	return (0);
}

int	routine(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_create(&philo->execute, NULL, &execution, (void *)philo);
	while (1)
	{
		philo_eats(philo);
		if (!philo->info->run || !philo->state)
			break ;
		print_action(philo, "is sleeping\n");
		time_control(philo, philo->info->timeto_sleep);
		if (!philo->info->run || !philo->state)
			break ;
		print_action(philo, "is thinking\n");
		usleep(235);
	}
	if (philo->info->run)
		exit(0);
	exit(1);
}
