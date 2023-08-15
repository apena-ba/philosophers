/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:34:18 by apena-ba          #+#    #+#             */
/*   Updated: 2022/10/12 13:46:16 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlocker(t_philo *philo)
{
	pthread_mutex_unlock(&philo->info->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->info->fork[philo->right_fork]);
	pthread_mutex_unlock(&philo->info->writing);
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

static void	philo_eats(t_philo *philo)
{
	if (!philo->info->run || !philo->state)
		return ;
	if ((philo->index + 1) % 2 == 0)
		pthread_mutex_lock(&philo->info->fork[philo->left_fork]);
	else
		pthread_mutex_lock(&philo->info->fork[philo->right_fork]);
	if (!philo->info->run || !philo->state)
		return (unlocker(philo));
	print_action(philo, "has taken a fork\n");
	if ((philo->index + 1) % 2 == 0)
		pthread_mutex_lock(&philo->info->fork[philo->right_fork]);
	else
		pthread_mutex_lock(&philo->info->fork[philo->left_fork]);
	if (!philo->info->run || !philo->state)
		return (unlocker(philo));
	print_action(philo, "has taken a fork\n");
	philo->meal_limit = (get_time() + philo->info->timeto_die);
	print_action(philo, "is eating\n");
	if (philo->eaten >= 0)
		philo->eaten++;
	if (!philo->info->run || !philo->state)
		return (unlocker(philo));
	time_control(philo, philo->info->timeto_eat);
	pthread_mutex_unlock(&philo->info->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->info->fork[philo->right_fork]);
}

void	*routine(void *param)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = param;
	while (1)
	{
		philo_eats(philo);
		if (!philo->info->run || !philo->state)
			return (NULL);
		print_action(philo, "is sleeping\n");
		time_control(philo, philo->info->timeto_sleep);
		if (!philo->info->run || !philo->state)
			return (NULL);
		print_action(philo, "is thinking\n");
		if (!philo->info->timeto_sleep || !philo->info->timeto_eat)
			usleep(235);
	}
	return (NULL);
}
