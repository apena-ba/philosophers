/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:27:55 by apena-ba          #+#    #+#             */
/*   Updated: 2022/10/13 12:11:46 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	print_action(t_philo *philo, const char *s)
{
	long long	time;

	if (philo->info->run)
	{
		sem_wait(philo->info->writing);
		if (!philo->info->run || !philo->state)
			return (sem_post(philo->info->writing));
		time = get_time() - philo->info->time;
		printf("%lli Philo %d %s", time, philo->index + 1, s);
		sem_post(philo->info->writing);
	}
	return (0);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

static size_t	ft_strlen(const char *str)
{
	size_t	con;

	con = 0;
	while (str[con] != '\0')
	{
		con++;
	}
	return (con);
}

char	*ft_strjoin(const char *str1, const char *str2)
{
	char	*res;
	size_t	t;
	size_t	pos;
	size_t	pos2;

	if (!str1 || !str2)
		return (NULL);
	t = ft_strlen(str1) + ft_strlen(str2);
	res = (char *)malloc(sizeof(char) * (t + 1));
	if (!res)
		return (NULL);
	res[t] = 0;
	pos = 0;
	pos2 = 0;
	while (str1[pos2] != '\0')
	{
		res[pos] = str1[pos2];
		pos++;
		pos2++;
	}
	pos2 = 0;
	while (str2[pos2] != '\0')
		res[pos++] = str2[pos2++];
	return (res);
}
