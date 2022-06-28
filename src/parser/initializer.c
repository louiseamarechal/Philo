/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 08:43:37 by lmarecha          #+#    #+#             */
/*   Updated: 2022/06/28 15:06:34 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	intitialize_mutex(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		if (pthread_mutex_init(&args->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&args->print_philo_state, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&args->meal_state, NULL) != 0)
		return (0);
	return (1);
}

static int	initialize_philo(t_args *args, t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		philo[i].id = i;
		philo[i].left_fork = (i + 1) % args->nb_philo;
		philo[i].right_fork = i;
		philo[i].started_meal = args->first_timestamp;
		philo[i].args = args;
		i++;
	}
	return (1);
}

int	initialize(t_args *args, char **argv, int argc)
{
	args->nb_philo = ft_atoi(argv[1]);
	args->t_die = ft_atoi(argv[2]);
	args->t_eat = ft_atoi(argv[3]);
	args->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->number_must_eat = ft_atoi(argv[5]);
	else
		args->number_must_eat = -1;
	if (args->number_must_eat == 0) // si aucun ne doit manger fin de simulation
		return (0); // erreur
	args->died = 0;
	args->all_ate = 0;
	args->first_timestamp = timestamp();
	initialize_philo(args, args->philosophers);
	intitialize_mutex(args);
	return (1);
}
