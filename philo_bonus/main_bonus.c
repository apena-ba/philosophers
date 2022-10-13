/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:46:10 by apena-ba          #+#    #+#             */
/*   Updated: 2022/10/13 12:11:39 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	action(t_data *info)
{
	int	i;
	int	status;

	i = 0;
	while (i < info->nthreads)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status))
		{
			i = 0;
			while (i < info->nthreads)
				kill(info->philo[i++].process, SIGKILL);
			return ;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	info;

	info.time = get_time();
	if (!parser(argc, argv, &info))
		return (write(2, "Error with arguments\n", 21), 1);
	sem_unlink("/forks");
	sem_unlink("/writing");
	info.fork = sem_open("/forks", O_CREAT, 0644, info.nthreads);
	info.writing = sem_open("/writing", O_CREAT, 0644, 1);
	if (info.fork == SEM_FAILED || info.writing == SEM_FAILED)
		return (1);
	if (philo_init(&info))
		return (1);
	action(&info);
	free(info.philo);
	sem_unlink("/forks");
	sem_unlink("/writing");
	return (0);
}
