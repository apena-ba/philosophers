/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 16:38:19 by apena-ba          #+#    #+#             */
/*   Updated: 2022/10/13 12:11:39 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	p_info_init(t_data *info)
{
	int	i;

	i = 0;
	while (i < info->nthreads)
	{
		info->philo[i].index = i;
		info->philo[i].forked = 0;
		info->philo[i].state = 1;
		info->philo[i].eaten = 0;
		info->philo[i].meal_limit = info->time + info->timeto_die;
		info->philo[i].info = info;
		info->philo[i].process = fork();
		if (info->philo[i].process == 0)
			routine(&info->philo[i]);
		i++;
	}
	return (0);
}

int	philo_init(t_data *info)
{
	info->philo = malloc(sizeof(t_philo) * (info->nthreads + 1));
	p_info_init(info);
	return (0);
}
