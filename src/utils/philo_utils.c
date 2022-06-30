/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:30:21 by lmarecha          #+#    #+#             */
/*   Updated: 2022/06/30 15:46:54 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	is_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == 32)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (is_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += *str - '0';
		str++;
	}
	if (*str != '\0' && is_digit(*str) == 0)
		return (-1);
	return (result * sign);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	cpt;

	cpt = 0;
	while (s1[cpt] && s1[cpt] == s2[cpt])
		cpt++;
	return ((unsigned char)s1[cpt] - (unsigned char)s2[cpt]);
}

void	kill_everything(t_args *args)
{
	int	i;

	i = 1;
	while (i <= args->nb_philo)
	{
		pthread_mutex_destroy(&args->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&args->global_block);
}
