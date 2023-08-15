/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apena-ba <apena-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:15:21 by apena-ba          #+#    #+#             */
/*   Updated: 2022/10/08 10:05:06 by apena-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit_str(const char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol(const char *str)
{
	int		pos;
	long	res;
	int		men;

	pos = 0;
	men = 1;
	res = 0;
	while ((str[pos] >= 9 && str[pos] <= 13) || str[pos] == ' ')
		pos++;
	if (str[pos] == '-' || str[pos] == '+')
	{
		if (str[pos] == '-')
			men = -1;
		pos++;
	}
	while (str[pos] >= '0' && str[pos] <= '9')
	{
		res = res * 10;
		res = res + (str[pos] - 48);
		pos++;
	}
	return (res * men);
}

static size_t	ft_putnbr_str(int n, char *str, size_t pos)
{
	if (n == -2147483648)
	{
		str[pos] = '-';
		pos++;
		str[pos] = '2';
		pos++;
		n = 147483648;
	}
	if (n < 0)
	{
		str[pos] = '-';
		pos++;
		n *= -1;
	}
	if (n < 10)
	{
		str[pos] = n + 48;
		pos++;
	}
	else
	{
		pos = ft_putnbr_str(n / 10, str, pos);
		pos = ft_putnbr_str(n % 10, str, pos);
	}
	return (pos);
}

static int	ft_ndigit(int n)
{
	size_t	count;

	count = 1;
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	while (n <= -10)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	pos;

	if (n >= 0)
		str = malloc(sizeof(char) * ft_ndigit(n) + 1);
	else
		str = malloc(sizeof(char) * ft_ndigit(n) + 2);
	if (!str)
		return (NULL);
	pos = 0;
	if (n >= 0)
		str[ft_ndigit(n)] = '\0';
	else
		str[ft_ndigit(n) + 1] = '\0';
	ft_putnbr_str(n, str, pos);
	return (str);
}
