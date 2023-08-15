/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:46:10 by apena-ba          #+#    #+#             */
/*   Updated: 2022/10/12 14:11:12 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_wrter(t_data *info)
{
	int	x;

	info->run = 0;
	x = 0;
	write(2, "Error when creating threads\n", 29);
	while (x < info->nthreads)
		pthread_mutex_destroy(&info->fork[x++]);
}

static void	action(t_data *info, int i)
{
	pthread_create(&info->execute, NULL, &execution, (void *)info);
	while (i < info->nthreads)
	{
		if (pthread_create(&info->philo[i].thread, NULL, &routine,
				(void *)&info->philo[i]))
			return (ft_wrter(info));
		usleep(10);
		i++;
	}
	pthread_join(info->execute, NULL);
	i = 0;
	while (i < info->nthreads)
		pthread_join(info->philo[i++].thread, NULL);
	i = 0;
	while (i < info->nthreads)
		pthread_mutex_destroy(&info->fork[i++]);
	free(info->philo);
	free(info->fork);
}

int	main(int argc, char **argv)
{
	t_data	info;

	info.time = get_time();
	if (!parser(argc, argv, &info))
		return (write(2, "Error with arguments\n", 21), 1);
	if (philo_init(&info))
		return (1);
	action(&info, 0);
	return (0);
}
