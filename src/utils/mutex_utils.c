/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:46:10 by lmarecha          #+#    #+#             */
/*   Updated: 2022/06/30 15:50:20 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	is_dead(t_args *args)
{
	int	ret;

	pthread_mutex_lock(&args->global_block);
	if (args->died != 1)
		ret = 0;
	else
		ret = 1;
	pthread_mutex_unlock(&args->global_block);
	return (ret);
}

int	is_full(t_args *args)
{
	int	ret;

	pthread_mutex_lock(&args->global_block);
	if (args->all_ate != 1)
		ret = 0;
	else
		ret = 1;
	pthread_mutex_unlock(&args->global_block);
	return (ret);
}

void	death_condition(t_args *args, t_philosopher philosopher, int i)
{
	pthread_mutex_lock(&args->global_block);
	if ((get_time() - philosopher.started_meal) > args->t_die)
	{
		pthread_mutex_unlock(&args->global_block);
		print_state(args, i, "\033[31mdied\033[0m");
		pthread_mutex_lock(&args->global_block);
		args->died = 1;
	}
	pthread_mutex_unlock(&args->global_block);
}

void	all_ate_checker(t_args *args, t_philosopher *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&args->global_block);
	while (args->number_must_eat != -1 && i < args->nb_philo
		&& philo[i].nb_meal >= args->number_must_eat)
		i++;
	pthread_mutex_unlock(&args->global_block);
	pthread_mutex_lock(&args->global_block);
	if (i == args->nb_philo)
		args->all_ate = 1;
	pthread_mutex_unlock(&args->global_block);
}
