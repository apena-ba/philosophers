/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:52:46 by apena-ba          #+#    #+#             */
/*   Updated: 2022/10/08 10:08:10 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	info_insert(int argc, char **argv, t_data *info)
{
	info->run = 1;
	info->nthreads = ft_atol(argv[1]);
	info->timeto_die = ft_atol(argv[2]);
	info->timeto_eat = ft_atol(argv[3]);
	info->timeto_sleep = ft_atol(argv[4]);
	if (argc == 6)
		info->numof_eat = ft_atol(argv[5]);
	else
		info->numof_eat = -1;
}

int	parser(int argc, char **argv, t_data *info)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (0);
	if (!ft_atol(argv[1]))
		return (0);
	while (argv[i])
	{
		if (!ft_isdigit_str(argv[i]) || ft_atol(argv[i]) > 2147483647)
			return (0);
		i++;
	}
	info_insert(argc, argv, info);
	return (1);
}
